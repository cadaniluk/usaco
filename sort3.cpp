/*
ID: th3c0r11
TASK: sort3
LANG: C++14
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
	ifstream in{"sort3.in"};
	ofstream out{"sort3.out"};

	int N;
	std::vector<int> seq;

	int overall[4] {0};	// overall[x] := number of x's in seq
	int oneArea[4] {0}; // oneArea[x] := number of x's in the one area
	int twoArea[4] {0}; // twoArea[x] := number of x's in the two area
	int threeArea[4] {0}; // threeArea[x] := number of x's in the three area

	in >> N;
	for (int i = 0; i < N; ++i) {
		int x;
		in >> x;
		++overall[x];
		seq.push_back(x);
	}

	int i = 0;
	for ( ; i < overall[1]; ++i)
		++oneArea[seq[i]];
	for ( ; i < overall[1] + overall[2]; ++i)
		++twoArea[seq[i]];
	for ( ; i < overall[1] + overall[2] + overall[3]; ++i)
		++threeArea[seq[i]];

	int directSwaps = min(oneArea[2], twoArea[1]) +
		min(twoArea[3], threeArea[2]) + min(threeArea[1], oneArea[3]);

	int misplaced = abs(oneArea[2] - twoArea[1]) +
		abs(twoArea[3] - threeArea[2]) + abs(threeArea[1] - oneArea[3]);

	out << directSwaps + misplaced / 3 * 2 << '\n';
}
