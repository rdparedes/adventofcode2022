#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

/*

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

 */

using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::string;
using std::vector;

const char ROCK = 'X';
const char PAPER = 'Y';
const char SCISSORS = 'Z';

std::map<char, int> player_points{
    {ROCK, 1},
    {PAPER, 2},
    {SCISSORS, 3}};

std::map<char, std::map<char, int>> opponent_vs_player{
    {'A', {{ROCK, 3}, {PAPER, 6}, {SCISSORS, 0}}},
    {'B', {{ROCK, 0}, {PAPER, 3}, {SCISSORS, 6}}},
    {'C', {{ROCK, 6}, {PAPER, 0}, {SCISSORS, 3}}}};

int play_hand(const char &opponent, const char &player)
{
  if (!opponent || !player)
  {
    return 0;
  }
  return opponent_vs_player[opponent][player] + player_points[player];
}

int main(int argc, char **argv)
{
  string buffer;
  char opponent;
  char player;
  int result = 0;
  ifstream ifs;
  ifs.open("./input.txt", ios::in);

  if (ifs)
  {
    while (!ifs.eof())
    {
      std::getline(ifs, buffer);
      opponent = buffer[0];
      player = buffer[2];
      result += play_hand(opponent, player);

      cout << opponent << " " << player << " => " << result << endl;
    }
  }

  cout << "Result: " << result << endl;
}
