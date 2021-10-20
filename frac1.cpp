/*
ID: th3c0r11
TASK: frac1
LANG: C++14
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

struct Fraction {
	int num, denom;
};

bool cmp(Fraction f1, Fraction f2)
{
	f1.num *= f2.denom;
	f2.num *= f1.denom;

	return f1.num < f2.num;
}

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main()
{
	ifstream in{"frac1.in"};
	ofstream out{"frac1.out"};

	int N;

	in >> N;

	std::vector<Fraction> fractions {{0,1}, {1, 1}};

	for (int denom = 1; denom <= N; ++denom) {
		for (int num = 1; num < denom; ++num) {
			if (gcd(num, denom) == 1) {
				fractions.push_back({num, denom});
			}
		}
	}

	std::sort(fractions.begin(), fractions.end(), cmp);

	for (const auto &i : fractions) {
		out << i.num << '/' << i.denom << '\n';
	}
}
