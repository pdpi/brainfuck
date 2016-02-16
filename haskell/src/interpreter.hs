module Interpreter where

import Control.Monad
import Data.Char
import Memory

data Instruction = Get
                 | Put
                 | Next
                 | Prev
                 | Add Int
                 | Loop [Instruction] deriving (Show, Eq)

type Program = [Instruction]

interpreter :: Program -> Memory -> IO Memory
interpreter prog memory = foldM (flip process) memory prog

process :: Instruction -> Memory -> IO Memory
process Put = \memory -> do
  putStr [chr . peek $ memory]
  return memory
process Get = \memory -> do
  char:_ <- getLine
  return (write memory $ ord char)
process Next     = return . next
process Prev     = return . prev
process (Add n)  = return . (add n)
process (Loop p) = \memory -> if (peek memory) /= 0
  then do
    mem <- interpreter p memory
    process (Loop p) mem
  else return memory
