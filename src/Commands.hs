{-# LANGUAGE DeriveFunctor #-}
module Commands where

import Control.Monad.Free

import Configuration (RobotConfig)


data Command = Forward    Double -- move forward d centimeters
             | Backward   Double -- move backward d centimeters
             | Clockwise  Double -- turn d radians clockwise
             | CClockwise Double -- turn d radians counter-clockwise
             deriving (Eq,Show)

data Reading = Barrier     Bool          -- whether robot hit some barrier or not
             | Light       Double        -- light intensity from light sensor
             | Temperature Double        -- value of temperature from temperature sensor
             | Sound       Double        -- volume of sound from sound sensor; dB or dB(A) scaling
             | Custom      String String -- reading from custom sensor with given description and serialized value
             deriving (Eq,Show)

data Interaction next = Output Command next
                      | Input String (Reading -> next)
                      deriving (Functor)

type Script = Free Interaction


forward :: Double -> Script ()
forward d = liftF $ Output (Forward d) ()

backward :: Double -> Script ()
backward d = liftF $ Output (Backward d) ()

clockwise :: Double -> Script ()
clockwise d = liftF $ Output (Clockwise d) ()

cclockwise :: Double -> Script ()
cclockwise d = liftF $ Output (CClockwise d) ()

readInput :: String -> Script Reading
readInput port = liftF (Input port id)

executeCommand :: Command -> Script ()
executeCommand c = liftF $ Output c ()


class Monad m => Driver m where
  initialize :: RobotConfig -> m ()
  output :: Command -> m ()
  input  :: String -> m Reading


run :: Driver m => Script a -> m a
run (Pure a) = return a
run (Free (Output cmd next)) = do
    output cmd
    run next
run (Free (Input v f)) = do
    i <- input v
    run $ f i
