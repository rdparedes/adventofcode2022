#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::string;

int main(int argc, char **argv)
{
  int temp;
  int biggest_number = 0;
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
        biggest_number = std::max(temp, biggest_number);
        temp = 0;
      }
      else
      {
        temp += std::stoi(buffer.c_str());
      }
    }
  }
  cout << biggest_number << endl;
}
