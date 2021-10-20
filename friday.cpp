/*
ID: th3c0r11
TASK: friday
LANG: C++14
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <array>

bool leap(int year)
{
	if (year % 100 == 0)
		return year % 400 == 0;
	return year % 4 == 0;
}

struct Date {
	int day, month, year;
	void next()
	{
		static std::array<int, 4> thirties{9, 4, 6, 11};

		++day;

		if (std::find(thirties.begin(), thirties.end(), month) != thirties.end()) {
			if (day == 31) {
				day = 1;
				++month;
				return;
			}
		}
		if (month == 2 && day == 29 && !leap(year)) {
			day = 1; ++month; return; }
		if (month == 2 && day == 30 && leap(year)) {
			day = 1; ++month; return; }
		if (day == 32) {
			day = 1;
			++month;
			return;
		}	
		if (month == 13) {
			++year;
			month = 1;
		}
	}
};


int main()
{
	std::ifstream in{"friday.in"};
	std::ofstream out{"friday.out"};

	int years;
	in >> years;

	Date d{1, 1, 1900};
	int weekdays[7] { };
	int weekday = 0;
	while (d.year != 1900 + years) {
		if (d.day == 13)
			++weekdays[weekday];
		++weekday;
		if (weekday == 7)
			weekday = 0;
		std::cout << d.day << " " << d.month << " " << d.year << '\n';
		d.next();
	}

	for (int i = 5; i < 7; ++i)
		out << weekdays[i] << " ";
	for (int i = 0; i < 4; ++i)
		out << weekdays[i] << " ";
	out << weekdays[4] << '\n';
}
