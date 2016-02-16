module Parser where

import Interpreter
import Data.List

type Parser = [Program]

push :: Parser -> Parser
push p = []:p

pop :: Parser -> Parser
pop (p:p':ps) = ((Loop $ reverse p):p'):ps

-- Add an instruction to the top of 
add :: Instruction -> Parser -> Parser
add i (p:ps) = (i:p):ps

parse :: String -> Program
parse src = reverse . head $ foldl' (flip parseChar) [[]] src

parseChar :: Char -> Parser -> Parser
parseChar '.' = add Put
parseChar ',' = add Get
parseChar '>' = add Next
parseChar '<' = add Prev
parseChar '+' = add $ Add 1
parseChar '-' = add $ Add (-1)
parseChar '[' = push
parseChar ']' = pop
parseChar _   = id
