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
