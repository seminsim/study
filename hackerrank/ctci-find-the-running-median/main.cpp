#include <iostream>
#include <iomanip>
#include <queue>
#include <functional>

using namespace std;

bool eq = true;
int n, a;
priority_queue<int> ql;
priority_queue<int, std::vector<int>, greater<int> > qh;

void insert(int a)
{
  if (eq) {
    if (!qh.empty() && a > qh.top()) {
      ql.push(qh.top());
      qh.pop();
      qh.push(a);
    } else {
      ql.push(a);
    }
  } else {
    if (a > ql.top()) {
      qh.push(a);
    } else {
      qh.push(ql.top());
      ql.pop();
      ql.push(a);
    }
  }
  eq = !eq;
}

double median()
{
  if (eq) {
    return (double)(ql.top() + qh.top()) / 2.0;
  }else{
    return (double)ql.top();
  }
}

void solve()
{
  cin >> n;
  for (int i=0; i<n; ++i) {
    cin >> a;
    insert(a);
    cout << fixed << setprecision(1) << median() << endl;
  }
}

int main (int argc, char* argv[])
{
  solve();
  return 0;
}
