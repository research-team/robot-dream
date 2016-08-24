module Configuration where

-- This type describes a kind of robotic system depending on its approach of movement
data RobotConfig = Vehical  VehicalConfig
                 | Humanoid HumanoidConfig

data VehicalConfig = VehicalConfig {
                     wheelRadius            :: Double
                   , distBetweenWheels      :: Double
                   , calcMotorSpeed         :: Power -> MotorSpeed  -- This function calculates motor speed (rotations per second in other words) basing on given power.
                   , calcWheelRotationSpeed :: MotorSpeed -> Double -- This function calculates wheel rotation speed basing on given motor speed.
                   }

data HumanoidConfig = HumanoidConfig {
                      stepLength       :: Double
                    , stepTime         :: Double
                    , legRotationSpeed :: Double
                    }

type MotorSpeed = Double
type Power = Int

defaultRobotConfig = Vehical $ VehicalConfig 0.2 0.5 ((*1.8) . fromIntegral) (* 0.25)
