#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <fstream>
#include <ctime>
#include <vector>
#include "number_check.h" //输入验证函数头文件



using namespace std;

//普通模式函数头文件
void gameway_common(bool& is_win, int& difficulty, int& attempts, int& max_num, int& chance, int& EP);
//挑战模式函数头文件
void gameway_challenge(bool& is_win, int& level, int& attempts, int& max_num, int& chance, int& EP);
//无尽模式函数头文件
void gameway_endless(bool& is_win, int& episode, int& attempts, int& max_num, int& chance, int& EP, int& update_EP);
