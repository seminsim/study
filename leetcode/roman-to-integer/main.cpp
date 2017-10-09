#include <iostream>
#include <string>
#include <map>

using namespace std;

int romanToInt (string s)
{
  map<char, int> notation;
  notation['I'] = 1;
  notation['V'] = 5;
  notation['X'] = 10;
  notation['L'] = 50;
  notation['C'] = 100;
  notation['D'] = 500;
  notation['M'] = 1000;

  int size = s.length();
  int val = 0;
  int last_notation_value = 0;
  int last_notation = 0;
  int current_notation = 0;

  for (int i=0; i<size; ++i) {
    current_notation = notation[s[i]];
    if (current_notation > last_notation) {
      val += current_notation - last_notation_value - last_notation_value;
    }else {
      val += current_notation;
    }

    if (last_notation == current_notation) {
      last_notation_value += current_notation;
    }

    last_notation_value = last_notation = current_notation;
  }

  return val;
}

int main (int argc, char* argv[])
{
  cout << romanToInt(argv[1]) << endl;
  return 0;
}
