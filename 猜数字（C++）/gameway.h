#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <fstream>
#include <ctime>
#include "number_check.h"    //输入验证函数头文件


using namespace std;

//函数声明
void gameway(bool& is_win, int& difficulty, int& attempts, int& max_num, int& chance);
void record_save(bool& is_win, int& difficulty, int& attempts, int& max_num, int& chance);

