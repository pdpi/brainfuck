module Optimiser where

import Interpreter

optimise :: Program -> Program
optimise ((Add n):Add m :is) = optimise ((Add $ n+m):is)
optimise ((Loop s)    :is) = (Loop $ optimise s):(optimise is)
optimise (i           :is) = i:optimise is
optimise []                = []