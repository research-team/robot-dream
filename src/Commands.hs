{-# LANGUAGE DeriveFunctor #-}
module Commands where

import Control.Monad.Free

import System

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

data Interaction next = Output Characteristics Command next
                      | Input String (Reading -> next)
                      deriving (Functor)

type Script = Free Interaction


forward :: Characteristics -> Double -> Script ()
forward chrs d = liftF $ Output chrs (Forward d) ()

backward :: Characteristics -> Double -> Script ()
backward chrs d = liftF $ Output chrs (Backward d) ()

clockwise :: Characteristics -> Double -> Script ()
clockwise chrs d = liftF $ Output chrs (Clockwise d) ()

cclockwise :: Characteristics -> Double -> Script ()
cclockwise chrs d = liftF $ Output chrs (CClockwise d) ()

readInput :: String -> Script Reading
readInput port = liftF (Input port id)


class Monad m => Driver m where
  initialize :: m ()
  output :: Characteristics -> Command -> m ()
  input  :: String -> m Reading


run :: Driver m => Script a -> m a
run (Pure a) = return a
run (Free (Output chrs cmd next)) = do
    output chrs cmd
    run next
run (Free (Input v f)) = do
    i <- input v
    run $ f i
