#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <fstream>
#include <ctime>
#include <vector>
#include "number_check.h" //������֤����ͷ�ļ�



using namespace std;

//��������
void gameway_common(bool& is_win, int& difficulty, int& attempts, int& max_num, int& chance, int& EP);
