/*
ID: th3c0r11
TASK: combo
LANG: C++14
*/

#include <bits/stdc++.h>

int n;
std::array<int, 3> combo1, combo2;

int convert(int i)
{
    if (i % n == 0)
        return n;
    return i % n;
}

int smallestDistance(int a, int b)
{
    return std::min(std::abs(a - b), n - std::abs(a - b));
}

bool within(int x, int bound)
{
    return smallestDistance(x, bound) <= 2;
}

bool validCombo(const std::array<int, 3> &combo)
{
    bool firstNot = false;
    for (int i = 0; i < 3; ++i)
        if (!within(combo[i], combo1[i])) {
            firstNot = true;
            break;
        }
    if (!firstNot)
        return true;
    for (int i = 0; i < 3; ++i) {
        if (!within(combo[i], combo2[i])) {
            if (firstNot)
                return false;
        }
    }
    return true;
}

int main()
{
    std::ifstream in{"combo.in"};
    std::ofstream out{"combo.out"};

    in >> n;
    in.ignore(100, '\n');

    for (auto &i : combo1)
        in >> i;
    in.ignore(100, '\n');
    for (auto &i : combo2)
        in >> i;
    in.ignore(100, '\n');

    int combos = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                if (validCombo({i, j, k})) {
                    std::cout << "valid = {" << i << ", " << j << ", " << k << "}\n";
                    ++combos;
                }
            }
        }
    }

    out << combos << '\n';
}