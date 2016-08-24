{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE MultiParamTypeClasses #-}
module Engine where

import Data.Functor ((<$>))
import Data.List (find)
import Data.Maybe (fromMaybe)

import Commands
import Rules


instance CanMatch (IfDo (Reading -> Bool) a) Reading where
  matches (IfDo f _) = f

instance CanMatch (IfDoThen (Reading -> Bool) a) Reading where
  matches (IfDoThen (IfDo f _) _) = f

-- THE ENGINE --
f :: (CanMatch a Reading, Actionable a Command) => [a] -> Reading -> Command
f db r = fromMaybe (Forward 0.5) $ getAction <$> find (`matches` r) db
