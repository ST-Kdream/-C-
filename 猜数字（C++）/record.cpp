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
