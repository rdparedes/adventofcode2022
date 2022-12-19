module Main where

import System.IO (IOMode (ReadMode), hGetContents, openFile)

{-
C > B > A > C

A = Rock -> X -> 1
B = Paper -> Y -> 2
C = Scissors -> Z -> 3

W = 6
D = 3
L = 0

Ex:
A Y = 2 (Points for Y) + 6 (for win) = 8
B X = 1 (Points for X) + 0 (for loss) = 1
C Z = 3 (Points for Z) + 3 (for draw) = 6

2nd part:
X = Lose
Y = Draw
Z = Win

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

findPlayerHandPoints :: Char -> Int
findPlayerHandPoints playerHand =
  case playerHand of
    'X' -> 1
    'Y' -> 2
    'Z' -> 3
    _ -> 0

findMatchPoints :: Char -> Char -> Int
findMatchPoints opponentHand playerHand =
  case lookup opponentHand opponentXPlayer of
    Just xs -> xs !! index
      where
        -- Takes advantage of the fact that X, Y and Z convert to integers in
        -- incremental order, so that X == 88, Y == 89 and Z == 90
        index = fromEnum playerHand - fromEnum 'X'
    Nothing -> 0
  where
    opponentXPlayer :: [(Char, [Int])]
    -- Match points are in [rock, paper, scissors] order. F.ex:
    -- A (Rock) vs Rock (3), Paper (6), Scissors (0)
    opponentXPlayer =
      [ ('A', [3, 6, 0]),
        ('B', [0, 3, 6]),
        ('C', [6, 0, 3])
      ]

findPlayerHand :: Char -> Char -> Char
findPlayerHand opponentHand outcome =
  case lookup opponentHand opponentXOutcome of
    Just xs -> xs !! index
      where
        index = fromEnum outcome - fromEnum 'X'
    Nothing -> 'X'
  where
    opponentXOutcome :: [(Char, [Char])]
    opponentXOutcome =
      -- Outcomes are in [lose, draw, win] order. F.ex.:
      -- If opponent plays 'A', play 'Z' to lose, 'X' to draw, 'Y' to win
      [ ('A', ['Z', 'X', 'Y']),
        ('B', ['X', 'Y', 'Z']),
        ('C', ['Y', 'Z', 'X'])
      ]

playMatch :: String -> Int -> Int
playMatch entry acc = acc + matchPoints + playerPoints
  where
    entries = words entry
    opponentHand = head (head entries)
    outcome = head (entries !! 1)
    playerHand = findPlayerHand opponentHand outcome
    matchPoints = findMatchPoints opponentHand playerHand
    playerPoints = findPlayerHandPoints playerHand
