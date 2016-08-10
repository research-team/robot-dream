module Driver.Interpreter_v2 where

import Control.Monad
import Data.Int
import Data.Fixed (mod')

import Commands as Cmd

import Robotics.NXT as N
import Robotics.NXT.MotorControl


-- # NXT driver

instance Cmd.Driver NXT where
  initialize = startMotorControlProgram
  output     = applyCommand
  input val  = readPort . read $ val


-- # Reading and converting data from sensor

convertData :: InputValue -> Cmd.Reading
convertData (InputValue _ _ _ sensor _ raw _ scaled _) = case sensor of
  NoSensor        -> Cmd.Custom "No sensor" "" 
  Switch          -> if scaled == 1 then (Cmd.Barrier True) else (Cmd.Barrier False)
  Reflection      -> Cmd.Light $ fromIntegral raw
  Temperature     -> Cmd.Custom "Temperature" (show scaled)
  Angle           -> Cmd.Custom "Rotation" (show scaled)
  SoundDB         -> Cmd.Custom "SoundDB" (show scaled)
  SoundDBA        -> Cmd.Custom "SoundDBA" (show scaled)
  Lowspeed        -> Cmd.Custom "LowSpeed" (show scaled)
  Lowspeed9V      -> Cmd.Custom "LowSpeed9V" (show scaled)
  NoOfSensorTypes -> Cmd.Custom "NoOfSensorType" ""
  N.Custom        -> Cmd.Custom "Custom" (show scaled)

readPort :: InputPort -> NXT Cmd.Reading
readPort port = liftM convertData val
  where val = getInputValues port


-- # Converting and applying Commands

calcMPower :: Double -> Int
calcMPower dist
  | dist  <=  0.0  = 0
  | dist  <   3.0  = 1
  | dist  <= 300.0 = round $ dist/3.0
  | otherwise      = 100

calcTPower :: Double -> Int
calcTPower angle
  | angle >  pi2 = calcTPower $ mod' angle pi
  | angle == pi  = 50
  | otherwise    = (min 100) . round . (*api) $ fromIntegral tpunit
  where pi2 = 2.0 * pi
	api = angle / pi

-- Turn power unit
tpunit :: Int
tpunit = calcTPower pi

calcPower :: Bool -> Double -> Int
calcPower turn val = if turn then (calcTPower val) else (calcMPower val)

calcLimit :: Int -> Int64
calcLimit power = fromIntegral . (*20) . abs $ power

startMotor :: Bool -> Bool -> Double -> NXT ()
startMotor turn reverse val = do
    controlledMotorCmd ports power limit [SmoothStart]
    -- TODO: write a timer or something else what will stop the motor AFTER achieving a goal of task
    controlledMotorCmd ports power limit [HoldBrake]
  where ports = if turn then [B] else [A]
        power = if reverse
		then ( -(calcPower turn val))
		else (calcPower turn val)
        limit = calcLimit power
 
applyCommand :: Cmd.Command -> NXT ()
applyCommand (Cmd.Forward d)    = startMotor False False d
applyCommand (Cmd.Backward d)   = startMotor False True d
applyCommand (Cmd.Clockwise a)  = startMotor True False a
applyCommand (Cmd.CClockwise a) = startMotor True True a
