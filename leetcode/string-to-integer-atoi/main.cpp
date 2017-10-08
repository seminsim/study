#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

bool isDigit(char c)
{
  return (c >= '0' && c <= '9');
}

int overflow(bool isNegative)
{
  return isNegative ? -2147483648 : 2147483647;
}

int solve (string str)
{
  int cur = 0;
  int len = str.length();
  int number = 0;

  // skip first white spaces
  while (isspace(str[cur])) cur ++;

  if (cur == len) return 0;

  // negative
  bool isNegative = false;
  if (str[cur] == '-') {
    isNegative = true;
    cur ++;
  } else if (str[cur] == '+') {
    cur ++;
  }

  if (cur == len) return 0;

  // number
  while (isDigit(str[cur])) {
    if (((number * 10) / 10) != number) return overflow(isNegative);
    number = number * 10 + (str[cur] - '0');

    if (number < 0) return overflow(isNegative);

    cur ++;
  }

  return isNegative ? -number : number;
}

int solve_lib (string str)
{
  int cur = 0;
  int len = str.length();
  int number = 0;

  // skip first white spaces
  while (isspace(str[cur])) cur ++;

  if (cur == len) return 0;

  // negative
  bool isNegative = false;
  if (str[cur] == '-') {
    isNegative = true;
    cur ++;
  } else if (str[cur] == '+') {
    cur ++;
  }

  if (cur == len) return 0;

  // number
  while (isDigit(str[cur])) {
    number = number * 10 + (str[cur] - '0');
    cur ++;
  }

  return isNegative ? -number : number;
}

int main (int argc, char* argv[])
{
  cout << solve(argv[1]) << endl;
  cout << atoi(argv[1]) << endl;

  return 0;
}
