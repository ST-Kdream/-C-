#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <limits>

using namespace std;
//��Ϸ��¼���溯��ͷ�ļ�
void record_save(bool& is_win, string mode ,int& difficulty, int& attempts, int& max_num, int& chance, int& EP);
//�����Ϣ��ʾ����ͷ�ļ�
bool player_information();
//��ʼ�������Ϣ����ͷ�ļ�
void player_init(string name,int& go_first);
//��Ҿ���ֵ��Ϣ���º���ͷ�ļ�
void player_update(int& EP);
//��ʾ��Ϸ������ͷ�ļ�
void show_rules();

