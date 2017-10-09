#include <stack>

#include <iostream>

using namespace std;

bool isValid (string s)
{
  stack<char> st;

  int len = s.length();
  char c, top;
  for (int i=0; i<len; ++i) {
    c = s[i];
    switch (c) {
      case '(':
      case '{':
      case '[':
        st.push(c);
        break;
      case ')':
        if (st.size() == 0) return false;
        top = st.top();
        if (top != '(') return false;
        st.pop();
        break;
      case '}':
        if (st.size() == 0) return false;
        top = st.top();
        if (top != '{') return false;
        st.pop();
        break;
      case ']':
        if (st.size() == 0) return false;
        top = st.top();
        if (top != '[') return false;
        st.pop();
        break;
    }
  }

  if (st.size() > 0) return false;

  return true;
}

int main (int argc, char* argv[])
{
  cout << (isValid(argv[1]) ? "true" : "false") << endl;
  return 0;
}
