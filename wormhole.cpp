/*
ID: th3c0r11
TASK: wormhole
LANG: C++14
*/

/* entry and exit hole needed, so every included hole has another hole at the same height.
 *  */

#include <bits/stdc++.h>

int n;
std::vector<std::pair<long long, long long>> coords;
std::vector<int> partners;

int iterate()
{
	int first = 0;
	while (partners[first] != -1 && first != coords.size())
		++first;

	if (first == coords.size()) {
		// check if cyclic
		for (int start = 0; start < partners.size(); ++start) {
			int curr = start;
			for (int i = 0; i < n; ++i) {
				long long minX = std::numeric_limits<long long>::max();
				int next = -1;
				for (int j = 0; j < coords.size(); ++j) {
					if (coords[j].second == coords[partners[curr]].second && coords[j].first > coords[partners[curr]].first && coords[j].first < minX) {
						next = j;
						minX = coords[j].first;
					}
				}
				if (next == -1)
					break;

				curr = next;
				if (curr == start)
					return 1;
			}
		}

		for (int i = 0; i < partners.size(); ++i) {
			std::cout << '(' << i << ',' << partners[i] << ");";
		}
		std::cout << '\n';
		return 0;
	}

	int matches = 0;
	for (int i = first + 1; i < coords.size(); ++i) {
		if (partners[i] == -1) {
			partners[first] = i;
			partners[i] = first;
			matches += iterate();
			partners[i] = -1;
			partners[first] = -1;
		}
	}

	return matches;
}

int main()
{
	std::ifstream in{"wormhole.in"};
	std::ofstream out{"wormhole.out"};

	in >> n;
	in.ignore(100, '\n');

	for (int i = 0; i < n; ++i) {
		std::pair<long long, long long> pair;
		in >> pair.first >> pair.second;
		in.ignore(100, '\n');
		coords.push_back(pair);
	}

	partners.resize(n, -1);
	out << iterate() << '\n';
}