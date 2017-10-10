#include <set>

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
      set<int> row;
      set<int> col;
      set<int> cell;
      char c;
      int num, rowKey, colKey, cellKey;

      for (int i=0; i<9; ++i) {
        for  (int j=0; j<9; ++j) {
          c = board[i][j];
          if (c == '.') continue;
          num = c - '0';

          rowKey = i * 9 + num;
          if (row.find(rowKey) != row.end()) return false;
          row.insert(rowKey);

          colKey = j * 9 + num;
          if (col.find(colKey) != col.end()) return false;
          col.insert(colKey);

          cellKey = ((i/3) * 3 + (j/3)) * 9 + num;
          if (cell.find(cellKey) != cell.end()) return false;
          cell.insert(cellKey);
        }
      }

      return true;
    }
};