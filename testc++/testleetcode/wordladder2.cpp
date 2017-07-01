///https://leetcode.com/problems/word-ladder-ii/#/description
#include "stdafx.h"
using namespace::std;



class Solution {
public:

	string begw;
	string endw;
	vector<string> *pvec;
	vector<bool> passed;

	vector<set<int>> backtrace;
	vector<vector<int>> allinterns;
	int endidx;
	vector<int> sequence;


	bool isneig(string& s1, string &s2){
		int cnt = 0;
		for (int i = 0; i < s1.size(); i++){
			if (s1[i] != s2[i]){
				cnt++;
				if (cnt > 1) break;
			}
		}
		return cnt == 1;
	}

	vector<int> getNeig(string& cur){
		vector<string> &vec = *pvec;
		vector<int> ret;
		for (int i = 0; i < vec.size(); i++){
			if (passed[i]) continue;
			if (isneig(cur, vec[i])) ret.push_back(i);
		}
		return ret;
	}

	//find all path form start to end.
	bool findEnd_e(string & cur, vector<vector<string>> &outarr){
		outarr.clear();
		vector<string> &vec = *pvec;

		if (cur == endw){
			outarr.push_back(vector<string>());
			outarr.back().push_back(cur);
			return true;
		}
		vector<int> neigs = getNeig(cur);
		for (int i = 0; i < neigs.size(); i++){
			vector<vector<string>> tmparr;
			if (findEnd(vec[neigs[i]], tmparr)){
				for (int j = 0; j < tmparr.size(); j++){
					outarr.push_back(tmparr[j]);
				}
			}
		}
		if (outarr.size() > 0){
			for (int i = 0; i < outarr.size(); i++){
				outarr[i].push_back(cur);
			}
			return true;
		}
		else{
			return false;
		}
	}

	void process(){
		vector<set<int>> &bt = backtrace;
		vector<vector<int>> &seqs = allinterns;
		vector<int> &seq = sequence;
		set<int> &nums = bt[seq.back()];
		if (nums.size() == 0){
			//dump one sequence.
			seqs.push_back(vector<int>());
			vector<int> &s = seqs.back();
			for (auto rit = seq.rbegin(); rit != seq.rend(); rit++){
				s.push_back(*rit);
			}
		}
		else{
			for (auto it = nums.begin(); it != nums.end(); it++){
				seq.push_back(*it);
				process();
				seq.pop_back();
			}
		}
	}
	//find all shortest path from start to end.
	bool findEnd(string& cur, vector <vector<string>> &outarr){
		vector<string> &vec = *pvec;
		vector<int> neigs = getNeig(cur);
		for (auto it = neigs.begin(); it != neigs.end(); it++){
			if (vec[*it] == endw){
				outarr.push_back(vector<string>());
				outarr.back().push_back(begw);
				outarr.back().push_back(endw);
				return true;
			}
		}

		set<int> curfloor(neigs.begin(), neigs.end());
		int level = 0;
		backtrace.resize(vec.size());
		endidx = -1;
		
		//generate backtrace.
		while (true){
			//step next floor.
			for (auto it = curfloor.begin(); it != curfloor.end(); it++){
				passed[*it] = true;
			}
			set<int> nextfloor;
			for (auto it = curfloor.begin(); it != curfloor.end(); it++){
				vector<int> tmp = getNeig(vec[*it]);
				for (auto nit = tmp.begin(); nit != tmp.end(); nit++){
					backtrace[*nit].insert(*it);
					nextfloor.insert(*nit);
				}
			}
			if (nextfloor.size() == 0){
				break;
			}
			curfloor = nextfloor;
			level++;

			//check if endw in this floor.
			for (set<int>::iterator it = curfloor.begin(); it != curfloor.end(); it++){
				if (vec[*it] == endw){
					endidx = *it;
					break;
				}
			}
			if (endidx != -1){
				break;
			}

		}

		if (endidx == -1) return false;
		//use backtrace to gather all sequences.
		sequence.push_back(endidx);
		process();
		for (auto it = allinterns.begin(); it != allinterns.end(); it++){
			outarr.push_back(vector<string>());
			vector<string> &arr = outarr.back();
			arr.push_back(begw);
			for (auto itt = it->begin(); itt != it->end(); itt++){
				arr.push_back(vec[*itt]);
			}
		}
		return true;
	}

	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
		begw = beginWord;
		endw = endWord;
		pvec = &wordList;
		passed.resize(wordList.size());
		for (int i = 0; i < passed.size(); i++){
			passed[i] = false;
		}

		vector<vector<string>> ret;
		findEnd(begw, ret);
		return ret;
	}
};

const char * testlist[] = { "hit", "cog", "hot", "dot", "dog", "lot", "log", "cog" };
const char * expectlist[][5] = { { "hit", "hot", "dot", "dog", "cog" },
							{ "hit", "hot", "lot", "log", "cog" } };

template<typename T>
bool cmpvec(T r1, T r2)
{
	if (r1.size() != r2.size()){
		return false;
	}
	int k = 0;
	for (; k < r1.size(); k++){
		if (! cmpvec(r1[k], r2[k])){
			break;
		}
	}
	if (k != r1.size()){
		return false;
	}
	return true;
}
bool cmpvec(char r1, char r2)
{
	return r1 == r2;
}

bool cmplistlist(vector<vector<string>> &inst1, vector<vector<string>> &inst2)
{
	if (inst1.size() != inst2.size()) return false;
	for (int i = 0; i < inst1.size(); i++){
		int j = 0;
		for (; j < inst2.size(); j++){
			if (!cmpvec(inst1[i], inst2[j])) break;
		}
		if (j == inst2.size()){
			return false;
		}
	}
	return true;
}
static void discardchar(){
	getchar();
}
TEST(wordladder2, first)
{
	Solution s;
	const char *beginword = testlist[0];
	const char *endword = testlist[1];
	unsigned arrlen = sizeof(testlist) / sizeof(char *);
	vector<string> wordlist(&testlist[2], &testlist[arrlen]);
	vector<vector<string>> outputs = s.findLadders(beginword, endword, wordlist);

	vector<vector<string>> expects;
	for (int i = 0; i < 2; i++){
		expects.push_back(vector<string>(&expectlist[i][0], &expectlist[i][5]));
	}
	EXPECT_TRUE(cmplistlist(expects, outputs));
	atexit(discardchar);
}