/*
ID: th3c0r11
TASK: skidesign
LANG: C++14
*/

#include <bits/stdc++.h>

// get pairs that exceed 17, sort non-increasingly, alter heights optimally by minimal amounts, always */

int n;
std::vector<int> elevation;
std::vector<int> change;

int main()
{
	std::ifstream in{"skidesign.in"};
	std::ofstream out{"skidesign.out"};

	in >> n;
	in.ignore(100, '\n');
	change.resize(n, 0);

	for (int i = 0; i < n; ++i) {
		int e;
		in >> e;
		elevation.push_back(e);
	}

	int minCost = std::numeric_limits<int>::max();
	for (int i = 0; i <= 83; ++i) {
		int cost = 0;
		for (int j = 0; j < elevation.size(); ++j) {
			if (elevation[j] < i)
				cost += (i - elevation[j]) * (i - elevation[j]);
			else if (elevation[j] > i + 17)
				cost += (elevation[j] - (i + 17)) * (elevation[j] - (i + 17));
		}
		if (cost < minCost)
			minCost = cost;
	}

	out << minCost << '\n';
}