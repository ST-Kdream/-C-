#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <limits>
#include<vector>
#include<stdexcept>
#include<sstream>

//游戏记录保存函数头文件
bool record_save(bool& is_win ,int& difficulty, int& attempts, int& max_num, int& chance, int& EP);
//玩家信息显示函数头文件
bool player_information(std::stringstream& output);
//初始化玩家信息函数头文件
void player_init();
//玩家经验值信息更新函数头文件
bool player_update(int& update_EP,int& sum_EP);
//段位更新函数头文件
bool rank_update(std::string rank_name);
//显示游戏规则函数头文件
void show_rules(std::stringstream& output);
//统一更新函数
bool update_all(int update_EP);

