module Driver.Interpreter_v2 where

import Data.Int
import Data.Fixed (mod')
import Data.Maybe (fromMaybe)
import Control.Concurrent.Thread.Delay (delay)
import Control.Monad
import Control.Monad.IO.Class (liftIO)
import Data.IORef (IORef, newIORef, readIORef, writeIORef)
import System.IO.Unsafe (unsafePerformIO)

import Commands as Cmd
import Configuration

import Robotics.NXT as N
import Robotics.NXT.MotorControl


-- # NXT driver

instance Cmd.Driver NXT where
  initialize cfg = do
    liftIO $ writeIORef robotConfigRef cfg
    startMotorControlProgram
  output = applyCommand
  input  = readPort . read


-- # Reading and converting data from sensor

convertData :: InputValue -> Maybe Cmd.Reading
convertData (InputValue _ _ _ sensor _ raw _ scaled _) = case sensor of
  NoSensor        -> Nothing
  NoOfSensorTypes -> Nothing
  Switch          -> Just $ Cmd.Barrier (scaled == 1)
  Reflection      -> Just $ Cmd.Light $ fromIntegral raw
  N.Temperature   -> Just $ Cmd.Temperature $ fromIntegral scaled
  Angle           -> Just $ Cmd.Custom "Rotation" $ show scaled
  N.SoundDB       -> Just $ Cmd.Sound $ fromIntegral scaled
  N.SoundDBA      -> Just $ Cmd.Sound $ fromIntegral scaled
  Lowspeed        -> Just $ Cmd.Custom "LowSpeed" $ show scaled
  Lowspeed9V      -> Just $ Cmd.Custom "LowSpeed9V" $ show scaled
  N.Custom        -> Just $ Cmd.Custom "Custom" $ show scaled

readPort :: InputPort -> NXT Cmd.Reading
readPort = liftM conv . getInputValues
  where conv = fromMaybe (error "No data.") . convertData


-- # Converting and applying Commands

-- Calculating motor power for movement
calcMPower :: Double -> Int
calcMPower dist
  | dist  <=  0.0  = 0                -- In this case motor power is equal to 0 because of distance can't be negative.
  | dist  <   3.0  = 1                -- If distance is less than 3 centimeters, motor power will be equalt to 1.
  | dist  <= 300.0 = round $ dist/3.0 -- If distance is less than or equal to 300 centimeters, motor power will be equal to whole part of division of distance by 3.0.
  | otherwise      = 100              -- If distance is greater than 3 meters, motor power wil be equal to 100.

-- Calculating motor power for rotating
-- calcTPower :: Double -> Int
-- calcTPower angle
--  | angle >  pi2 = calcTPower $ mod' angle pi                              -- As each angle can be represented in [2*pi*k+fi] view,
                                                                           -- so function calculates fi and calls itself with it as argument.
--  | angle == pi  = 50                                                      -- This is a central point of this function, called tpunit.
--  | otherwise    = (min 100) . (+1) . round . (*api) $ fromIntegral tpunit -- Each angle in radians can be represented in [a*pi/b] view, and function uses this fact in rule below:
                                                                           --   f(x) = f(a*pi/b) = (a/b)*f(pi) .
                     -- As value of motor power lies in [-100,100] interval, so the final view of function is:
                     --   f(x) = min((a/b)*tpunit,100) .
                     -- (!) Notice that the result value of function lies in [0,100] interval.
--  where pi2 = 2.0 * pi
--	api = angle / pi

-- Turn power unit
-- tpunit :: Int
-- tpunit = calcTPower pi

calcPower :: Bool -> Double -> Int
calcPower True d  = 50
calcPower False d = calcMPower d

-- Calculating tacho limit
calcLimit :: Int -> Int64
calcLimit = fromIntegral . (*2) . abs

-- Function for calculeting a time that a robot is going to spend to complite a given task
-- First argument means a kind of task: turning around or move?
-- Second argument is a value that meaning depends on kind of task: in case of turning it represents an angle to rotate, in case of moving it is a distance to pass.
-- Third one is a motor power.
-- Last argument is a characteristics of the robot
workTime :: Bool -> Double -> Int -> RobotConfig -> Int
workTime True angle power (Vehical _) = 5 -- TODO: write a concrete realization for case of turning
workTime True angle power (Humanoid _) = 5 -- TODO: write a concrete realization for case of turning
workTime False dist power (Vehical (VehicalConfig r gms gwrs)) = let
                            rs  = gwrs $ gms power
                            div = 2.0*pi*r*rs
                          in round . (/div) $ dist
workTime False dist power (Humanoid (HumanoidConfig s t)) = let mult = dist/s in round . (*mult) $ t

startMotor :: Bool -> Bool -> Double -> NXT ()
startMotor turn reverse val = do
    chrs <- getRobotConfig
    controlledMotorCmd ports power limit [SmoothStart]
    liftIO . delay . (*1000) . toInteger $ workTime turn val power chrs
    controlledMotorCmd ports power limit [HoldBrake]
  where ports = if turn then [B] else [A]
        power = if reverse
                 then (-(calcPower turn val))
                 else calcPower turn val
        limit = calcLimit power

applyCommand :: Cmd.Command -> NXT ()
applyCommand (Cmd.Forward d)    = startMotor False False d
applyCommand (Cmd.Backward d)   = startMotor False True d
applyCommand (Cmd.Clockwise a)  = startMotor True False a
applyCommand (Cmd.CClockwise a) = startMotor True True a

{-# NOINLINE robotConfigRef #-}
robotConfigRef :: IORef RobotConfig
robotConfigRef = unsafePerformIO $ newIORef defaultRobotConfig

getRobotConfig :: NXT RobotConfig
getRobotConfig = liftIO $ readIORef robotConfigRef
