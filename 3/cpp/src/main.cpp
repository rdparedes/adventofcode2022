#include <iostream>
#include <fstream>
#include <string>
#include <array>

/*
The first half of the characters represent items in the first compartment,
while the second half of the characters represent items in the second compartment.

vJrwpWtwJgWrhcsFMMfFFhFp -> vJrwpWtwJgWr, hcsFMMfFFhFp.
The only item type that appears in both compartments is lowercase p
The priority of the item type that appears in both compartments is 16 (p)

Lowercase item types a through z have priorities 1 through 26.
Uppercase item types A through Z have priorities 27 through 52.

Find the item type that appears in both compartments of each rucksack.
What is the sum of the priorities of those item types?
 */

using std::cout;
using std::endl;
using std::string;

const int ASCII_UPPERCASE_OFFSET = 38;
const int ASCII_LOWERCASE_OFFSET = 96;

const int get_item_priority(const char &c)
{
  const int ascii_code = (int)c;
  if (ascii_code >= 65 && ascii_code <= 90)
  {
    // handle uppercases
    return ascii_code - ASCII_UPPERCASE_OFFSET;
  }
  else if (ascii_code >= 97 && ascii_code <= 122)
  {
    // handle lowercases
    return ascii_code - ASCII_LOWERCASE_OFFSET;
  }
  else
  {
    return 0;
  }
}

const std::array<string, 2> split_sack(const string &sack)
{
  const int sack_length = sack.size();
  const int middle = sack_length / 2;
  const string first_compartment = sack.substr(0, middle);
  const string second_compartment = sack.substr(middle);
  return std::array<string, 2>({first_compartment, second_compartment});
}

const char find_duplicate(const std::array<string, 2> &compartments)
{
  for (auto left_item : compartments[0])
  {
    for (auto right_item : compartments[1])
    {
      if (left_item == right_item)
      {
        return left_item;
      }
    }
  }
  return NULL;
}

int main(int argc, char **argv)
{
  string buffer;
  int total = 0;
  std::ifstream ifs;
  ifs.open("./input.txt", std::ios::in);

  if (ifs)
  {
    while (!ifs.eof())
    {
      std::getline(ifs, buffer);
      const int item_priority = get_item_priority(find_duplicate(split_sack(buffer)));
      total += item_priority;
    }
  }

  cout << "Result: " << total << endl;
}
