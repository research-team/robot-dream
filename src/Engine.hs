{-# LANGUAGE UnicodeSyntax #-}
{-# LANGUAGE ExistentialQuantification #-}
{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE MultiParamTypeClasses #-}
module Engine where

import Control.Monad (forever, guard)
import Data.Functor ((<$>))
import Data.List (find, delete)
import Data.Maybe (fromMaybe)
import Control.Concurrent (forkIO)
import Control.Concurrent.MVar (newEmptyMVar, putMVar, takeMVar)

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

findSuitableReaction :: [Rule] -> Reading -> Command
findSuitableReaction db r = fromMaybe (Forward 0.5) $ getAction <$> find (`matches` r) db

chainForward :: (Eq c, Eq a) => [IfDoThen c a] -> c -> c -> [a]
chainForward []    _     _    = []
chainForward rules start goal = do
  r <- rules              -- try all available rules
  guard $ matches r start -- reject `r` and backtrack unless it matches current condition
  let res = outcome r
  let a   = action $ rule r
  if res == goal
    then return a
    else a : chainForward (delete r rules) (condition $ rule r) goal

parallelChainConstruct :: (Eq c, Eq a) => [IfDoThen c a] -> c -> c -> [[a]]
parallelChainConstruct []    _     _    = []
parallelChainConstruct rules start goal = do
  fstRls <- getListOfFirstRules rules start
  if fstRls == []
    then []
    else map (fun rules goal) fstRls
  where fun = \rs g r -> let c   = condition . rule $ r
                             rs' = delete r rs
		         in do
		           m <- newEmptyMVar
			   putMVar m []
			   forkIO $ do
                             a  <- takeMVar m
			     as <- chainForward rs' c g
			     putMVar m (as:a)
			   return $ takeMVar m

getListOfFirstRules :: (Eq c, Eq a) => [IfDoThen c a] -> c -> [IfDoThen c a]
getListOfFirstRules []    _     = []
getListOfFirstRules rules start = do
  r <- find (`matches` start) rules
  case r of
    Nothing   -> []
    (Just r') ->  r' : f1 (delete r' rules) start

initialDB :: [Rule]
initialDB = [Rule $ IfDo (Barrier True) (CClockwise (pi/6))]

engine :: Script ()
engine = forever $ do
  r <- readInput "One" -- FIXME: there should be no parameter here. I suggest polling all the ports.
  let c = f initialDB r
  executeCommand c
