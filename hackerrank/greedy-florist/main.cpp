#include <bits/stdc++.h>

using namespace std;

int getMinimumCost(int n, int k, vector < int > c){
    // Complete this function
    int step = 0;
    int totalCost = 0;
    int current = n-1;

    sort(c.begin(), c.end());
    vector <bool> purchased (n, false);
    for (int i=n-1; i>=0; ) {
      for (int j=0; j<k && i>=0; ++j, --i) {
        totalCost += (step+1) * c[i];
      }
      step++;
    }

    return totalCost;
}

int main() {
    int n;
    int k;
    cin >> n >> k;
    vector<int> c(n);
    for(int c_i = 0; c_i < n; c_i++){
       cin >> c[c_i];
    }
    int minimumCost = getMinimumCost(n, k, c);
    cout << minimumCost << endl;
    return 0;
}
