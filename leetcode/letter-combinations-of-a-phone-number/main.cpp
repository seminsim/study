#include <map>
#include <vector>

#include <iostream>

using namespace std;

map<char, string> numberMapping;

void printOutput (vector<string> combinations);

vector<string> letterCombinations (string digits, int pos, string prefix)
{
  int inputLen = digits.length();
  if (pos == inputLen) {
    vector<string> ret;
    ret.push_back(prefix);
    return ret;
  }

  vector<string> ret;
  vector<string> retRest;

  char digit = digits[pos];

  if (numberMapping.find(digit) == numberMapping.end()) {
    return ret;
  }

  string mapping = numberMapping[digit];
  int size = mapping.length();
  int restSize;

  for (int i=0; i<size; ++i) {
    retRest = letterCombinations(digits, pos+1, prefix + mapping[i]);
    restSize = retRest.size();
    for (int j=0; j<restSize; ++j) {
      ret.push_back (retRest[j]);
    }
  }

  return ret;
}

vector<string> letterCombinations (string digits)
{
  if (digits.length() == 0) {
    return vector<string>();
  }

  numberMapping['2'] = "abc";
  numberMapping['3'] = "def";
  numberMapping['4'] = "ghi";
  numberMapping['5'] = "jkl";
  numberMapping['6'] = "mno";
  numberMapping['7'] = "pqrs";
  numberMapping['8'] = "tuv";
  numberMapping['9'] = "wxyz";

  return letterCombinations(digits, 0, "");
}

void printOutput (vector<string> combinations)
{
  int size = combinations.size();
  for (int i=0; i<size; ++i) {
    cout << combinations[i] << endl;
  }
}

int main (int argc, char* argv[])
{
  printOutput( letterCombinations(argv[1]) );
  return 0;
}
