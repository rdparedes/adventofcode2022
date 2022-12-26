module Main where

import Data.Char (isUpper, ord)
import Data.List (intersect, nub)
import Data.List.Split (chunksOf)
import System.IO (IOMode (ReadMode), hGetContents, openFile)

main :: IO ()
main = do
  handle <- openFile "input.txt" ReadMode
  contents <- hGetContents handle
  let entries = lines contents
  let totalPriorities = foldr (\g ps -> ps + getItemPrio (findBadge g)) 0 (chunksOf 3 entries)
  print totalPriorities

getItemPrio :: Maybe Char -> Int
getItemPrio (Just c) = asciiCode - asciiOffset
  where
    asciiCode = ord c
    asciiOffset = if isUpper c then 38 else 96
getItemPrio Nothing = 0

findBadge :: [String] -> Maybe Char
findBadge g =
  let first = nub (head g)
      second = nub g !! 1
      third = nub g !! 2
      badge = intersect first (second `intersect` third)
   in case badge of
        [c] -> Just c
        _ -> Nothing