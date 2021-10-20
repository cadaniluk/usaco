/*
ID: th3c0r11
TASK: ariprog
LANG: C++14
*/

#include <bits/stdc++.h>
using namespace std;

int nMax, m;
std::unordered_set<int> bisquares;

int main()
{
	ifstream in{"ariprog.in"};
	ofstream out{"ariprog.out"};

	in >> nMax >> m;

	for (int p = 0; p <= m; ++p) {
		for (int q = p; q <= m; ++q) {
			bisquares.insert(p*p+q*q);
		}
	}
	
	int matches = 0;
	for (int b = 1; b <= m*m; ++b) {
		for (int a = 0; a <= m*m; ++a) {
			bool sequenceOK = true;
			for (int n = 0, value = a; n < nMax; ++n) {
				if (bisquares.find(value) == bisquares.end()) {
					sequenceOK = false;
					break;
				}
				value += b;
			}
			if (sequenceOK) {
				++matches;
				out << a << ' ' << b << '\n';
			}
		}
	}

	if (matches == 0) {
		out << "NONE\n";
	}
}
