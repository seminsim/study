#include <bits/stdc++.h>
#include <set>

using namespace std;

const int MAX = 200;
const int MIN = 0;


vector <int> I; // input array
int N;  // length of input
int D;  // length of detection window
multiset<int> wl; // detection window (left)
multiset<int> wr; // detection window (right)
int d;  // detected count
int isEven;

void add(int val)
{
    auto size_l = wl.size();
    auto size_r = wr.size();

    if (size_l == 0) {
        wl.insert(val);
        return;
    }

    int max_l;
    auto it_maxl = wl.rbegin();
    max_l = *(it_maxl);

    if (val <= max_l) {
        wl.insert(val);
    } else {
        wr.insert(val);
        return;
    }
}

void remove(int val)
{
    int max_l;
    auto it_maxl = wl.rbegin();
    max_l = *(it_maxl);

    if (val <= max_l) {
        wl.erase(wl.find(val));
    } else {
        wr.erase(wr.find(val));
        return;
    }
}

void balance()
{
    auto size_l = wl.size();
    auto size_r = wr.size();

    while (size_r > size_l) {
        int val = *(wr.begin());
        wl.insert(val);
        wr.erase(wr.find(val));
        size_l = wl.size();
        size_r = wr.size();
    }

    if (size_l > size_r + 1) {
        int val = *(wl.rbegin());
        wr.insert(val);
        wl.erase(wl.find(val));
    }
}

int median2()
{
    if (isEven) {
        auto it_l = wl.rbegin();
        auto it_r = wr.begin();

        return (*it_l) + (*it_r);;
    } else {
        auto it_l = wl.rbegin();
        return 2 * (*it_l);
    }
}

int solve()
{
    int r;
    int m2;
    d = 0;
    for (int i=0; i<N-1; ++i) {
        if (i < D) {
            add(I[i]);
            balance();
        } else {
            remove(I[i-D]);
            balance();
            add(I[i]);
            balance();
        }

        if (i < D-1) continue;

        m2 = median2();
        if (I[i+1] >= m2) d++;
    }

    return d;
}

int activityNotifications(vector <int> expenditure, int _d) {
    // Complete this function
    N = expenditure.size();
    D = _d;
    isEven = (D % 2 == 0);
    I = expenditure;
    d = 0;
    wl.clear();
    wr.clear();

    return solve();
}

int main() {
    int n;
    int d;
    cin >> n >> d;
    vector<int> expenditure(n);
    for(int expenditure_i = 0; expenditure_i < n; expenditure_i++){
       cin >> expenditure[expenditure_i];
    }
    int result = activityNotifications(expenditure, d);
    cout << result << endl;
    return 0;
}
