#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <unordered_map>

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

PART 2:

The only way to tell which item type is the right one is by finding the one item type that
is common between all three Elves in each group.

Find the item type that corresponds to the badges of each three-Elf group.
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
  return '\0';
}

const char find_badge(const std::array<string, 3> &groups)
{
  std::unordered_map<char, int> char_counts;
  for (char c : groups[0])
  {
    char_counts[c] = 1;
  }
  for (char c : groups[1])
  {
    if (char_counts[c])
    {
      char_counts[c] = 2;
    }
  }
  for (char c : groups[2])
  {
    if (char_counts[c] > 1)
    {
      cout << "found this letter! -> " << c << endl;
      return c;
    }
  }
  return '\0';
}

int main(int argc, char **argv)
{
  string buffer;
  std::array<string, 3> current_group = {"", "", ""};
  int total = 0;
  std::ifstream ifs;
  ifs.open("./input.txt", std::ios::in);

  if (ifs)
  {
    while (!ifs.eof())
    {
      int temp = 0;
      while (temp < 3)
      {
        std::getline(ifs, buffer);
        current_group[temp] = buffer;
        temp++;
      }
      const int item_priority = get_item_priority(find_badge(current_group));
      total += item_priority;
    }
  }

  cout << "Result: " << total << endl;
}
