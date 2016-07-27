{-# LANGUAGE DeriveFunctor #-}
module Commands where

import Control.Monad.Free


data Command = Forward    Double -- move forward d centimeters
             | Backward   Double -- move backward d centimeters
             | Clockwise  Double -- turn d radians clockwise
             | CClockwise Double -- turn d radians counter-clockwise
             deriving (Eq,Show)

data Reading = Barrier Bool   -- whether robot hit some barrier or not
             | Light   Double -- light intensity from light sensor
             | Custom String String -- reading from custom sensor with given description and serialized value
             deriving (Eq,Show)

data Interaction next = Output Command next
                      | Input (Reading -> next)
                      deriving (Functor)

type Script = Free Interaction


class Driver m where
  initialize :: m ()
  output :: Command -> m ()
  input  :: m Reading
