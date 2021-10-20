/*
ID: th3c0r11
LANG: C++14
TASK: milk3
*/

#include <queue>
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>

std::vector<int> possible;

struct Triple {
	int a, b, c;

	bool operator==(const Triple &t) const
	{
		return a == t.a && b == t.b && c == t.c;
	}
};

std::vector<Triple> already;

std::queue<Triple> q;

int A, B, C;

void addPossible(int c)
{
	bool unique = true;
	for (auto i : possible) {
		if (c == i) {
			unique = false;
			break;
		}
	}

	if (unique)
		possible.push_back(c);
}

void addTriple(Triple t)
{
	bool unique = true;
	for (const auto i : already)
		if (i == t) {
			unique = false;
			break;
		}
	if (unique) {
		already.push_back(t);
		q.push(t);
	}
}

void search(int a, int b, int c)
{
	// try every pouring combination, if a is empty, return

	// (to + from)

	do {
		if (a + b > A) addTriple({A, a + b - A, c});
		else addTriple({a + b, 0, c});
		if (c + b > C) addTriple({a, c + b - C, C});
		else addTriple({a, 0, c + b});

		if (b + a > B) addTriple({b + a - B, B, c});
		else addTriple({0, b + a, c});
		if (c + a > C) addTriple({c + a - C, b, C});
		else addTriple({0, b, c + a});

		if (a + c > A) addTriple({A, b, a + c - A});
		else addTriple({a + c, b, 0});
		if (b + c > B) addTriple({a, B, b + c - B});
		else addTriple({a, b + c, 0});

		auto triple = q.front();
		a = triple.a;
		b = triple.b;
		c = triple.c;
		q.pop();
		if (a == 0)
			addPossible(c);
	} while (!q.empty());
}

int main()
{
	std::ifstream in{"milk3.in"};
	std::ofstream out{"milk3.out"};

	in >> A >> B >> C;

	search(0, 0, C);

	std::sort(possible.begin(), possible.end());
	for (std::size_t i = 0; i < possible.size() - 1; ++i)
		out << possible[i] << ' ';
	out << possible.back() << '\n';
}
