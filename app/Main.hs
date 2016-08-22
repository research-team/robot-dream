module Main where

import Commands
import Lib
import Configuration

import Driver.Console

dummyScript :: Script ()
dummyScript = do
    forward 5.5
    clockwise 30.0
    forward 3.2

main :: IO ()
main = run dummyScript
