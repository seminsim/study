#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxArea (vector<int>& heights)
{
  int size = heights.size();
  int max = 0, vol = 0;

  for (int i=0; i<size; ++i) {
    for (int j=i+1; j<size; ++j) {
      vol = min(heights[i], heights[j]) * (j-i);
      cout << "i=" << i << " j=" << j << " vol=" << vol << endl;
      if (vol > max) max = vol;
    }
  }

  return max;
}

int main (int argc, char* argv[])
{
//  int input[] = {1,2,3,4,5,6,7};
  int input[] = {1,2,1};
  vector<int> heights (input, input + (sizeof(input) / sizeof(int)));
  cout << maxArea(heights) << endl;
  return 0;
}
