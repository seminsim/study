class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        vector<string> cv(numRows);
        bool forward = true;
        int row = 0;
        int len = s.length();
        for (int i=0; i<len; ++i) {
            cv[row].push_back(s[i]);
            row += forward ? 1 : -1;
            if (row == numRows) { row-=2; forward=false; }
            else if (row == -1) { row=1; forward=true; }
        }

        string ret;
        for (const auto& c : cv) ret += c;
        return ret;
    }
};