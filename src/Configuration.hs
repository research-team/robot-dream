module Configuration where

-- This type describes a kind of robotic system depending on its approach of movement
-- TODO: decide, rename this type or not.
data Characteristics = Vehical  WheelRadius DistBetweenWheels GetMotorSpeed GetWheelRotationSpeed
                     | Humanoid StepLength StepTime LegRotationSpeed

-- Radius of leading pair of wheels in meters.
type WheelRadius = Double
-- Distance between two wheels in pair.
type DistBetweenWheels = Double
-- This is a synonim for function that somehow calculates wheel rotation speed basing on given motor speed.
type GetWheelRotationSpeed = Double -> Double
-- This is a synonim for function that somehow calculates motor speed (rotations per second in other words) basing on given power.
type GetMotorSpeed = Int -> Double
-- Step length in meters.
type StepLength = Double
-- This type describes a time that robot spends to make a step.
type StepTime = Double
-- This type describes a constant speed with that robot rotates its leg.
type LegRotationSpeed = Double
