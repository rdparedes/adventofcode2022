#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <algorithm>

using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::string;

int main(int argc, char **argv)
{
  int temp;
  std::array<int, 3> top_three = {0, 0, 0};
  ifstream ifs;
  string buffer;
  ifs.open("./input.txt", ios::in);

  if (ifs)
  {
    while (!ifs.eof())
    {
      std::getline(ifs, buffer);
      if (buffer == "")
      {
        auto min = std::min_element(top_three.begin(), top_three.end());
        if (temp > *min)
        {
          cout << temp << " is bigger than " << *min << endl;
          *min = temp;
          cout << "the list is now: ";
          std::copy(top_three.begin(), top_three.end(), std::ostream_iterator<int>(cout, ", "));
          cout << endl;
        }
        temp = 0;
      }
      else
      {
        temp += std::stoi(buffer.c_str());
      }
    }
  }
  int top_three_sum = 0;
  for (auto element : top_three)
  {
    top_three_sum += element;
  }
  cout << top_three_sum << endl;
}
