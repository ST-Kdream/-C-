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
void player_init(string name) {
	cin >> name;
	ofstream player_init("�����������Ϣ.txt");
	if (player_init.is_open()) {
		player_init << name << endl;
		player_init << "�ܾ���ֵ��" << 0 << endl;
	}
}

//��Ҿ���ֵ��Ϣ���º�������
void player_update(int& EP) {
	int sum_EP;
	string EP_line;
	string first_line;
	fstream player_file("�����������Ϣ.txt");
	if (player_file.is_open()) {
		getline(player_file, first_line);
		getline(player_file, EP_line);
		size_t pos = EP_line.find("��");
		if (pos != string::npos) {
			string EP_str = EP_line.substr(pos + 1);
			sum_EP = stoi(EP_str);
			sum_EP += EP;
		}
		else {
			cout << "�����Ϣ��ʽ�����޷���ȡ����ֵ��" << endl;
		}
		string new_EP_line = "�ܾ���ֵ��" + to_string(sum_EP);
		player_file << first_line << endl;
		player_file << new_EP_line << endl;
		player_file.close();
		}
}