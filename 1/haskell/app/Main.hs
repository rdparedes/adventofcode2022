{-# LANGUAGE BlockArguments #-}

module Main where

import System.IO ( IOMode(ReadMode), hGetContents, openFile )

main :: IO ()
main = do
  handle <- openFile "input.txt" ReadMode
  contents <- hGetContents handle
  -- split the contents into lines
  let c = lines contents
  let accums = (0, 0)
  let final_accums = reduce c accums
  -- print the biggest number
  print final_accums

-- Define a function that takes two accumulators and a value from the input list,
-- and returns a pair containing the updated accumulator values.
combine :: (Int, Int) -> String -> (Int, Int)
combine (biggest, temp) c = (biggest', temp')
  where
    biggest' = if c == "" then max biggest temp else biggest
    temp' = if c == "" then 0 else temp + readInt c

-- Define the reduce function, which uses foldl to apply the combine function
-- to each value in the input list, using the given initial accumulator values.
reduce :: [String] -> (Int, Int) -> (Int, Int)
reduce xs (biggest, temp) = foldl combine (biggest, temp) xs

readInt :: String -> Int
readInt = read