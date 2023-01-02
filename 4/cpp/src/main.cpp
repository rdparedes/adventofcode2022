#include <iostream>
#include <fstream>
#include <string>
#include <array>

/*
In how many assignment pairs does one range fully contain the other?

For example, 2-8 fully contains 3-7, and 6-6 is fully contained by 4-6.
 */

using std::cout;
using std::endl;
using std::string;

const char PAIR_DELIMITER = ',';
const char RANGE_DELIMITER = '-';

struct Assignment
{
  int first;
  int last;
  Assignment(const string &);
  bool contains(const Assignment *);
};

Assignment::Assignment(const string &a)
{
  size_t pos = a.find(RANGE_DELIMITER);
  string s_first = a.substr(0, pos);
  this->first = std::stoi(s_first);
  this->last = std::stoi(a.substr(pos + 1));
}

bool Assignment::contains(const Assignment *other)
{
  return (other->first - this->first >= 0 && other->last - this->last <= 0);
}

int main(int argc, char **argv)
{
  int total = 0;
  string buffer;
  std::ifstream ifs;
  ifs.open("./input.txt", std::ios::in);

  if (ifs)
  {
    while (!ifs.eof())
    {
      std::getline(ifs, buffer);
      if (buffer.empty())
      {
        break;
      }
      size_t pos = buffer.find(PAIR_DELIMITER);
      Assignment *a = new Assignment(buffer.substr(0, pos));
      Assignment *b = new Assignment(buffer.substr(pos + 1));

      if (a->contains(b) || b->contains(a))
      {
        total++;
      }
    }
  }

  cout << "Result: " << total << endl;
}
