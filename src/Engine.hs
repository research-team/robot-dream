{-# LANGUAGE UnicodeSyntax #-}
{-# LANGUAGE ExistentialQuantification #-}
{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE MultiParamTypeClasses #-}
module Engine where

import Control.Monad (forever)
import Data.Functor ((<$>))
import Data.List (find, delete)
import Data.Maybe (fromMaybe)

import Commands
import Rules


instance CanMatch (IfDo (Reading -> Bool) a) Reading where
  matches (IfDo f _) = f

instance CanMatch (IfDoThen (Reading -> Bool) a) Reading where
  matches (IfDoThen (IfDo f _) _) = f

-- THE ENGINE --
data Rule = ∀ a . (CanMatch a Reading, Actionable a Command) => Rule a

instance CanMatch Rule Reading where
  matches (Rule a) = matches a

instance Actionable Rule Command where
  getAction (Rule a) = getAction a

f :: [Rule] -> Reading -> Command
f db r = fromMaybe (Forward 0.5) $ getAction <$> find (`matches` r) db

-- TODO: implement backtracking
chainForward :: CanMatch (IfDoThen c a) c => [IfDoThen c a] -> c -> [a]
chainForward []        _    = []
chainForward (r:rules) goal =
  if matches r goal
    then return $ action $ rule r
    else let goal' = condition $ rule r
             a     = action $ rule r
         in a : chainForward rules goal' -- FIXME: this way we'll never reach original goal


initialDB :: [Rule]
initialDB = [Rule $ IfDo (Barrier True) (CClockwise (pi/6))]

engine :: Script ()
engine = forever $ do
  r <- readInput "One" -- FIXME: there should be no parameter here. I suggest polling all the ports.
  let c = f initialDB r
  executeCommand c
