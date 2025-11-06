#include "number_check.h"

bool get_valid_int(int& number, int min, int max, const std::string& prompt) {
	while (true) {
		std::cout << prompt;
		std::cin >> number;
		if (std::cin.fail() || number < min || number > max) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "输入错误，请重新输入（" << min << "到" << max << "的整数）:" << std::endl;
		}
		else {
			return true;
		}
	}
}