/*
ID: th3c0r11
TASK: gift1
LANG: C++14
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <vector>

int main()
{
	std::ifstream in{"gift1.in"};
	std::ofstream out{"gift1.out"};

	int np;
	std::unordered_map<std::string, int> accounts;
	std::vector<std::string> names;

	std::string npstr;
	std::getline(in, npstr);
	np = std::atoi(npstr.c_str());

	std::string null;
	for (int i = 0; i < np; ++i) {
		std::getline(in, null);
		accounts[null] = 0;
		names.push_back(null);
	}

	for (int i = 0; i < np; ++i) {
		std::string name;
		int amount;
		int people;

		std::getline(in, name);
		in >> amount >> people;
		std::getline(in, null);

		if (people == 0)
			continue;

		int giveAmount = amount / people;
		int keepAmount = amount % people;

		accounts[name] += keepAmount;
		accounts[name] -= amount;

		for (int j = 0; j < people; ++j) {
			std::string recipient;
			std::getline(in, recipient);

			accounts[recipient] += giveAmount;
		}
	}

	for (const auto &name : names)
		out << name << " " << accounts[name] << '\n';
}
