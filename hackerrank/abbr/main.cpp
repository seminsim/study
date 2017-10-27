#include <list>
#include <set>
#include <string>
#include <iostream>

using namespace std;

string solve()
{
  string a, b;
  cin >> a >> b;

  int a_len = a.length();
  int b_len = b.length();

  set<int> cursorSet, newCursorSet;
  cursorSet.insert(-1);  // initial state

  char c_a;
  for (int i=0; i<a_len; ++i) {
    c_a = a[i];
    if (c_a >= 'a') { // lower case
      c_a += -'a' + 'A';
      list<int> adding;
      for (auto& cur : cursorSet) {
        if (cur+1 < b_len && b[cur+1] == c_a) adding.push_back(cur+1);
      }

      for (auto& val : adding) cursorSet.insert(val);
    } else {
      for (auto& cur : cursorSet) {
        if (cur+1 < b_len && b[cur+1] == c_a) {
          newCursorSet.insert(cur+1);
        }
      }
      cursorSet = move(newCursorSet);
    }
  }

  return cursorSet.find(b_len-1) != cursorSet.end() ? "YES" : "NO";
}

int main (int argc, char* argv[])
{
  int N;
  cin >> N;
  for (int i=0; i<N; ++i)
    cout << solve() << endl;
  return 0;
}
