#include <string>
#include <iostream>

using namespace std;

int strStr (string haystack, string needle)
{
  int hSize, nSize;
  int matchedLen;

  hSize = haystack.length();
  nSize = needle.length();
  matchedLen = 0;

  if (nSize == 0) return 0;
  if (nSize > hSize) return -1;

  for (int i=0; i<hSize; ++i) {
    if (haystack[i] == needle[matchedLen]) {
      matchedLen++;
      if (matchedLen == nSize) return i-nSize+1;
    } else if (matchedLen > 0) {
      i -= matchedLen;
      matchedLen = 0;
    }
  }

  return -1;
}

int main (int argc, char* argv[])
{
  cout << strStr(argv[1], argv[2]) << endl;
  return 0;
}
