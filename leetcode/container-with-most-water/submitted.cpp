#include <algorithm>

class Solution {
public:
    int maxArea(vector<int>& heights) {
      int size = heights.size();
      int max = 0, vol = 0;

      vector<bool> covered(size, false);
      for (int i=0; i<size; ++i) {
        if (covered[i]) continue;
        for (int j=i+1; j<size; ++j) {
          vol = min(heights[i], heights[j]) * (j-i);
          if (heights[j] <= heights[i]) { covered[j] = true; }
          if (vol > max) max = vol;
        }
      }

      return max;
    }
};