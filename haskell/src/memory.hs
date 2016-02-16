module Memory where

data Memory = Memory [Int] Int [Int] deriving (Show)

peek :: Memory -> Int
peek (Memory _ c _) = c

write :: Memory -> Int -> Memory
write (Memory b _ f) i = Memory b i f

next :: Memory -> Memory
next (Memory b c [])     = Memory (c:b) 0 []
next (Memory b c (f:fs)) = Memory (c:b) f fs

prev :: Memory -> Memory
prev (Memory []     c f) = Memory [] 0 (c:f)
prev (Memory (b:bs) c f) = Memory bs b (c:f)

inc :: Memory -> Memory
inc = add 1

add :: Int -> Memory -> Memory
add n (Memory b c f) = Memory b ((c + n) `mod` 255) f

dec :: Memory -> Memory
dec = sub 1

sub :: Int -> Memory -> Memory
sub n (Memory b c f) = Memory b ((c - n) `mod` 255) f
