{-# LANGUAGE UnicodeSyntax #-}
{-# LANGUAGE ExistentialQuantification #-}
{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE MultiParamTypeClasses #-}
module Engine where

import Control.Monad (forever)
import Data.Functor ((<$>))
<<<<<<< Updated upstream
import Data.List (find, delete)
=======
import Data.List (find, foldl')
>>>>>>> Stashed changes
import Data.Maybe (fromMaybe)
import Control.Monad.Loop

import Commands
import Rules


instance CanMatch (IfDo Reading a) Reading where
  matches f r = 

instance CanMatch (IfDoThen Reading a) Reading where
  matches f = condition . rule $ f

-- THE ENGINE --
data Rule = ∀ a . (CanMatch a Reading, Actionable a Command) => Rule a

instance CanMatch Rule Reading where
  matches (Rule a) = matches a

instance Actionable Rule Command where
  getAction (Rule a) = getAction a

findSuitableReaction :: [Rule] -> Reading -> Command
findSuitableReaction db r = fromMaybe (Forward 0.5) $ getAction <$> find (`matches` r) db

<<<<<<< Updated upstream
-- TODO: implement backtracking
chainForward :: CanMatch (IfDoThen c a) c => [IfDoThen c a] -> c -> [a]
chainForward []        _    = []
chainForward (r:rules) goal =
  if matches r goal
    then return $ action $ rule r
    else let goal' = condition $ rule r
             a     = action $ rule r
         in a : chainForward rules goal' -- FIXME: this way we'll never reach original goal

 =======
-- TEMP SOLUTION --
-- This solution of construction a chain of needed actions is not perfect:
-- function fails when searching of suitable next element for chain fails

chainForward' :: CanMatch (IfDoThen c a) c => [IfDoThen c a] -> c -> c -> [a]
chainForward' [] _    _    = []
chainForward' db init goal = let first = findElem db init in constructChain db first goal

findElem :: CanMatch (IfDoThen c a) c => [IfDoThen c a] -> c -> Maybe (IfDoThen c a)
findElem [] _    = Nothing
findElem db cond = find (`mathces` init) db

constructChain :: CanMatch (IfDoThen c a) c => [IfDoThen c a] -> Maybe (IfDoThen c a) -> c -> [a]
constructChain [] _            _    = []
constructChain _  Nothing      _    = []
constructChain db (Just chain) goal = 
  if mathces elem goal
    then return . action . rule $ chain
    else let outcome   = outcome elem
             act       = action . rule $ chain
             nextElem = find db outcome
	 in act : constructChain db nextElem goal

------------------

delibDB :: [IfDoThen Reading Command]
delibDB = []
>>>>>>> Stashed changes

initialDB :: [Rule]
initialDB = [Rule $ IfDo (Barrier True) (CClockwise (pi/6))]

engine :: Script ()
engine = forever $ do
  r <- readInput "One" -- FIXME: there should be no parameter here. I suggest polling all the ports.
  let c = findSuitableReaction initialDB r
  executeCommand c
