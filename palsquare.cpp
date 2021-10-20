/*
ID: th3c0r11
TASK: palsquare
LANG: C++14
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

int base;

bool palindrome(const std::string &str)
{
    return std::equal(str.begin(), str.begin() + str.size() / 2, str.rbegin(), str.rbegin() + str.size() / 2);
}



static std::array<char, 20> list { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

struct BaseInt {
    int value;
    std::array<int, 10> repr;

    bool operator<=(int n)
    {
        return value <= n;
    }

    BaseInt &operator++()
    {
        ++value;
        int i = 9;
        while (++repr[i] == base) {
            repr[i] = 0;
            --i;
        }

        return *this;
    }

    operator std::string()
    {
		std::string ret;
		int i = 0;
		for ( ; repr[i] == 0; ++i);

		for (; i < repr.size(); ++i) {
			ret += list[repr[i]];
		}
        
        return ret;
    }

    std::string squareVal()
    {
        int square = value * value;
        std::string ret;
        while (square) {
            ret += list[square % base];
            square /= base;
        }
        return ret;
    }
};

int main()
{
    std::ifstream in{"palsquare.in"};
    std::ofstream out{"palsquare.out"};

    in >> base;
    in.ignore(100, '\n');

    for (BaseInt i{1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}}; i <= 300; ++i) {
        if (palindrome(i.squareVal()))
            out << std::string(i) << ' ' << i.squareVal() << '\n';
    }
}