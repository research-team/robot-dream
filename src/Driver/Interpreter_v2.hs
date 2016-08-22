module Driver.Interpreter_v2 where

import Control.Monad
import Data.Int
import Data.Fixed (mod')
import Control.Concurrent.Thread.Delay (delay)
import Control.Monad.IO.Class (liftIO)

import Commands as Cmd
import Configuration

import Robotics.NXT as N
import Robotics.NXT.MotorControl


-- # NXT driver

instance Cmd.Driver NXT where
  initialize = startMotorControlProgram
  output     = applyCommand
  input      = readPort . read 


-- # Reading and converting data from sensor

convertData :: InputValue -> Maybe Cmd.Reading
convertData (InputValue _ _ _ sensor _ raw _ scaled _) = case sensor of
  NoSensor        -> Nothing
  NoOfSensorTypes -> Nothing
  Switch          -> Just $ Cmd.Barrier (if scaled == 1 then True else False)
  Reflection      -> Just $ Cmd.Light $ fromIntegral raw
  N.Temperature   -> Just $ Cmd.Temperature $ fromIntegral scaled
  Angle           -> Just $ Cmd.Custom "Rotation" $ show scaled -- TODO: try to understand a metric of data providing by NXT Angle sensor
                                                                -- and after write a function for converting that metric to radians.
  N.SoundDB       -> Just $ Cmd.Sound $ fromIntegral scaled
  N.SoundDBA      -> Just $ Cmd.Sound $ fromIntegral scaled
  Lowspeed        -> Just $ Cmd.Custom "LowSpeed" $ show scaled
  Lowspeed9V      -> Just $ Cmd.Custom "LowSpeed9V" $ show scaled
  N.Custom        -> Just $ Cmd.Custom "Custom" $ show scaled

readPort :: InputPort -> NXT Cmd.Reading
readPort port = liftM conv val
  where val  = getInputValues port
        fun  = \x -> case x of
          Nothing -> error "No data."
          Just a  -> a
        conv = fun . convertData


-- # Converting and applying Commands

-- Calculating motor power for movement
calcMPower :: Double -> Int
calcMPower dist
  | dist  <=  0.0  = 0                -- In this case motor power is equal to 0 because of distance can't be negative.
  | dist  <   3.0  = 1                -- If distance is less than 3 centimeters, motor power will be equalt to 1.
  | dist  <= 300.0 = round $ dist/3.0 -- If distance is less than or equal to 300 centimeters, motor power will be equal to whole part of division of distance by 3.0.
  | otherwise      = 100              -- If distance is greater than 3 meters, motor power wil be equal to 100.

calcPower :: Bool -> Double -> Int
calcPower True d  = 50 
calcPower False d = calcMPower d

-- Calculating tacho limit
calcLimit :: Int -> Int64
calcLimit = fromIntegral . (*2) . abs

-- Function for getting equivalnet value of angle if it is greater than or equal to 2pi. Argument is unsigned value.
getAngle :: Double -> Double
getAngle angle
  | angle < 2.0*pi = angle
  | otherwise      = angle `mod'` (2.0*pi)

-- Function for calculeting a time that a robot is going to spend to complite a given task
-- First argument means a kind of task: turning around or move?
-- Second argument is a value that meaning depends on kind of task: in case of turning it represents an angle to rotate, in case of moving it is a distance to pass.
-- Third one is a motor power.
-- Last argument is a characteristics of the robot
workTime :: Bool -> Double -> Int -> Characteristics -> Int
workTime True angle power chrs = case chrs of
  (Vehical wr dbr gms gwrs)  -> let rs  = gwrs . gms $ power
                                    div = 2.0*pi*wr*rs
				    fi  = getAngle angle
			        in round . (/div) $ fi * dbr
  (Humanoid _ _ lrs)         -> let fi = getAngle angle
                                in (*2) . round . (/lrs) $ fi
workTime False dist power chrs = case chrs of
  (Vehical wr _ gms gwrs) -> let rs  = gwrs . gms $ power
                                 div = 2.0*pi*wr*rs*100.0 -- As metric of argument 'dist' is in centimeters, so it has to be divided by 100 to convert metric into meters.
                             in round . (/div) $ dist
  (Humanoid sl st _ )     -> let mult = dist/(100.0*sl) in round . (*mult) $ st

startMotor :: Characteristics -> Bool -> Bool -> Double -> NXT ()
startMotor chrs turn reverse val = do
    controlledMotorCmd ports power limit [SmoothStart]
    liftIO . delay . (*1000) . toInteger . (workTime turn val power) $ chrs
    controlledMotorCmd ports power limit [HoldBrake]
  where ports = if turn then [B] else [A]
        power = if reverse
		then (-(calcPower turn val))
		else (calcPower turn val)
        limit = calcLimit power
 
applyCommand :: Characteristics -> Cmd.Command -> NXT ()
applyCommand chrs (Cmd.Forward d)    = startMotor chrs False False d
applyCommand chrs (Cmd.Backward d)   = startMotor chrs False True d
applyCommand chrs (Cmd.Clockwise a)  = startMotor chrs True False a
applyCommand chrs (Cmd.CClockwise a) = startMotor chrs True True a
