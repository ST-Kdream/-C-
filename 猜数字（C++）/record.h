#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <limits>
#include<vector>
#include<stdexcept>

using namespace std;
//游戏记录保存函数头文件
void record_save(bool& is_win, string mode ,int& difficulty, int& attempts, int& max_num, int& chance, int& EP);
//玩家信息显示函数头文件
bool player_information();
//初始化玩家信息函数头文件
void player_init(string name,int& go_first);
//玩家经验值信息更新函数头文件
int player_update(int& EP);
//段位更新函数头文件
void rank_update(string rank_name);
//显示游戏规则函数头文件
void show_rules();
//统一更新函数
void update_all(int update_EP);

