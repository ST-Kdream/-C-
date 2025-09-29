#include "number_check.h"

bool get_valid_int(int& number, int min, int max, const string& prompt) {
	while (true) {
		cout << prompt;
		cin >> number;
		if (cin.fail() || number < min || number > max) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "����������������루" << min << "��" << max << "��������:" << endl;
		}
		else {
			return true;
		}
	}
}