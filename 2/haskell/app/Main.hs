module Main where

import System.IO (IOMode (ReadMode), hGetContents, openFile)

{-
C > B > A > C

A = Rock
B = Paper
C = Scissors

2nd part:
X = Lose = 0
Y = Draw = 3
Z = Win = 6

Ex:

A Y = draw -> play X (Rock) to draw -> 1 (Points for X) + 3 (for draw) = 4
B X = lose -> play X (Rock) to lose -> 1 (Points for X) + 0 (for defeat) = 1
B Z = win -> play Z (Scissors) to win -> 3 (Points for Z) + 6 (for win) = 9
-}

main :: IO ()
main = do
  handle <- openFile "input.txt" ReadMode
  contents <- hGetContents handle
  let entries = lines contents
  let result = foldr playMatch 0 entries
  print result

findMatchPoints :: Char -> Char -> Int
findMatchPoints opponentHand outcome = resultMatrix !! x !! y
  where
    x = fromEnum opponentHand - fromEnum 'A'
    y = fromEnum outcome - fromEnum 'X'
    {-
      Precalculated values of each possible match, where the columns
      are X, Y, Z (Lose, Draw, Win) and the rows are A, B, C (Rock, Paper, Scissors)
    -}
    resultMatrix :: [[Int]]
    resultMatrix =
      [ [3, 4, 8],
        [1, 5, 9],
        [2, 6, 7]
      ]

playMatch :: String -> Int -> Int
playMatch entry acc = acc + matchPoints
  where
    entries = words entry
    opponentHand = head (head entries)
    outcome = head (entries !! 1)
    matchPoints = findMatchPoints opponentHand outcome
