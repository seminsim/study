#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <stack>

using namespace std;

bool is_balanced(string expression) {
  stack<char> st;
  int len = expression.length();
  char c, cl;
  for (int i=0; i<len; ++i) {
    c = expression[i];
    switch (c){
      case '(':
      case '{':
      case '[':
        st.push(c);
        break;
      case ')':
        if (st.empty()) return false;
        cl = st.top();
        if (cl != '(') return false;
        st.pop();
        break;
      case '}':
        if (st.empty()) return false;
        cl = st.top();
        if (cl != '{') return false;
        st.pop();
        break;
      case ']':
        if (st.empty()) return false;
        cl = st.top();
        if (cl != '[') return false;
        st.pop();
        break;
    }
  }
  return st.empty();
}

int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        string expression;
        cin >> expression;
        bool answer = is_balanced(expression);
        if(answer)
            cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
