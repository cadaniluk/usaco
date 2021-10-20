/*
ID: th3c0r11
LANG: C++14
TASK: beads
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

enum bead { b = 'b', w = 'w', r = 'r' };

int main()
{
	std::ifstream in{"beads.in"};
	std::ofstream out{"beads.out"};

	int beads;
	in >> beads;
	in.ignore(100, '\n');

	std::string necklace;
	std::getline(in, necklace);

	std::vector<std::pair<bead, int>> chains;

	bead currBead = static_cast<bead>(necklace[0]);
	int trailingLength = 0;

	while (necklace[necklace.size() - trailingLength - 1] == currBead && trailingLength <= necklace.size() - 1)
		++trailingLength;
	std::cout << trailingLength << '\n';
	int currLen = trailingLength;
	for (int i = 0; i < necklace.size() - trailingLength; ++i) {
		if (necklace[i] == currBead)
			++currLen;
		else {
			chains.push_back({currBead, currLen});
			currBead = static_cast<bead>(necklace[i]);
			currLen = 1;
		}
	}
	chains.push_back({currBead, currLen});

	if (chains.size() == 1) {
		out << chains[0].second << '\n';
		return 0;
	}

	int longest = 0;

#define AT(i) ((i) % chains.size())
	for (int i = 0; i < chains.size(); ++i) {
		int first = 0;
		int second = 0;

		int firstOffset = 0;
		bead cmp = w;
		if (chains[i].first == w)
			cmp = chains[AT(i+1)].first;

		for ( ; chains[AT(i+firstOffset)].first == cmp || chains[AT(i+firstOffset)].first == chains[i].first; ++firstOffset)
			first += chains[AT(i+firstOffset)].second;
			
		for (int j = i + firstOffset; (chains[AT(j)].first == w || chains[AT(j)].first == chains[AT(i + firstOffset)].first) && AT(j) != i; ++j) {
			second += chains[AT(j)].second;
		}

		std::cout << first << " " << second << '\n';

		if (first + second > longest) {
			longest = first + second;
		}
	}

	out << longest << '\n';
}
