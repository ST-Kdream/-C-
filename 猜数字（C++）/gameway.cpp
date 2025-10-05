#include"gameway.h"

//��Ϸ��ʽ��������
void gameway(bool& is_win, int& difficulty, int& attempts, int& max_num, int& chance) {
	//��Ϸ���ܺ��Ѷ�ѡ��
	cout << "��ӭ������������Ϸ��" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "�����������Ѷ�ѡ��\n1Ϊ\t��\n2Ϊ\t��ͨ\n3Ϊ\t����\n4Ϊ\tج��\n5Ϊ\t����\n6Ϊ\t�Զ���" << endl;

	get_valid_int(difficulty, 1, 6, "�������Ѷ�ѡ��(��������1��6��: ");

	//�Ѷ�����
	int difficulty_set[2][6] = { {100, 100, 1000, 5000, 50000, 0},
								 { 10 , 6 , 12 ,  15 ,  20  ,  0} };
	string difficulty_names[6] = { "��","��ͨ","����","ج��","����","�Զ���" };

	//����ѡ�����ò���
	max_num = difficulty_set[0][difficulty - 1];
	chance = difficulty_set[1][difficulty - 1];
	string difficulty_name = difficulty_names[difficulty - 1];

	if (difficulty == 6) {
		get_valid_int(max_num, 10, 1000000, "����������Ҫ���������(10��1000000֮���������: ");
		get_valid_int(chance, 1, 100000, "����������Ҫ�Ĳ²����(1��100000֮���������: ");
		difficulty_name = "�Զ���";

	}

	//��Ϸ��ʼ����ʱ
	cout << "��ѡ����Ѷ�Ϊ��" << difficulty_name << "������1��" << max_num << "֮�䣬����" << chance << "�λ�����д𰸡�" << endl;
	cout << "��Ϸ����3���ʼ��������׼����" << endl;
	int enter_time = 3;
	while (enter_time > 0) {
		cout << enter_time << endl;
		this_thread::sleep_for(chrono::seconds(1));
		enter_time--;
	}
	cout << "��Ϸ��ʼ��" << endl;


	//�����������
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>int_dis(1, max_num);
	//��Ϸ����
	int answer = int_dis(gen);
	int guess = 0;
	attempts = 0;
	

	//��Ϸ��ѭ��
	cout << "������һ��1��" << max_num << "֮���������" << endl;

	while (chance > attempts) {
		get_valid_int(guess, 1, max_num, "��Ĳ²��ǣ�");
		attempts++;

		if (guess > answer) {
			cout << "�´��ˣ�����" << (chance - attempts) << "�λ��ᣬ" << "������һ�Σ�" << endl;
		}

		else if (guess < answer) {
			cout << "��С�ˣ�����" << (chance - attempts) << "�λ��ᣬ" << "������һ�Σ�" << endl;
		}

		else {
			cout << "��ϲ�㣬�¶��ˣ�" << endl;
			cout << "��һ������" << attempts << "��" << endl;
			break;
		}
	}

	if (guess != answer) {
		cout << "���ź�����û�в��У���ȷ��Ϊ��" << answer << endl;
		is_win = false;
	}
	else {
		is_win = true;
	}

}

//��¼���溯������
void record_save(bool& is_win, int& difficulty, int& attempts, int& max_num, int& chance) {
	time_t now = time(0);
	char time_str[26];
	ctime_s(time_str, sizeof time_str, &now);
	ofstream record_file("��������Ϸ��¼.txt", ios::app);
	if (record_file.is_open()) {
		record_file << "��Ϸʱ��: " << time_str;
		record_file << "��Ϸ�����" << (is_win ? "ʤ��" : "ʧ��") << endl;
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

