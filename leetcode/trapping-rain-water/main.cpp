#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
      map<int, int> edge_min;
      map<int, int> edge_max;
      map<int, int> blocks;
      int height_max = 0;
      int size = height.size();
      for (int i=0; i<size; ++i){
        int h = height[i];
        if (edge_min.find(h) == edge_min.end()) {
          edge_min[h] = i;
          blocks[h] = 0;
        }
        edge_max[h] = i;
        blocks[h]++;
        height_max = max(height_max, h);
      }

      int all_blocks = 0;
      int block_left = 123456789;
      int block_right = -123456789;
      int water = 0;
      const auto blocks_end = blocks.end();
      for (int h=height_max; h>0; --h) {
        if (blocks.find(h) != blocks_end){
          all_blocks += blocks[h];
          block_left = min(block_left, edge_min[h]);
          block_right = max(block_right, edge_max[h]);
        }
        water += block_right - block_left + 1 - all_blocks;
      }

      return water;
    }
};

void input(vector<int>& height)
{
  //height = {0,1,0,2,1,0,1,3,2,1,2,1};
  //height = {4, 2, 3};
  height = {1};
}

int main(int argc, char* argv[])
{
  vector<int> height;
  input(height);
  Solution s;
  cout << s.trap(height) << endl;
  return 0;
}
