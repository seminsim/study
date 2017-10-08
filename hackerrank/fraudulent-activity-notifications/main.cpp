#include <vector>
#include <set>
#include <iostream>
#include <memory.h>
#include <stdlib.h>

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

void readInputCase1()
{
    N = 9;
    D = 5;
    isEven = (D % 2 == 0);
    I.resize(N);
    I[0] = 2;
    I[1] = 3;
    I[2] = 4;
    I[3] = 2;
    I[4] = 3;
    I[5] = 6;
    I[6] = 8;
    I[7] = 4;
    I[8] = 5;

    d = 0;
    wl.clear();
    wr.clear();
}

void readInputCase2()
{
    N = 5;
    D = 4;
    isEven = (D % 2 == 0);
    I.resize(N);
    I[0] = 1;
    I[1] = 2;
    I[2] = 3;
    I[3] = 4;
    I[4] = 4;
    // I[5] = 6;
    // I[6] = 8;
    // I[7] = 4;
    // I[8] = 5;

    d = 0;
    wl.clear();
    wr.clear();
}


void buildInput(int seed)
{
    srand(seed);
    N = rand() % 30 + 10;
    D = rand() % (N-2) + 2;
    isEven = (D % 2 == 0);
    I.resize(N);
    for (int i=0; i<N; ++i) {
        I[i] = rand() % 200;
    }
    wl.clear();
    wr.clear();

    cout << "N=" << N << endl;
    cout << "D=" << D << endl;
}

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

void printWindow();
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
        cout << "INPUT=" << I[i] << endl;
        printWindow();

        if (i < D-1) continue;

        m2 = median2();
        cout << "MEDIAN2=" << m2 << endl;
        if (I[i+1] >= m2) d++;
    }

    return d;
}

void printWindow()
{
    auto it_l_begin = wl.begin();
    auto it_l_end = wl.end();

    cout << "WL: ";
    for(auto it = it_l_begin; it != it_l_end; ++it) {
        cout << (*it) << " ";
    }
    cout << endl;

    auto it_r_begin = wr.begin();
    auto it_r_end = wr.end();

    cout << "WR: ";
    for(auto it = it_r_begin; it != it_r_end; ++it) {
        cout << (*it) << " ";
    }
    cout << endl;
}

void testAdd()
{
    printWindow();
    for (int i=0; i<100; i++) {
        add(rand() % 100 + 100);
        printWindow();
    }
}

void testMedian()
{
    D = 10;
    for (int i=0; i<D; i++) {
        add(rand() % 100 + 100);
    }
    printWindow();
    cout << "MEDIAN2 = " << median2() << endl;
}

int main(int argc, char* argv[])
{
    //readInputCase1();
    buildInput(atoi(argv[1]));
    cout << solve() << endl;
    //testMedian();

    return 0;
}

