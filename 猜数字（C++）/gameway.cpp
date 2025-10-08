#include"gameway.h"

//游戏方式函数定义
void gameway_common(bool& is_win, int& difficulty, int& attempts, int& max_num, int& chance , int& EP) {
	//游戏介绍和难度选择
	cout << "欢迎来到猜数字游戏！" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "接下来进行难度选择\n1为\t简单\n2为\t普通\n3为\t困难\n4为\t噩梦\n5为\t地狱\n6为\t自定义" << endl;

	get_valid_int(difficulty, 1, 6, "请输入难度选择(输入整数1到6）: ");

	//难度设置
	class DifficultySetting {
	public:
		int max_num;
		int chance;
		int EP;
		string name;

		DifficultySetting(int Difficulty_max_num, int Difficulty_chance, int Difficulty_EP, string difficulty_name) {
			max_num = Difficulty_max_num;
			chance = Difficulty_chance;
			EP = Difficulty_EP;
			name = difficulty_name;
		}
	};
	
	// 定义并初始化难度参数
	vector <DifficultySetting> difficulty_settings = {
	{100,10, 5, "简单"},
	{100, 7, 10, "普通"},
	{2000, 15, 15, "困难"},
	{10000, 20, 20, "噩梦"},
	{500000, 25, 30, "地狱"},
	{0, 0, 0, "自定义"} 
	};
	
   

	//根据选择设置参数
	DifficultySetting chosen_difficulty = difficulty_settings[difficulty - 1];
	max_num = chosen_difficulty.max_num;
	chance = chosen_difficulty.chance;
	EP = chosen_difficulty.EP;

	

	if (difficulty == 6) {
		get_valid_int(max_num, 10, 1000000, "请输入你想要的最大数字(10到1000000之间的整数）: ");
		get_valid_int(chance, 1, 100000, "请输入你想要的猜测次数(1到100000之间的整数）: ");
		
	}

	//游戏开始倒计时
	cout << "你选择的难度为：" << chosen_difficulty.name << "，答案在1到" << max_num << "之间，你有" << chance << "次机会猜中答案。" << endl;
	cout << "如果胜利，你将获得" << EP << "经验" << endl;
	cout << "游戏将在3秒后开始，请做好准备！" << endl;
	int enter_time = 3;
	while (enter_time > 0) {
		cout << enter_time << endl;
		this_thread::sleep_for(chrono::seconds(1));
		enter_time--;
	}
	cout << "游戏开始！" << endl;


	//随机数生成器
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>int_dis(1, max_num);
	//游戏变量
	int answer = int_dis(gen);
	int guess = 0;
	attempts = 0;
	

	//游戏主循环
	cout << "请输入一个1到" << max_num << "之间的整数：" << endl;

	while (chance > attempts) {
		get_valid_int(guess, 1, max_num, "你的猜测是：");
		attempts++;

		if (guess > answer) {
			cout << "猜大了，还有" << (chance - attempts) << "次机会，" << "请再试一次：" << endl;
		}

		else if (guess < answer) {
			cout << "猜小了，还有" << (chance - attempts) << "次机会，" << "请再试一次：" << endl;
		}

		else {
			cout << "恭喜你，猜对了！" << endl;
			cout << "你一共猜了" << attempts << "次" << endl;
			break;
		}
	}

	if (guess != answer) {
		cout << "很遗憾，你没有猜中，正确答案为：" << answer << endl;
		is_win = false;
	}
	else {
		is_win = true;
	}

}


	



