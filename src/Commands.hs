module Commands where

data Commnd = Forward    Double -- move forward d centimeters
            | Backward   Double -- move backward d centimeters
            | Clockwise  Double -- turn d radians clockwise
            | CClockwise Double -- turn d radians counter-clockwise

data Reading = Barrier Bool   -- whether robot hit some barrier or not
             | Light   Double -- light intensity from light sensor
             | Custom String String -- reading from custom sensor with given description and serialized value
