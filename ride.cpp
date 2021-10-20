/*
ID: th3c0r11
TASK: ride
LANG: C++14
*/

#include <iostream>
#include <fstream>
#include <algorithm>

long name2num(const std::string &name)
{
	static std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	long ret = 1;
	for (auto c : name)
		ret *= alphabet.find(c) + 1;

	return ret % 47;
}

int main()
{
	std::ofstream out{"ride.out"};
	std::ifstream in{"ride.in"};
	std::string comet, group;
	std::getline(in, comet);
	std::getline(in, group);

	out << (name2num(comet) == name2num(group) ? "GO" : "STAY") << std::endl;
}
