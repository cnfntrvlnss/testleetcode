#include <string>
#include <iostream>

using namespace::std;
class Solution {
    public:
    inline bool isalphanum(char a){
        if(a>=48 && a<=57 || a>=65 && a<=122) return true;
        if(a != '-') return true;
        return false;

    }
    string licenseKeyFormatting(string S, int K) {
        string tmpS;
        int tokcnt = 0;
        for(size_t idx=0; idx < S.size(); idx++){
            if(isalphanum(S[idx])){
                tmpS.push_back(S[idx]);
                tokcnt++;
                if(tokcnt == K){
                    tmpS.push_back('-');
                    tokcnt = 0;
                }
            }
        }
        if(tmpS[tmpS.size() - 1] == '-'){
            tmpS.resize(tmpS.size() - 1);
            return tmpS;
        }
        else if(tmpS.size() < K){
            return tmpS;
        }
        else{
            int remcnt = 0;
            for(int i=2; i< K + 1; i++){
                if(tmpS[tmpS.size() - i] == '-'){
                    remcnt = i -1;
                    break;
                }
            }
            cout<< tmpS<< " remcnt: "<< remcnt << endl;
            int shiftcnt = K - remcnt;
            for(size_t idx=K; idx < tmpS.size(); idx += K + 1){
                for(int cnt=0; cnt < shiftcnt; cnt++){
                    tmpS[idx - cnt] = tmpS[idx - cnt - 1];
                }
                tmpS[idx - shiftcnt] = '-';
            }
            return tmpS;
        }
    }
};

int main()
{
    string test1 = "2-4A0r7-4k";
    Solution s;
    string ret = s.licenseKeyFormatting(test1, 4);
    cout<< ret << endl;
    string test2 = "a0001afds-";
    ret = s.licenseKeyFormatting(test2, 4);
    cout << ret <<endl;
    return 0;
}
