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

//��ͨģʽ����ͷ�ļ�
void gameway_common(bool& is_win, int& difficulty, int& attempts, int& max_num, int& chance, int& EP);
//��սģʽ����ͷ�ļ�
void gameway_challenge(bool& is_win, int& level, int& attempts, int& max_num, int& chance, int& EP);
//�޾�ģʽ����ͷ�ļ�
void gameway_endless(bool& is_win, int& episode, int& attempts, int& max_num, int& chance, int& EP, int& update_EP);
