{-# LANGUAGE BlockArguments #-}

module Main where

import Data.List (sort)
import System.IO (IOMode (ReadMode), hGetContents, openFile)

main :: IO ()
main = do
  handle <- openFile "input.txt" ReadMode
  contents <- hGetContents handle
  -- split the contents into lines
  let c = lines contents
  -- Use the first element in the tuple to store the top 3 biggest groups. Use the
  -- second element as temporary storage to add each element of a group.
  let accumulators = ([0, 0, 0], 0)
  let final_accums = reduce c accumulators
  -- print the biggest number
  print (total final_accums)
  where
    total (top_three, _) = sum top_three

-- Define a function that takes two accumulators and a value from the input list,
-- and returns a pair containing the updated accumulator values.
combine :: ([Int], Int) -> String -> ([Int], Int)
combine (top_three, temp) c = (top_three', temp')
  where
    top_three' = if c == "" then pick_highest top_three temp else top_three
      where
        pick_highest xs x = take 3 . reverse . sort $ x : xs
    temp' = if c == "" then 0 else temp + readInt c
      where
        readInt :: String -> Int
        readInt = read

-- Define the reduce function, which uses foldl to apply the combine function
-- to each value in the input list, using the given initial accumulator values.
reduce :: [String] -> ([Int], Int) -> ([Int], Int)
reduce xs (top_three, temp) = foldl combine (top_three, temp) xs
