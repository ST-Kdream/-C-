#include "record.h"


//记录保存函数定义
void record_save(bool& is_win, int& difficulty, int& attempts, int& max_num, int& chance,int& EP) {
	time_t now = time(0);
	char time_str[26];
	ctime_s(time_str, sizeof time_str, &now);
	ofstream record_file("猜数字游戏记录.txt", ios::app);
	if (record_file.is_open()) {
		record_file << "游戏时间: " << time_str;
		record_file << "游戏结果：" << (is_win ? "胜利" : "失败") << "  ";
		record_file << "获得经验：" << (is_win ? EP : 0) << endl;
		record_file << "难度等级: " << difficulty << endl;
		record_file << "最大数字: " << max_num << endl;
		record_file << "猜测次数: " << attempts << "/" << chance << endl;
		record_file << "----------------------------------------" << endl;
		record_file.close();
		cout << "游戏记录已保存到'猜数字游戏记录.txt'" << endl;
	}
	else {
		cout << "无法打开记录文件，游戏记录未保存。" << endl;
	}
}

//玩家信息显示函数定义
bool player_information() {
	ifstream player_file("猜数字玩家信息.txt");
	if (player_file.is_open()) {
		string player_line;
		cout << "玩家信息记录：" << endl;
		while (getline(player_file, player_line)) {
			cout << player_line << endl;
		}
		player_file.close();
		return true;
	}
	else {
		cout << "无法打开记录文件，无法显示玩家信息。" << endl;
		return false;
	}
}

//初始化玩家信息函数定义
void player_init(string name,int& go_first) {
	cin >> name;
	ofstream player_init("猜数字玩家信息.txt");
	if (player_init.is_open()) {
		player_init << name << endl;
		player_init << "总经验值：" << 0 << endl;
		player_init.close();
	}
	else {
		cout << "无法创建玩家信息文件，玩家信息未保存。" << endl;
	}
	cout << "玩家信息已保存，欢迎你，" << name << "！" << endl;
	go_first = 1;
	
}

//玩家经验值信息更新函数定义
void player_update(int& EP) {
	int sum_EP;
	string EP_line;
	string first_line;
	fstream player_file("猜数字玩家信息.txt",ios::in|ios::out);
	if (player_file.is_open()) {
		getline(player_file, first_line);
		getline(player_file, EP_line);
		size_t pos = EP_line.find("：");
		if (pos != string::npos) {
			try {
				sum_EP = stoi(EP_line.substr(pos)) + EP;
			}
			catch (const invalid_argument&) {
				cout << "玩家信息格式错误，无法读取经验值。" << endl;
				return;
			}
			catch (const out_of_range&) {
				cout << "玩家信息中的经验值超出范围，无法读取经验值。" << endl;
				return;
			}
		}
		else {
			cout << "玩家信息格式错误，无法读取经验值。" << endl;
		}
		player_file.seekp(0);
		player_file << first_line << endl;
		player_file << "总经验值：" << sum_EP << endl;
		player_file.flush();
		player_file.close();
		cout << "经验值已更新，你当前的总经验值为：" << sum_EP << endl
			;
		
	}
}
		

//显示游戏规则函数定义
void show_rules() {
	ifstream rule_file("猜数字游戏规则.txt");
	if (rule_file.is_open()) {
		string rule_line;
		while (getline(rule_file, rule_line)) {
			cout << rule_line << endl;
		}
		rule_file.close();
    }
	else {
		cout << "无法打开规则文件，无法显示游戏规则。" << endl;
	}
}
