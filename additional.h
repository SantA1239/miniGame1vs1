#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace valid {
	// valid_num - возвращает число с консоли в формате int
	// message_info - информаци€ о числе, message_error - информаци€ в случае неправильного ввода, lower_limit - нижн€€ граница (включительно), upper_limit - верхн€€ граница (включительно)
	int valid_num(string message_info, string message_error, int lower_limit, int upper_limit) {
		int x;
		cout << message_info;
		cin >> x;
		while (cin.fail() || cin.peek() != '\n' || lower_limit > x || upper_limit < x)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << message_error;
			cin >> x;
		}

		return x;
	}
}

namespace random {
	// generate_random_chance - возвращает проценты (0-100%)
	int generate_random_chance() {
		srand(time(0));
		return rand() % 101;
	}

	// провер€ет шанс и возвращает true/false (выпал/не выпал, увернулс€/неувернулс€ и тд.)
	// int chance шанс (0-100%) возникновени€ событи€
	bool if_chance(int chance) {

		return chance > generate_random_chance();
	}

	// get_random_by_lover_upper_limit - возвращает число от lover_limit до upper_limit
	// int lover_limit - нижн€€ граница (включительно), int upper_limit - верхн€€ граница (включительно)
	int get_random_by_lover_upper_limit(int lover_limit, int upper_limit) {
		srand(time(0));
		return rand() % (upper_limit + 1) + lover_limit;
	}
}