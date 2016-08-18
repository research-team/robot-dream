module Main where

import Commands
import Lib
import System

import Driver.Console

dummyScript :: Script ()
dummyScript = do
    forward chrs 5.5
    clockwise chrs 30.0
    forward chrs 3.2
  where chrs = Vehical 0.2 (\x -> (*1.8) . fromIntegral $ x) (\x -> x*0.25)

main :: IO ()
main = run dummyScript
