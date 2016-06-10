module Rules where

data IfDo c a = IFDo {
                  condition :: c
                , action    :: a
                }

data IfDoThen c a = IfDoThen {
                      rule    :: IfDo c a
                    , outcome :: c
                    }
