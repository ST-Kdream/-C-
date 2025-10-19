#include "record.h"

//��¼���溯������
void record_save(bool& is_win, int& difficulty, int& attempts, int& max_num, int& chance,int& EP) {
	time_t now = time(0);
	char time_str[26];
	ctime_s(time_str, sizeof time_str, &now);
	ofstream record_file("��������Ϸ��¼.txt", ios::app);
	if (record_file.is_open()) {
		record_file << "��Ϸʱ��: " << time_str;
		record_file << "��Ϸ�����" << (is_win ? "ʤ��" : "ʧ��") << "  ";
		record_file << "��þ��飺" << (is_win ? EP : 0) << endl;
		record_file << "�Ѷȵȼ�: " << difficulty << endl;
		record_file << "�������: " << max_num << endl;
		record_file << "�²����: " << attempts << "/" << chance << endl;
		record_file << "----------------------------------------" << endl;
		record_file.close();
		cout << "��Ϸ��¼�ѱ��浽'��������Ϸ��¼.txt'" << endl;
	}
	else {
		cout << "�޷��򿪼�¼�ļ�����Ϸ��¼δ���档" << endl;
	}
}

//�����Ϣ��ʾ��������
bool player_information() {
   	ifstream player_file("�����������Ϣ.txt");
	if (player_file.is_open()) {
		string player_line;
		cout << "�����Ϣ��¼��" << endl;
		while (getline(player_file, player_line)) {
			cout << player_line << endl;
		}
		player_file.close();
		return true;
	}
	else {
		cout << "�޷��򿪼�¼�ļ����޷���ʾ�����Ϣ��" << endl;
		return false;
	}
}

//��ʼ�������Ϣ��������
void player_init(string name,int& go_first) {
	cin >> name;
	ofstream player_init("�����������Ϣ.txt");
	if (player_init.is_open()) {
		player_init << name << endl;
		player_init << "�ܾ���ֵ:" << 0 << endl;
		player_init.close();
	}
	else {
		cout << "�޷����������Ϣ�ļ��������Ϣδ���档" << endl;
	}
	cout << "�����Ϣ�ѱ��棬��ӭ�㣬" << name << "��" << endl;
	go_first = 1;
	
}

//��Ҿ���ֵ��Ϣ���º�������
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

void player_update(int& EP) {
	int sum_EP = 0;
	string EP_line, first_line;
	// ��binaryģʽ�򿪣����⻻�з�ת������
	fstream player_file("�����������Ϣ.txt", ios::in | ios::out | ios::binary);

	if (!player_file.is_open()) {
		cout << "�ļ���ʧ�ܣ�" << endl;
		return;
	}

	// 1. ��ȡ�������ԭ����ֵ��
	getline(player_file, first_line); // ��һ�У������
	getline(player_file, EP_line);    // �ڶ��У�����ֵ��

	// 2. ����ԭ����ֵ
	size_t pos = EP_line.find("��");
	if (pos == string::npos) 
		pos = EP_line.find(":");
	if (pos == string::npos) {
		cout << "��ʽ������ð��" << endl;
		player_file.close();
		return;
	}
	string num_str = EP_line.substr(pos + 1);
	string pure_num;
	for (char c : num_str) 
		if (isdigit(c)) pure_num += c;
	if (pure_num.empty()) {
		cout << "δ�ҵ���Ч����" << endl;
		player_file.close();
		return;
	}

	// 3. �����¾���ֵ
	try {
		sum_EP = stoi(pure_num) + EP;
	}
	catch (...) {
		cout << "ת��ʧ��" << endl;
		player_file.close();
		return;
	}

	// 4. д�������ݣ��÷���1���رպ���truncģʽ���´򿪣�
	player_file.close(); // �ȹر�ԭ�ļ�
	ofstream out_file("�����������Ϣ.txt", ios::out | ios::trunc | ios::binary);
	if (out_file.is_open()) {
		out_file << first_line << "\r\n"; // ����д�������
		out_file << "�ܾ���ֵ��" << sum_EP << "\r\n"; // д���¾���ֵ
		out_file.close();
		cout << "���³ɹ����¾���ֵ��" << sum_EP << endl;
	}
	else {
		cout << "д��ʧ�ܣ��޷����ļ�" << endl;
	}
}


//��ʾ��Ϸ����������
void show_rules() {
	ifstream rule_file("��������Ϸ����.txt");
	if (rule_file.is_open()) {
		string rule_line;
		while (getline(rule_file, rule_line)) {
			cout << rule_line << endl;
		}
		rule_file.close();
    }
	else {
		cout << "�޷��򿪹����ļ����޷���ʾ��Ϸ����" << endl;
	}
}
