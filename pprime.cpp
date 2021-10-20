/*
ID: th3c0r11
LANG: C++14
TASK: pprime
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

long a, b;

bool isPrime(long l)
{
	for (long i = 2; i <= sqrt(l); ++i)
		if (l % i == 0)
			return false;
	return true;
}

size_t length(long x)
{
	size_t l = 1;

	while (x /= 10)
		++l;
	
	return l;
}

long numReverse(long l, size_t length)
{
	long ret = 0;

	for (size_t i = length; i >= 1; --i) {
		ret += (l % 10) * pow(10, i - 1);
		l /= 10;
	}

	return ret;
}

long evenPalindrome(long half)
{
	long halfLength = length(half);
	return half * pow(10, halfLength) + numReverse(half, halfLength);
}

long oddPalindrome(long half, long middleNum)
{
	long halfLength = length(half);
	return half * pow(10, halfLength + 1) + pow(10, halfLength) * middleNum + numReverse(half, halfLength);
}

std::vector<long> list;

int main()
{
	ifstream in{"pprime.in"};
	ofstream out{"pprime.out"};

	in >> a >> b;

	long firstHalf = 1;

	if (a <= 7) {
		list.push_back(7);
		if (a == 5)
			list.push_back(5);
	}

	for (long evenP = 0; evenP <= b; ++firstHalf, evenP = evenPalindrome(firstHalf)) {
		evenP = evenPalindrome(firstHalf);
		if (isPrime(evenP) && evenP >= a && evenP <= b)
			list.push_back(evenP);

		for (long i = 0, p = oddPalindrome(firstHalf, i); i < 10 && p <= b; ++i, p = oddPalindrome(firstHalf, i))
			if (isPrime(p) && p >= a && p <= b)
				list.push_back(p);
	}

	std::sort(list.begin(), list.end());

	for (auto i : list)
		out << i << '\n';
}
