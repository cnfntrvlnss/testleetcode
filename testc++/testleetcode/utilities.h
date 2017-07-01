#include <vector>

static bool getarr(const char *&st, std::vector<int> &arr)
{
	arr.clear();
	while (strchr(" \n", *st) != NULL){
		if (*st == '\0') return false;
		st++;
	}

	while (true){
		const char *ed = st + 1;
		while (strchr(" \n", *ed) == NULL) ed++;
		int num;
		sscanf(st, "%d", &num);
		arr.push_back(num);
		if (*ed != ' ')break;
		st = ed + 1;
		while (*st == ' ') st++;
		if (strchr("\n", *st) != NULL) break;
	}
	return true;
}

