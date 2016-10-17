{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE FunctionalDependencies #-}
{-# LANGUAGE FlexibleInstances #-}
module Rules where

-- | IF 'condition' DO 'action' rule following Minsky's "Model Six"
data IfDo c a = IfDo {
                  condition :: c
                , action    :: a
                } deriving (Eq,Show)

-- | IF 'condition' DO 'action' THEN 'outcome' rule following Minsky's "Model Six"
-- This form is used for deliberative thinking and above layers
data IfDoThen c a = IfDoThen {
                      rule    :: IfDo c a
                    , outcome :: c
                    } deriving (Eq,Show)

-- | The main common trait of the rules - they might match some situation
class CanMatch a b where
  matches :: a -> b -> Bool

-- | The second common trait of the rules - they prescribe some action
class Actionable a b | a -> b where
  getAction :: a -> b

instance Eq c => CanMatch (IfDo c a) c where
  matches (IfDo c1 _) c2 = c1 == c2

instance Eq c => CanMatch (IfDoThen c a) c where
  matches (IfDoThen (IfDo c1 _) _) c2 = c1 == c2

instance Actionable (IfDo c a) a where
  getAction (IfDo _ a) = a

instance Actionable (IfDoThen c a) a where
  getAction (IfDoThen (IfDo _ a) _) = a
