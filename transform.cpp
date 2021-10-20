/*
ID: th3c0r11
TASK: transform
LANG: C++14
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

int n;

std::vector<char> deg90(const std::vector<char> &a)
{
    std::vector<char> ret;
    int x = 0, y = n - 1;
    for (int i = 0; i < a.size(); ++i) {
        ret.push_back(a[y * n + x]);
        if (y == 0) {
            ++x;
            y = n - 1;
        } else
            --y;
    }
    return ret;
}

std::vector<char> reflect(const std::vector<char> &a)
{
    std::vector<char> ret;

    for (int i = 0; i < n; ++i) {
        for (int j = n - 1; j >= 0; --j) {
            ret.push_back(a[i * n + j]);
        }
    }

    return ret;
}

int main()
{
    std::ifstream in{"transform.in"};
    std::ofstream out{"transform.out"};

    in >> n;
    in.ignore(100, '\n');

    std::vector<char> pattern;

    for (int i = 0; i < n; ++i) {
        std::string str;
        std::getline(in, str);
        for (char c : str)
            pattern.push_back(c);
    }

    std::vector<char> result;

    for (int i = 0; i < n; ++i) {
        std::string str;
        std::getline(in, str);
        for (char c : str)
            result.push_back(c);
    }

    if (deg90(pattern) == result)
        out << "1\n";
    else if (deg90(deg90(pattern)) == result)
        out << "2\n";
    else if (deg90(deg90(deg90(pattern))) == result)
        out << "3\n";
    else if (reflect(pattern) == result)
        out << "4\n";
    else if (deg90(reflect(pattern)) == result || deg90(deg90(reflect(pattern))) == result || deg90(deg90(deg90(reflect(pattern)))) == result)
        out << "5\n";
    else if (pattern == result)
        out << "6\n";
    else
        out << "7\n";
}