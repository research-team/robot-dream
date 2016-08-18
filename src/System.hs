module System where

-- This type describes a kind of robotic system depending on its approach of movement
-- TODO: decide, rename this type or not.
data Characteristics = Vehical  WheelRadius GetMotorSpeed GetWheelRotationSpeed
                     | Humanoid StepLength Double -- The second argument of constructor describes a time that robot spends to make a step.

type WheelRadius = Double
type StepLength = Double
-- This is a synonim for function that somehow calculates wheel rotation speed basing on given motor speed.
type GetWheelRotationSpeed = Double -> Double
-- This is a synonim for function that somehow calculates motor speed (rotations per second in other words) basing on given power.
type GetMotorSpeed = Int -> Double
