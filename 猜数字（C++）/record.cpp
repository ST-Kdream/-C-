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
		player_init << "总经验值:" << 0 << endl;
		player_init.close();
	}
	else {
		cout << "无法创建玩家信息文件，玩家信息未保存。" << endl;
	}
	cout << "玩家信息已保存，欢迎你，" << name << "！" << endl;
	go_first = 1;
	
}

//玩家经验值信息更新函数定义
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

void player_update(int& EP) {
	int sum_EP = 0;
	string EP_line, first_line;
	// 用binary模式打开，避免换行符转换问题
	fstream player_file("猜数字玩家信息.txt", ios::in | ios::out | ios::binary);

	if (!player_file.is_open()) {
		cout << "文件打开失败！" << endl;
		return;
	}

	// 1. 读取玩家名和原经验值行
	getline(player_file, first_line); // 第一行：玩家名
	getline(player_file, EP_line);    // 第二行：经验值行

	// 2. 解析原经验值
	size_t pos = EP_line.find("：");
	if (pos == string::npos) 
		pos = EP_line.find(":");
	if (pos == string::npos) {
		cout << "格式错误：无冒号" << endl;
		player_file.close();
		return;
	}
	string num_str = EP_line.substr(pos + 1);
	string pure_num;
	for (char c : num_str) 
		if (isdigit(c)) pure_num += c;
	if (pure_num.empty()) {
		cout << "未找到有效数字" << endl;
		player_file.close();
		return;
	}

	// 3. 计算新经验值
	try {
		sum_EP = stoi(pure_num) + EP;
	}
	catch (...) {
		cout << "转换失败" << endl;
		player_file.close();
		return;
	}

	// 4. 写入新内容（用方案1：关闭后以trunc模式重新打开）
	player_file.close(); // 先关闭原文件
	ofstream out_file("猜数字玩家信息.txt", ios::out | ios::trunc | ios::binary);
	if (out_file.is_open()) {
		out_file << first_line << "\r\n"; // 重新写入玩家名
		out_file << "总经验值：" << sum_EP << "\r\n"; // 写入新经验值
		out_file.close();
		cout << "更新成功！新经验值：" << sum_EP << endl;
	}
	else {
		cout << "写入失败：无法打开文件" << endl;
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
