#include"gameway.h"

void gameway_all(int& max_num, int& chance, int& attempts, bool& is_win)
{
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

//��ͨģʽ��������
void gameway_common(bool& is_win, int& difficulty, int& attempts, int& max_num, int& chance , int& EP) {
	//��Ϸ���ܺ��Ѷ�ѡ��
	cout << "��ӭ������������Ϸ����ͨģʽ����" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "�����������Ѷ�ѡ��\n1Ϊ\t��\n2Ϊ\t��ͨ\n3Ϊ\t����\n4Ϊ\tج��\n5Ϊ\t����\n6Ϊ\t�Զ���" << endl;

	get_valid_int(difficulty, 1, 6, "�������Ѷ�ѡ��(��������1��6��: ");

	//�Ѷ�����
	class DifficultySetting {
	public:
		int max_num;
		int chance;
		int EP;
		string name;

		DifficultySetting(int Difficulty_max_num, int Difficulty_chance, int Difficulty_EP, string difficulty_name) {
			max_num = Difficulty_max_num;
			chance = Difficulty_chance;
			EP = Difficulty_EP;
			name = difficulty_name;
		}
	};
	
	// ���岢��ʼ���ѶȲ���
	vector <DifficultySetting> difficulty_settings = {
	{100,10, 5, "��"},
	{100, 7, 10, "��ͨ"},
	{2000, 15, 15, "����"},
	{10000, 20, 20, "ج��"},
	{500000, 25, 30, "����"},
	{0, 0, 0, "�Զ���"} 
	};
	
   

	//����ѡ�����ò���
	DifficultySetting chosen_difficulty = difficulty_settings[difficulty - 1];
	max_num = chosen_difficulty.max_num;
	chance = chosen_difficulty.chance;
	EP = chosen_difficulty.EP;

	

	if (difficulty == 6) {
		get_valid_int(max_num, 10, 1000000, "����������Ҫ���������(10��1000000֮���������: ");
		get_valid_int(chance, 1, 100000, "����������Ҫ�Ĳ²����(1��100000֮���������: ");
		
	}

	//��Ϸ��ʼ����ʱ
	cout << "��ѡ����Ѷ�Ϊ��" << chosen_difficulty.name << "������1��" << max_num << "֮�䣬����" << chance << "�λ�����д𰸡�" << endl;
	cout << "���ʤ�����㽫���" << EP << "����" << endl;
	cout << "��Ϸ����3���ʼ��������׼����" << endl;
	int enter_time = 3;
	while (enter_time > 0) {
		cout << enter_time << endl;
		this_thread::sleep_for(chrono::seconds(1));
		enter_time--;
	}
	cout << "��Ϸ��ʼ��" << endl;

	gameway_all(max_num, chance, attempts, is_win);
}

//��սģʽ��������
void gameway_challenge(bool& is_win, int& level, int& attempts, int& max_num, int& chance, int& EP)
{
	cout << "��ӭ������������Ϸ����սģʽ����" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "�㽫��9���Ѷȵȼ��ɹ���ս" << endl;
	get_valid_int(level, 1, 9, "��������ѡ������Ҫ��ս���Ѷȵȼ��� ");
	
	//����ѡ�����ò���
	class LevelSetting
	{
	public:
		int level_num;
		int max_num, chance, EP;
		LevelSetting(int Level_max_num, int Level_chance, int Level_EP, int Level_level_num)
		{
			max_num = Level_max_num;
			chance = Level_chance;
			EP = Level_EP;
			level_num = Level_level_num;
		}
	};

	// ���岢��ʼ���ѶȲ���
	vector <LevelSetting> level_settings = 
	{
		{100, 6, 20, 1},
		{2000, 14, 30, 2},
		{5000 ,16, 45, 3},
		{8000, 16, 50, 4},
    	{10000, 18, 55, 5},
		{60000, 20, 65, 6},
		{100000, 25, 70, 7},
		{200000, 35, 80, 8},
		{10000000, 40, 100, 9}
	};

	//����ѡ�����ò���
	max_num = level_settings[level - 1].max_num;
	chance = level_settings[level - 1].chance;
	EP = level_settings[level - 1].EP;
	level = level_settings[level - 1].level_num;
	cout << "��ѡ����Ѷȵȼ�Ϊ��" << level << "������1��" << max_num << "֮�䣬����" << chance << "�λ�����д𰸡�" << endl;

	//��Ϸ��ʼ����ʱ
	cout << "��Ϸ����3���ʼ��������׼����" << endl;
	for (int enter_time = 3; enter_time > 0; enter_time--)
	{
		cout << enter_time << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
	cout << "��Ϸ��ʼ��" << endl;

	gameway_all(max_num, chance, attempts, is_win);
}

	



