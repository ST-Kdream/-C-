#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <fstream>
#include <ctime>
#include "number_check.h"    //������֤����ͷ�ļ�


using namespace std;

//��������
void gameway(bool& is_win, int& difficulty, int& attempts, int& max_num, int& chance);
void record_save(bool& is_win, int& difficulty, int& attempts, int& max_num, int& chance);

