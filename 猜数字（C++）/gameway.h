#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <random>
#include <fstream>
#include <ctime>
#include <vector>
#include "Qt_gui.h"

std::stringstream gameway_judge(int guess, int answer, int chance, int attempts);
//普通模式函数头文件
void gameway_common(int& difficulty,int& max_num, int& chance, int& EP);
//挑战模式函数头文件
void gameway_challenge(int& level,int& max_num, int& chance, int& EP);
//无尽模式函数头文件
void gameway_endless(bool& is_win, int& episode, int& attempts, int& max_num, int& chance, int& EP, int& update_EP);
// 获取难度设置的描述信息
QString getdiffinfo(int difficulty, int max_num, int chance, int EP);
// 获取等级设置的描述信息
QString getlevelinfo(int level, int max_num, int chance, int EP);
QString endlessgammemessage(int episode);

