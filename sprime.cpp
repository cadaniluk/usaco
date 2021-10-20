/*
ID: th3c0r11
TASK: sprime
LANG: C++14
*/

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

int N;

long primes[8];

// level of failure. N - 1: one-digit number is non-prime up to 0: entire number is non-prime
int isSuperprime(long l)
{
    for (size_t i = 0; i < N; ++i, l /= 10)
        primes[i] = l;
    
    if (primes[N - 1] == 1 || primes[N - 1] == 4 || primes[N - 1] == 6 || primes[N - 1] == 8 || primes[N - 1] == 9)
        return N - 1;

    for (size_t i = N - 1; i >= 1; --i) {
        for (long d = 2; d <= sqrt(primes[i - 1]); ++d)
            if (primes[i - 1] % d == 0)
                return i - 1;
    }

    return -1;
}

int main()
{
    ifstream in{"sprime.in"};
    ofstream out{"sprime.out"};

    in >> N;

    long max = pow(10, N);

    for (long i = pow(10, N - 1) + 1; i < max; ) {
        int level = isSuperprime(i);
        if (level == -1) {
            out << i << '\n';
            i += 2;
        } else {
            i += pow(10, level);
        }
    }
}