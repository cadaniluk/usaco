/*
ID: th3c0r11
TASK: hamming
LANG: C++14
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int n, b, d;

int distance(unsigned int a, unsigned int b)
{
	auto c = a ^ b;
	int ret = 0;
	while (c) {
		if (c & 0x1)
			++ret;
			c >>= 1;
	}

	return ret;
}

int main()
{
	ifstream in{"hamming.in"};
	ofstream out{"hamming.out"};

	in >> n >> b >> d;

	vector<unsigned int> values{0};

	for (unsigned int i = 1; i < pow(2, b) && values.size() < n; ++i) {
		bool distanceok = true;
		for (int j = 0; j < values.size(); ++j) {
			if (distance(i, values[j]) < d) {
				distanceok = false;
				break;
			}
		}
		if (distanceok)
			values.push_back(i);
	}

	for (int i = 0; i < values.size(); ++i) {
		if (i % 10 == 9 && i != 0 || i == values.size() - 1)
			out << values[i] << '\n';
		else
			out << values[i] << ' ';
	}
}