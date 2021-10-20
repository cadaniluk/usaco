/*
ID: th3c0r11
TASK: crypt1
LANG: C++14
*/

/* O(n^5), but n <= 9, so possibly feasible. */

#define NDEBUG
#include <bits/stdc++.h>

std::vector<int> digits;
int n;

template<std::size_t N>
struct Number {
	std::array<int, N> indices{};

	Number &operator++()
	{
		int i = N - 1;
		while (++indices[i] == digits.size() && i >= 0) {
			indices[i] = 0;
			--i;
		}

		return *this;
	}

	operator int() const
	{
		int ret = 0;

		for (int i = 0; i < N; ++i) {
			ret += digits[indices[N - i - 1]] * std::pow(10, i);
		}
		return ret;
	}
};

bool isValid(int num)
{
	while (num) {
		if (std::find(digits.begin(), digits.end(), num % 10) == digits.end())
			return false;
		num /= 10;
	}
	return true;
}

int numDigits(int i)
{
	int c = 0;
	while (i) {
		i /= 10;
		++c;
	}
	return c;
}

int main()
{
	std::ifstream in{"crypt1.in"};
	std::ofstream out{"crypt1.out"};

	in >> n;
	in.ignore(100, '\n');

	int digit;
	while (in >> digit) {
		digits.push_back(digit);
	}
	assert(n == digits.size());

	int numValid = 0;

	Number<3> first;
	for (int i = 0; i < n * n * n; ++first, ++i) {
			Number<2> last;
			for (int j = 0; j < n * n; ++last, ++j) {
				int firstInt = first;
				if (!isValid(firstInt * last))
					continue;
				auto p1 = firstInt * digits[last.indices[0]];
				auto p2 = firstInt * digits[last.indices[1]];
				if (!isValid(p1) || numDigits(p1) > 3)
					continue;
				if (!isValid(p2) || numDigits(p2) > 3)
					continue;
				++numValid;
				std::cout << firstInt << " " << last << '\n';
			}
	}

	out << numValid << '\n';
}
