// testc++.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <set>

using namespace std;
vector<vector< vector<vector<int> >* > > g_Buf;
vector<vector<int>>* gensubsets(unsigned cap, unsigned len)
{
	if (g_Buf[cap - 1][len - 1] != NULL) return g_Buf[cap - 1][len - 1];
	g_Buf[cap - 1][len - 1] = new vector<vector<int> >();
	vector<vector<int> > & sets = *g_Buf[cap - 1][len - 1];
	if (len == 1){
		vector<int> tmp;
		tmp.resize(1);
		for (unsigned idx = 0; idx < cap; idx++){
			tmp[0] = idx;
			sets.push_back(tmp);
		}
		return g_Buf[cap - 1][len - 1];
	}
	else if (cap == len){
		vector<int> tmp;
		for (unsigned idx = 0; idx < len; idx++){
			tmp.push_back(idx);
		}
		sets.push_back(tmp);
		return g_Buf[cap - 1][len - 1];

	}

	vector<vector<int>> & sets1 = *gensubsets(cap - 1, len);
	vector<vector<int>> &sets2 = *gensubsets(cap - 1, len - 1);
	sets.insert(sets.end(), sets1.begin(), sets1.end());
	for (auto it = sets2.begin(); it != sets2.end(); it++){
		vector<int> tmp(it->begin(), it->end());
		tmp.resize(len);
		tmp.at(len - 1) = cap - 1;
		sets.push_back(tmp);
	}
	return g_Buf[cap - 1][len - 1];
}

void rearange(int *a, unsigned alen, int *b, unsigned blen)
{
	int *larr = a;
	unsigned llen = alen;
	int *sarr = b;
	unsigned slen = blen;
	if (alen < blen){
		larr = b;
		llen = blen;
		sarr = a;
		slen = alen;
	}
	int ssum = 0;
	for (unsigned idx = 0; idx < slen; idx++){
		ssum += sarr[idx];
	}
	int lsum = 0; 
	for (unsigned idx = 0; idx < llen; idx++){
		lsum += larr[idx];
	}
	int medsum = (ssum + lsum) / 2;
	int tgt = medsum - ssum;
	int mindelta = tgt;
	unsigned minlen = 0;
	unsigned minidx = 0;
	unsigned minjdx = 0;
	for (unsigned len = 1; len < slen + 1; len++){
		int curdelta = tgt;
		unsigned sidx = 0;
		unsigned lidx = 0;
		vector<vector<int>> &sset = *gensubsets(slen, len);
		vector<vector<int>> &lset = *gensubsets(llen, len);
		for (unsigned idx = 0; idx < sset.size(); idx++){
			for (unsigned jdx = 0; jdx < lset.size(); jdx++){
				vector<int>& ssubset = sset[idx];
				vector<int>& lsubset = lset[jdx];
				int ssubsum = 0;
				int lsubsum = 0;
				for (unsigned k = 0; k < ssubset.size(); k++){
					ssubsum += sarr[ssubset[k]];
					lsubsum += larr[lsubset[k]];
				}
				int delta = medsum - ssum + ssubsum - lsubsum;
				if (delta < 0) delta = -delta;
				if (delta < curdelta){
					curdelta = delta;
					sidx = idx;
					lidx = jdx;
				}
			}
		}

		cout << len<< ": "<< curdelta<< endl;
		if (curdelta < mindelta){
			mindelta = curdelta;
			minlen = len;
			minidx = sidx;
			minjdx = lidx;
		}
	}
	vector<int> ssubset = gensubsets(slen, minlen)->at(minidx);
	vector<int> lsubset = gensubsets(llen, minlen)->at(minjdx);
	for (unsigned idx = 0; idx < ssubset.size(); idx++){
		unsigned sidx = ssubset[idx];
		unsigned lidx = lsubset[idx];
		unsigned tmp = sarr[sidx];
		sarr[sidx] = larr[lidx];
		larr[lidx] = tmp;
	}
}

static int a_1[] = {2, 3, 9};
static int b_1[] = {7, 7, 4, 0, 9, 9};
void test_rearange()
{
	g_Buf.resize(100);
	for (unsigned idx = 0; idx < g_Buf.size(); idx++){
		g_Buf[idx].resize(100);
		for (unsigned jdx = 0; jdx < g_Buf[idx].size(); jdx++){
			g_Buf[idx][jdx] = NULL;
		}
	}

	unsigned alen = 3;
	unsigned blen = 6;
	rearange(a_1, alen, b_1, blen);
	for (unsigned idx = 0; idx < alen; idx++){
		cout << a_1[idx] << " ";
	}
	cout << endl;
	for (unsigned idx = 0; idx < blen; idx++){
		cout << b_1[idx] << " ";
	}
	cout << endl;
}

TEST(aa, bb)
{
	test_rearange();
}