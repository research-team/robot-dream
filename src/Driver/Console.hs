module Driver.Console where

import Commands

instance Driver IO where
  initialize = return ()

  output = print

  input = do
    l <- getLine
    let (s1:s2:_) = words l
    return $ Custom s1 s2 -- FIXME: case by the first string
