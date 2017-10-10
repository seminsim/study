#include <set>
#include <vector>

#include <iostream>

using namespace std;

bool isValidSudoku (vector< vector<char> >& board)
{
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

void generateInput (vector< vector<char> >& board)
{
  board.resize(9);

  board[0].resize(9);
  board[0][0] = '5';
  board[0][1] = '3';
  board[0][2] = '.';
  board[0][3] = '.';
  board[0][4] = '7';
  board[0][5] = '.';
  board[0][6] = '.';
  board[0][7] = '.';
  board[0][8] = '.';

  board[1].resize(9);
  board[1][0] = '6';
  board[1][1] = '.';
  board[1][2] = '.';
  board[1][3] = '1';
  board[1][4] = '9';
  board[1][5] = '5';
  board[1][6] = '.';
  board[1][7] = '.';
  board[1][8] = '.';

  board[2].resize(9);
  board[2][0] = '.';
  board[2][1] = '9';
  board[2][2] = '8';
  board[2][3] = '.';
  board[2][4] = '.';
  board[2][5] = '.';
  board[2][6] = '.';
  board[2][7] = '6';
  board[2][8] = '.';

  board[3].resize(9);
  board[3][0] = '8';
  board[3][1] = '.';
  board[3][2] = '.';
  board[3][3] = '.';
  board[3][4] = '6';
  board[3][5] = '.';
  board[3][6] = '.';
  board[3][7] = '.';
  board[3][8] = '3';

  board[4].resize(9);
  board[4][0] = '4';
  board[4][1] = '.';
  board[4][2] = '.';
  board[4][3] = '8';
  board[4][4] = '.';
  board[4][5] = '3';
  board[4][6] = '.';
  board[4][7] = '.';
  board[4][8] = '1';

  board[5].resize(9);
  board[5][0] = '7';
  board[5][1] = '.';
  board[5][2] = '.';
  board[5][3] = '.';
  board[5][4] = '2';
  board[5][5] = '.';
  board[5][6] = '.';
  board[5][7] = '.';
  board[5][8] = '6';

  board[6].resize(9);
  board[6][0] = '.';
  board[6][1] = '6';
  board[6][2] = '.';
  board[6][3] = '.';
  board[6][4] = '.';
  board[6][5] = '.';
  board[6][6] = '2';
  board[6][7] = '8';
  board[6][8] = '.';

  board[7].resize(9);
  board[7][0] = '.';
  board[7][1] = '.';
  board[7][2] = '.';
  board[7][3] = '4';
  board[7][4] = '1';
  board[7][5] = '9';
  board[7][6] = '.';
  board[7][7] = '.';
  board[7][8] = '5';

  board[8].resize(9);
  board[8][0] = '.';
  board[8][1] = '.';
  board[8][2] = '.';
  board[8][3] = '.';
  board[8][4] = '8';
  board[8][5] = '.';
  board[8][6] = '.';
  board[8][7] = '7';
  board[8][8] = '9';
}

int main (int argc, char* argv[])
{
  vector< vector<char> > board;

  generateInput(board);
  cout << (isValidSudoku(board) ? "Valid" : "Invalid") << endl;

  return 0;
}