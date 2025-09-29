#include"gameway.h"

void gameway() {
	//��Ϸ���ܺ��Ѷ�ѡ��
	cout << "��ӭ������������Ϸ��" << endl;
	int difficulty = 0;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "�����������Ѷ�ѡ��\n1Ϊ\t��\n2Ϊ\t��ͨ\n3Ϊ\t����\n4Ϊ\tج��\n5Ϊ\t����\n6Ϊ\t�Զ���" << endl;

	get_valid_int(difficulty, 1, 6, "�������Ѷ�ѡ��(��������1��6��: ");

	//�Ѷ�����
	int difficulty_set[2][6] = { {100, 100, 1000, 5000, 50000, 0},
								 { 10 , 6 , 12 ,  15 ,  20  ,  0} };
	string difficulty_names[6] = { "��","��ͨ","����","ج��","����","�Զ���" };

	//����ѡ�����ò���
	int max_num = difficulty_set[0][difficulty - 1];
	int chance = difficulty_set[1][difficulty - 1];
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
	int attempt = 0;


	//��Ϸ��ѭ��
	cout << "������һ��1��" << max_num << "֮���������" << endl;

	while (chance > attempt) {
		get_valid_int(guess, 1, max_num, "��Ĳ²��ǣ�");
		attempt++;

		if (guess > answer) {
			cout << "�´��ˣ�����" << (chance - attempt) << "�λ��ᣬ" << "������һ�Σ�" << endl;
		}

		else if (guess < answer) {
			cout << "��С�ˣ�����" << (chance - attempt) << "�λ��ᣬ" << "������һ�Σ�" << endl;
		}

		else {
			cout << "��ϲ�㣬�¶��ˣ�" << endl;
			cout << "��һ������" << attempt << "��" << endl;
			break;
		}
	}

	if (guess != answer) {
		cout << "���ź�����û�в��У���ȷ��Ϊ��" << answer << endl;
	}

}

