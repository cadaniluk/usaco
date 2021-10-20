/*
ID: th3c0r11
TASK: milk
LANG: C++14
*/

#include <bits/stdc++.h>

std::vector<std::pair<int, int>> farmers;

int main()
{
    int need, nfarmers;

    std::ifstream in{"milk.in"};
    std::ofstream out{"milk.out"};

    in >> need >> nfarmers;
    in.ignore(100, '\n');

    for (int i = 0; i < nfarmers; ++i) {
        std::pair<int, int> farmer;
        in >> farmer.first >> farmer.second;
        farmers.push_back(farmer);
        in.ignore(100, '\n');
    }

    if (nfarmers == 0) {
        out << "0\n";
        return 0;
    }

    std::sort(farmers.begin(), farmers.end(), [] (auto a, auto b) { return a.first < b.first; });

    int price = 0;
    for (int i = 0; ; ++i) {
        for (int j = 0; j < farmers[i].second; ++j) { 
            if (need == 0)
                goto end;
            price += farmers[i].first;
            --need;
        }
    }

end:
    out << price << '\n';
}