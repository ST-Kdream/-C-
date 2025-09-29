#include "number_check.h"

bool get_valid_int(int& number, int min, int max, const string& prompt) {
	while (true) {
		cout << prompt;
		cin >> number;
		if (cin.fail() || number < min || number > max) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "输入错误，请重新输入（" << min << "到" << max << "的整数）:" << endl;
		}
		else {
			return true;
		}
	}
}