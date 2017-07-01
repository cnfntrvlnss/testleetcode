#include "stdafx.h"

#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <list>

using namespace::std;
/**
* Definition for undirected graph.
*/
struct UndirectedGraphNode {
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) {};

};

bool getarr_ex(const char*&st, vector<int>&arr, const char*tokseps = ", ", const char *lineseps="#", const char *terms = "}")
{
	arr.clear();
	char seps[50];
	_snprintf(seps, 50, "%s%s%s", tokseps, lineseps, terms);
	char seps1[50];
	_snprintf(seps1, 50, "%s%s", lineseps, terms);
	while (strchr(seps, *st) != NULL){
		if (strchr(terms, *st) != NULL) return false;
		st++;
	}
	while (true){
		int num;
		assert(sscanf(st, "%d", &num) == 1);
		arr.push_back(num);
		while (strchr(seps, *st) == NULL) st++;
		bool bexit = false;
		while (strchr(seps, *st) != NULL){
			if (strchr(seps1, *st) != NULL) {
				bexit = true;
				break;
			}
			st++;
		}
		if (bexit){
			break;
		}
	}
	return true;
}

/**
* use BFS to transver graph, and use hashtable to save transered nodes.
*/
class Solution {
public:
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		if (node == NULL) return NULL;
		map<int, UndirectedGraphNode*> graphhash;
		list<UndirectedGraphNode*> pendings;
		graphhash[node->label] = new UndirectedGraphNode(node->label);
		pendings.push_back(node);
		UndirectedGraphNode *ret = graphhash[node->label];;

		while (!pendings.empty()){
			UndirectedGraphNode *cur = pendings.front();	
			pendings.pop_front();
			//visit cur.
			UndirectedGraphNode *ccur = graphhash[cur->label];
			for (auto it = cur->neighbors.begin(); it != cur->neighbors.end(); it++){
				if (graphhash.find((*it)->label) == graphhash.end()){
					graphhash[(*it)->label] = new UndirectedGraphNode((*it)->label);
					pendings.push_back(*it);
				}
				ccur->neighbors.push_back(graphhash[(*it)->label]);
			}
		}

		return ret;
	}

	UndirectedGraphNode *constructGraph(const char*present){
		const char *st = present + 1;
		//map<int, vector<int>> graphoj;
		map<int, UndirectedGraphNode*> graphhash;
		UndirectedGraphNode *graph = NULL;
		vector<int> arr;
		while (getarr_ex(st, arr)){
			for (size_t idx = 0; idx < arr.size(); idx++){
				if (graphhash.find(arr[idx]) == graphhash.end()){
					graphhash[arr[idx]] = new UndirectedGraphNode(arr[idx]);
				}
			}
			if (graph == NULL){
				graph = graphhash[arr[0]];
			}
			for (size_t idx = 1; idx < arr.size(); idx++){
				UndirectedGraphNode * neighbor = graphhash[arr[idx]];
				graphhash[arr[0]]->neighbors.push_back(neighbor);
				if(graphhash[arr[0]]->label != neighbor->label) neighbor->neighbors.push_back(graphhash[arr[0]]); // note that symetric connection.
			}
		}
		return graph;
	}
	string serializeGraph(UndirectedGraphNode *graph){
		map<int, UndirectedGraphNode*> graphhash;		
		char tmpline[1024];
		unsigned curlen = 0;
		tmpline[0] = '\0';
		list<UndirectedGraphNode*>  pendnodes;
		pendnodes.push_back(graph);
		while (!pendnodes.empty()){
			UndirectedGraphNode *cur = pendnodes.front();
			pendnodes.pop_front();
			vector<int> unneighbors;
			for (auto it = cur->neighbors.begin(); it != cur->neighbors.end(); it++){
				if (graphhash.find((*it)->label) == graphhash.end()){
					unneighbors.push_back((*it)->label);
					pendnodes.push_back(*it);
				}
			}
			if (unneighbors.size() > 0){
				if (curlen != 0) curlen += _snprintf(tmpline + curlen, 1024 - curlen, "#");
				curlen += _snprintf(tmpline + curlen, 1024 - curlen, "%d", cur->label);
				for (auto it = unneighbors.begin(); it != unneighbors.end(); it++){
					curlen += _snprintf(tmpline + curlen, 1024 - curlen, ",%d", *it);
				}
			}
			graphhash[cur->label] = cur;
		}
		return tmpline;
	}
};

const char *testtxt = "{0,1,2#1,2#2,2}";
const char *testtxt1 = "{0,1#1,2#2,2}";
TEST(DISABLED_clonegraph, first){
	Solution s;
	UndirectedGraphNode * graph = s.constructGraph(testtxt1);
	string ret = s.serializeGraph(s.cloneGraph(graph));
	cout << "debug: " << ret << endl;
	getchar();
}