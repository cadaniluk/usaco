/*
ID: th3c0r11
TASK: barn1
LANG: C++14
*/

/* BTW: this is the first USACO problem i solved first try! */ 

#include <bits/stdc++.h>

int main()
{
    std::ifstream in{"barn1.in"};
	std::ofstream out{"barn1.out"};

	int boards, stalls, cows;

	in >> boards >> stalls >> cows;
	in.ignore(100, '\n');

	std::vector<int> occupiedStalls;
	for (int i = 0; i < cows; ++i) {
		std::string line;
		std::getline(in, line);
		occupiedStalls.push_back(std::atoi(line.data()));
	}

	std::sort(occupiedStalls.begin(), occupiedStalls.end());

	// total number of stalls blocked (minimal)

	if (boards >= cows) {
		out << cows << '\n';
		return 0;
	}

	std::vector<int> gapLengths;
	for (int i = 1; i < occupiedStalls.size(); ++i)
		gapLengths.push_back(occupiedStalls[i] - occupiedStalls[i - 1] - 1);
	assert(gapLengths.size() == occupiedStalls.size() - 1);
	std::sort(gapLengths.begin(), gapLengths.end());
	// sort by length

	int left = cows - boards;
	int blocked = cows;
	int i = 0;

	while (left--) {
		blocked += gapLengths[i++];
	}

	out << blocked << '\n';
}