/*
ID: th3c0r11
TASK: holstein
LANG: C++14
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <limits>

using namespace std;

int noVitamins;
int noFeeds;
vector<int> requirements;
vector<vector<int>> vitaminsPerFeed;
vector<vector<int>> solutions;
int minSolution = 16;

void tryFeed(int i, vector<int> solution, vector<int> requirements)
{
    solution.push_back(i);

    bool allZero = true;
    for (int j = 0; j < requirements.size(); ++j) {
        requirements[j] -= vitaminsPerFeed[i][j];
        if (requirements[j] > 0)
            allZero = false;
    }

    if (solution.size() >= minSolution)
        return;
    
    if (allZero) {
        minSolution = solution.size();
        solutions.push_back(solution);
    } else {
        for (int j = i + 1; j < noFeeds; ++j) {
            tryFeed(j, solution, requirements);
        }
    }
}

int main()
{
    ifstream in{"holstein.in"};
    ofstream out{"holstein.out"};

    in >> noVitamins;

    for (int i = 0; i < noVitamins; ++i) {
        int req;
        in >> req;
        requirements.push_back(req);
    }

    in >> noFeeds;

    for (int i = 0; i < noFeeds; ++i) {
        std::vector<int> vitamins;
        for (int j = 0; j < noVitamins; ++j) {
            int amountVitamin;
            in >> amountVitamin;
            vitamins.push_back(amountVitamin);
        }
        vitaminsPerFeed.push_back(move(vitamins));
    }

    for (int i = 0; i < noFeeds; ++i)
        tryFeed(i, {}, requirements);

    auto sol = *std::min_element(solutions.begin(), solutions.end(), [](vector<int>& sol1, vector<int>& sol2) {
        if (sol1.size() != sol2.size())
            return sol1.size() < sol2.size();
        int sum1 = 0, sum2 = 0;
        for (int i : sol1)
            sum1 += i;
        for (int i : sol2)
            sum2 += i;
        return sum1 < sum2;
    });

    out << minSolution << ' ';
    for (int i = 0; i < sol.size() - 1; ++i)
        out << sol[i] + 1 << ' ';
    out << sol[sol.size() - 1] + 1 << '\n';
}