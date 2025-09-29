#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <chrono>
#include "number_check.h"

using namespace std;

int main() {

	int max_num = 0;
	int chance = 0;
	int difficulty = 0;
	string difficulty_name = "暂无";



	cout << "欢迎来到猜数字游戏！" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "接下来进行难度选择\n1为\t简单\n2为\t普通\n3为\t困难\n4为\t噩梦\n5为\t地狱\n6为\t自定义" << endl;
	
	get_valid_int(difficulty, 1, 6, "请输入难度选择(输入整数1到6）: ");

	
	int difficulty_set[2][6] = { {100, 100, 1000, 5000, 50000, 0},
							     { 10 , 6 , 12 ,  15 ,  20  ,  0} };
	string difficulty_names[6] = { "简单","普通","困难","噩梦","地狱","自定义" };
	
	
	max_num = difficulty_set[0][difficulty - 1];
	chance = difficulty_set[1][difficulty - 1];
	difficulty_name = difficulty_names[difficulty - 1];
	
if (difficulty == 6) { 
	get_valid_int(max_num, 10, 1000000, "请输入你想要的最大数字(10到1000000之间的整数）: ");
	get_valid_int(chance, 1, 100000, "请输入你想要的猜测次数(1到100000之间的整数）: ");
	difficulty_name = "自定义";
		
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
		get_valid_int(guess, 1, max_num, "你的猜测是：");
		attempt++;

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
