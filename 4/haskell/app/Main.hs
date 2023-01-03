{-# LANGUAGE NamedFieldPuns #-}

{-
In how many assignment pairs does one range fully contain the other?
For example, 2-8 fully contains 3-7, and 6-6 is fully contained by 4-6.

--- Part Two ---

In how many assignment pairs do the ranges overlap?
 -}

module Main where

import Data.List.Split (splitOn)
import System.IO (IOMode (ReadMode), hGetContents, openFile)

main :: IO ()
main = do
  handle <- openFile "input.txt" ReadMode
  contents <- hGetContents handle
  let entries = lines contents
  let totalContains = foldr (\entry acc -> acc + aContainsB entry) 0 entries
  let totalOverlaps = foldr (\entry acc -> acc + aOverlapsWithB entry) 0 entries
  print ("Total contains: ", totalContains)
  print ("Total overlaps: ", totalOverlaps)

aContainsB :: String -> Int
aContainsB entry = fromEnum (contains a b || contains b a)
  where
    [strA, strB] = splitOn "," entry
    a = assignmentFromString strA
    b = assignmentFromString strB

aOverlapsWithB :: String -> Int
aOverlapsWithB entry = fromEnum (overlaps a b)
  where
    [strA, strB] = splitOn "," entry
    a = assignmentFromString strA
    b = assignmentFromString strB

data Assignment = Assignment
  { firstElem :: Int,
    lastElem :: Int
  }
  deriving (Show)

assignmentFromString :: String -> Assignment
assignmentFromString str =
  let (sFirst, sLast) = span (/= '-') str
      firstElem = read sFirst
      lastElem = read (drop 1 sLast)
   in Assignment {firstElem, lastElem}

contains :: Assignment -> Assignment -> Bool
contains a b =
  (firstElem a <= firstElem b) && (lastElem a >= lastElem b)

overlaps :: Assignment -> Assignment -> Bool
overlaps a b =
  (lastElem b >= firstElem a) && (firstElem b <= lastElem a)
