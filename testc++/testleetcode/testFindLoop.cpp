/*************************************************************************
	> File Name: testFindLoop.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 10 Jan 2017 04:54:25 AM EST
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <string>
#include<iostream>
#include <vector>

using namespace std;

class Solution{
public:
    inline int getnext(int cur, vector<int>& nums){
        int nidx = cur + nums[cur];
        if(nidx < 0){
            nidx += nums.size();
        }
        if(nidx >= nums.size()){
            nidx -= nums.size();
        }
        return nidx;
    }
    bool circularArrayLoop1(vector<int>& nums){
        vector<int> arrmarks;
        arrmarks.resize(nums.size());
        for(size_t idx=0; idx< arrmarks.size(); idx++){
            arrmarks[idx] = 0;
        }
        int st = 0;
        int lcnt = 1;
        bool isfound = false;
        while(true){
            size_t idx;
            for(idx=st; idx< arrmarks.size(); idx++){
                if(arrmarks[st] == 0) break;
            }
            if(idx == arrmarks.size()) break;
            arrmarks[st] = lcnt;
            int nidx = st;
            int lst = 0;
            while(true){
                nidx = getnext(nidx, nums);
                if(arrmarks[nidx] != 0){
                    if(arrmarks[nidx] < lcnt) break;
                    if(arrmarks[nidx] == lcnt){
                        if(getnext(nidx, nums) == nidx) break;
                        else{
                            isfound = true;
                            lst = nidx;
                            break;
                        }
                    }
                }
                else{
                    arrmarks[nidx] = lcnt;
                }
            }
            if(isfound){
                printf("%d", lst);
                nidx = getnext(lst, nums);
                while(nidx != lst){
                    printf("->%d", nidx);
                    nidx = getnext(nidx, nums);
                }
                printf("->%d\n", lst);
                break;
            }
            else{
                lcnt ++;
            }
        }
        return isfound;
    }
    
    bool circularArrayLoop2(vector<int>& nums){
        int size = nums.size();
        bool isfound = false;
        int lst = 0;
        for(int st = 0; st < size - 1; st ++){
            int npos = st;
            int tolcnt = 0;
            int tolnum = 0;
            
            while(true){
                int curnum = nums[npos] % size;
                if(curnum == 0) break;
                tolnum += curnum;
                tolnum = tolnum % size;
                if(tolnum == 0){
                    isfound = true;
                    lst = npos;
                    break;
                }
                int nnpos = st + tolnum;
                if(nnpos < 0) nnpos += size;
                if(nnpos >= size) nnpos -= size;
                if(nnpos < st) break;
                tolcnt ++;
                if(tolcnt == nums.size() - st){
                    isfound = true;
                    lst = npos;
                    break;
                }
                npos = nnpos;
            }
            if(isfound){
                break;
            }
        }
        if(isfound){
            printf("%d", lst);
            int nidx = getnext(lst, nums);
            while(nidx != lst){
                printf("->%d", nidx);
                nidx = getnext(nidx, nums);
            }
            printf("->%d\n", lst);
             return true; 
        }
        return false;
    }

    inline int getnext(int st, int stp, int size){
        int ret = st + stp;
        if(ret < 0) return ret + size;
        if(ret >= size) return ret - size;
        return ret;
    }
    void printloop(int lst, vector<int>& nums){
        printf("%d", lst);
        int nidx = getnext(lst, nums);
        while(nidx != lst){
            printf("->%d", nidx);
            nidx = getnext(nidx, nums);
        }
        printf("->%d\n", lst);
    }

    bool circularArrayLoop3(vector<int> &nums){
        int size = nums.size();
        int st = 0;
        bool bforward = false;
        bool bfound = false;
        int lst = 0;

        for(int st =0; st < size; st++){
            if(nums[st] < 0) bforward = false;
            else bforward = true;
            int pidx = st;
            
            while(true){
                if(bforward && nums[pidx] < 0 || !bforward && nums[pidx] > 0) break;
                int nidx = getnext(pidx, nums[pidx], size);
                if(nidx == pidx){
                    //fall into single loop.
                    break;
                }
                if(nidx == st){
                    bfound = true;
                    lst = st;
                    break;
                }
                pidx = nidx;
            }
        }
        if(bfound){
            printloop(lst, nums);
             return true; 
        }
        return false;
    }

    bool circularArrayLoop4(vector<int> &nums){
        vector<int> tolnums(nums);
        int size = tolnums.size();
        bool bfound = false;
        int lst = 0;
        for(int idx=tolnums.size() -1; idx > -1; idx--){
            int curstp = tolnums[idx];
            curstp = curstp % size;
            if(curstp < 0) continue;
            if(curstp == 0){
                tolnums[idx] = 0;
                 continue;
            }
            int nidx = getnext(idx, curstp, size);
            if(tolnums[nidx] < 0){
                continue;
            }
            tolnums[idx] += tolnums[nidx];
            tolnums[idx] = tolnums[idx] % size;
            if(tolnums[idx] == 0){
                bfound = true;
                lst = idx;
                break;
            }
        }
        if(bfound){
            printloop(lst, nums);
            return true;
        }
        for(int idx=0; idx < size; idx++){
            int curstp = tolnums[idx];
            curstp = curstp % size;
            if(curstp > 0) continue;
            if(curstp == 0){
                tolnums[idx] = 0;
                continue;
            }
            int nidx = getnext(idx, curstp, size);
            if(tolnums[nidx] > 0){
                continue;
            }
            tolnums[idx] += tolnums[nidx];
            tolnums[idx] = tolnums[idx] % size;
            if(tolnums[idx] == 0){
                bfound = true;
                lst = idx;
                break;
            }
            
        }
        if(bfound){
            printloop(lst, nums);
            return true;
        }
        
        return false;
    }

    bool circularArrayLoop(vector<int> &nums){
        int size = nums.size();
        bool bfound = false;
        int lst = 0;
        int st = 0;
        for(int st = 0; st < size; st++){
            if(nums[st] == 0) continue;
            int bidx = st;
            int fidx = st;
            while(true){
                bidx = getnext(bidx, nums[bidx], size);
                if(nums[st] * nums[bidx] < 0) break;
                fidx = getnext(fidx, nums[fidx], size);
                if(nums[st] * nums[fidx] < 0) break;
                fidx = getnext(fidx, nums[fidx], size);
                if(nums[st] * nums[fidx] < 0) break;
                if(bidx == fidx){
                    if(bidx == getnext(bidx, nums[bidx], size)){
                        break;
                    }
                    bfound = true;
                    lst = bidx;
                    break;
                }
            }
            if(bfound){
                printloop(lst, nums);
                return true;
            }
            else{
                //reset(st, nums);
                int stval = nums[st];
                int idx = getnext(st, nums[st], size);
                nums[st] = 0;
                while(stval * nums[idx] > 0){
                    int nidx = getnext(idx, nums[idx], size);
                    nums[idx] = 0;
                    idx = nidx;
                }
            }
        }
    }
};

int main(int argc, char* argv[])
{
    Solution a;
    int test1[] = {2, -1, 1, 2, 2};
    vector<int> nums1(test1, test1 + 5);
    a.circularArrayLoop(nums1);
    int test2[] = {-1, 2};
    vector<int> nums2(test2, test2 + 2);
    a.circularArrayLoop(nums2);
    if(argc > 1){
        string strtmp(argv[1]);
        vector<int> argnums;
        char *argtest = const_cast<char*>(strtmp.c_str());
        char *st = argtest;
        while(true){
            char* seppos = strchr(st, ' ');
            int num;
            sscanf(st, "%d", &num);
            argnums.push_back(num);
            if(seppos == NULL) break;
            st = seppos + 1;
        }
        a.circularArrayLoop(argnums);
    }
    return 0;
}
