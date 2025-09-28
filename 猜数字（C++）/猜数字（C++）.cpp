#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

int main() {

	int max_num = 0;
	int chance = 0;
	int difficulty = 0;
	string difficulty_name = "暂无";



	cout << "欢迎来到猜数字游戏！" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "接下来进行难度选择\n1为\t简单\n2为\t普通\n3为\t困难\n4为\t噩梦\n5为\t地狱\n6为\t自定义" << endl;
	cout << "请输入难度选择(输入整数1到6）" << endl;

	while (true) {
		cin >> difficulty;
		if (cin.fail() || difficulty < 1 || difficulty>6) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "输入错误，请重新输入（1到6的整数）:" << endl;
		}
		else {
			break;
		}
	}


	switch (difficulty) {
	case 1:
		max_num = 100;
		chance = 10;
		difficulty_name = "简单";
		break;
	case 2:
		max_num = 100;
		chance = 6;
		difficulty_name = "普通";
		break;
	case 3:
		max_num = 1000;
		chance = 12;
		difficulty_name = "困难";
		break;
	case 4:
		max_num = 5000;
		chance = 15;
		difficulty_name = "噩梦";
		break;
	case 5:
		max_num = 50000;
		chance = 20;
		difficulty_name = "地狱";
		break;
	case 6:

		cout << "请输入你想要的最大数字（大于1的整数）：" << endl;
		while (true) {
			cin >> max_num;
			if (cin.fail() || max_num <= 1) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "输入错误，请重新输入（大于1的整数）:" << endl;
			}
			else {
				break;
			}
		}

		cout << "请输入你想要的猜测次数（大于0的整数）：" << endl;
		while (true) {
			cin >> chance;
			if (cin.fail() || chance <= 0) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "输入错误，请重新输入（大于0的整数）:" << endl;
			}
			else {
				break;
			}
		}

	}


	cout << "你选择的难度为：" << difficulty_name << "，答案在1到" << max_num << "之间，你有" << chance << "次机会猜中答案。" << endl;
	cout << "游戏将在3秒后开始，请做好准备！" << endl;
	int enter_time = 3;
	while (enter_time > 0) {
		cout << enter_time << endl;
		this_thread::sleep_for(chrono::seconds(1));
		enter_time--;
	}
	cout << "游戏开始！" << endl;





	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>int_dis(1, max_num);

	int answer = int_dis(gen);
	int guess = 0;
	int attempt = 0;



	cout << "请输入一个1到" << max_num << "之间的整数：" << endl;




	while (chance > attempt) {
		while (true) {
			cin >> guess;
			if (cin.fail() || guess < 1 || guess>max_num) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "输入错误，请重新猜测:" << endl;
			}
			else {
				attempt++;
				break;
			}
		}


		if (guess > answer) {
			cout << "猜大了，还有" << (chance - attempt) << "次机会，" << "请再试一次：" << endl;
		}

		else if (guess < answer) {
			cout << "猜小了，还有" << (chance - attempt) << "次机会，" << "请再试一次：" << endl;
		}

		else {
			cout << "恭喜你，猜对了！" << endl;
			cout << "你一共猜了" << attempt << "次" << endl;
			break;
		}
	}

	if (guess != answer) {
		cout << "很遗憾，你没有猜中，正确答案为：" << answer << endl;
	}

	return 0;
}
