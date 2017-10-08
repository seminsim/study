#include <cstdio>

class Solution {
public:
    bool isDigit(char c)
    {
      return (c >= '0' && c <= '9');
    }

    int overflow(bool isNegative)
    {
      return isNegative ? -2147483648 : 2147483647;
    }

    int myAtoi(string str) {
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
};