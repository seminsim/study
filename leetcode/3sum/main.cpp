#include <algorithm>
#include <map>
#include <vector>

#include <iostream>

using namespace std;

vector< vector<int> > threeSum (vector<int>& nums)
{
  sort(nums.begin(), nums.end());

  map <int, int> cnt;
  int size = nums.size();
  int curCount = 0;
  int num;
  for (int i=0; i<size; ++i) {
    num = nums[i];
    if (cnt.find(num) == cnt.end()) cnt[num] = 1;
    else cnt[num] = cnt[num] + 1;
  }

  int firstNum, firstNumCount, secondNum, thirdNum, secondNumCount;
  vector< vector<int> > triplets;
  for (auto it=cnt.begin(); it!=cnt.end(); ++it) {
    firstNum = it->first;
    firstNumCount = it->second;

    auto it2 = it;
    if (firstNumCount == 1) it2++;
    if (it2 == cnt.end()) break;

    for (; it2!=cnt.end(); ++it2) {
      secondNum = it2->first;
      secondNumCount = it2->second;
      thirdNum = -(firstNum + secondNum);
      if (secondNum == thirdNum) {
        if ((firstNum != secondNum && secondNumCount >= 2) ||
           (firstNum == secondNum && secondNumCount >= 3)
        ) {
          int triplet[] = {firstNum, secondNum, secondNum};
          triplets.push_back( vector<int>(triplet, triplet + (sizeof(triplet) / sizeof(int))));
        }
        break;
      }
      if (secondNum > thirdNum) {
        break;
      }
      if (cnt.find(thirdNum) != cnt.end()) {
        int triplet[] = {firstNum, secondNum, thirdNum};
        triplets.push_back( vector<int>(triplet, triplet + (sizeof(triplet) / sizeof(int))));
      }
    }
  }

  return triplets;
}

void printOutput (vector< vector<int> > triplets)
{
  int size = triplets.size();
  for (int i=0; i<size; ++i) {
    cout << triplets[i][0] << " " << triplets[i][1] << " " << triplets[i][2] << endl;
  }
}

int main (int argc, char* argv[])
{
  int numsArr[] = {-1, 0, 1, 2, -1, -4, 0, 0};
  vector<int> nums (numsArr, numsArr + (sizeof(numsArr) / sizeof(int)));
  printOutput( threeSum(nums) );
  return 0;
}
