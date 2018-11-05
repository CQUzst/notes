class Solution {
public:
    string toHex(int num) {
        string res = "";
        for (int i = 0; num && i < 8; ++i) {
            int t = num & 0xf;
            if (t >= 10) 
                res = char('a' + t - 10) + res;
            else 
                res = char('0' + t) + res;
            num >>= 4;
        }
        return res.empty() ? "0" : res;
    }
};