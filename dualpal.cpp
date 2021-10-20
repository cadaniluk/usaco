/*
ID: th3c0r11
TASK: dualpal
LANG: C++14
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

bool palindrome(const std::string &str)
{
    return std::equal(str.begin(), str.begin() + str.size() / 2, str.rbegin(), str.rbegin() + str.size() / 2);
}

std::string tobase(int base, int i)
{
    std::string ret;
    while (i) {
        ret += i % base + '0';
        i /= base;
    }
    return ret;
}

int main()
{
    std::ifstream in{"dualpal.in"};
    std::ofstream out{"dualpal.out"};

    int n, s;
    in >> n >> s;
    in.ignore(100, '\n');

    for (int i = s + 1, counter = 0; counter < n; ++i) {
        int palcounter = 0;
        bool ispal = false;
        for (int base = 2; base <= 10; ++base) {
            if (palindrome(tobase(base, i))) {
                ++palcounter;
                if (palcounter == 2) {
                    ispal = true;
                    ++counter;
                    break;
                }
            }
        }
        if (ispal)
            out << i << '\n';
    }
}