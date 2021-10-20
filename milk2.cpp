/*
ID: thc0r11
TASK: milk2
LANG: C++14
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>

bool between(int val, int start, int stop)
{
    return val >= start && val <= stop;
}

int main()
{
    std::ifstream in{"milk2.in"};
    std::ofstream out{"milk2.out"};

    int farmers;
    in >> farmers;
    in.ignore(100, '\n');

    if (farmers == 0) {
        out << "0 0\n";
        return 0;
    }

    std::vector<std::pair<int, int>> times;
    for (int i = 0; i < farmers; ++i) {
        std::pair<int, int> time;
        in >> time.first >> time.second;
        in.ignore(100, '\n');
        times.push_back(time);
    }

    std::sort(times.begin(), times.end(), [] (auto a, auto b) { return a.first < b.first; });

    std::vector<int> chains;
    int standby = 0;

    int start = times[0].first, stop = times[0].second;
    for (size_t i = 1; i < times.size(); ++i) {
        if (between(times[i].first, start, stop))
            stop = std::max(stop, times[i].second);
        else {
            chains.push_back(stop - start);
            standby = std::max(standby, times[i].first - stop);
            start = times[i].first;
            stop = times[i].second;
        }
    }
    chains.push_back(stop - start);

    out << *std::max_element(chains.begin(), chains.end()) << ' ' << standby << '\n';
}