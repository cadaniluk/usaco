/*
ID: th3c0r11
LANG: C++14
TASK: numtri
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define LEFT(i, r) (i + r + 1)
#define RIGHT(i, r) (i + r + 2)
#define ROW(n) (n * (n + 1) / 2)

int main()
{
	ifstream in{"numtri.in"};
	ofstream out{"numtri.out"};

	std::vector<int> triangle;

	int R;
	in >> R;

	triangle.reserve(R * (R + 1) / 2);

	int node;
	while (in >> node) {
		triangle.push_back(node);
	}

	for (int r = R - 2; r >= 0; --r) {
		for (int i = ROW(r); i <= ROW(r) + r; ++i) {
			triangle[i] += max(triangle.at(LEFT(i, r)),
				triangle[RIGHT(i, r)]);
		}
	}

	out << triangle.front() << '\n';
}
