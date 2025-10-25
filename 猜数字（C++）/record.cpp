#include "record.h"

//��¼���溯������
void record_save(bool& is_win, string mode, int& difficulty, int& attempts, int& max_num, int& chance,int& EP) {
	time_t now = time(0);
	char time_str[26];
	ctime_s(time_str, sizeof time_str, &now);
	ofstream record_file("game_record.txt", ios::app);
	if (record_file.is_open()) {
		record_file << "��Ϸʱ��: " << time_str;
		record_file << "��Ϸ�����" << (is_win ? "ʤ��" : "ʧ��") << "  ";
		record_file << "��þ��飺" << (is_win ? EP : 0) << endl;
        record_file << "��Ϸģʽ��" << mode << "   ";
		record_file << "�Ѷȵȼ�: " << difficulty << endl;
		record_file << "�������: " << max_num << endl;
		record_file << "�²����: " << attempts << "/" << chance << endl;
		record_file << "----------------------------------------" << endl;
		record_file.close();
		cout << "��Ϸ��¼�ѱ��浽'game_record.txt'" << endl;
	}
	else {
		cout << "�޷��򿪼�¼�ļ�����Ϸ��¼δ���档" << endl;
	}
}

//�����Ϣ��ʾ��������
bool player_information() {
   	ifstream player_file("player_information.txt");
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
	ofstream player_init("player_information.txt");
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
void player_update(int& EP) {
    int sum_EP;  
    string EP_line;  
    string first_line;  
    // ��binaryģʽ�򿪣����⻻�з�ת�����µ�����
    fstream player_file("player_information.txt", ios::in | ios::out | ios::binary);  

    if (player_file.is_open()) {
        // ��ȡ��һ�У���������͵ڶ��У�����ֵ�У�
        getline(player_file, first_line);
        getline(player_file, EP_line);

        // ����ð�ţ��������ġ�������Ӣ�ġ�:����
        size_t pos = EP_line.find("��");
        if (pos == string::npos) {
            pos = EP_line.find(":");  // ����Ӣ��ð�ż���
        }

        if (pos != string::npos) {
            // ��ȡð�ź����ݣ������˳���������֣������ʽ������ģ�
            string num_str = EP_line.substr(pos + 1);  // ����ð��
            string pure_num;  // ��ʱ���������ڴ洢���˺������
            // ��ASCII��Χ�жϰ�����֣����isdigit���������У�
            for (char c : num_str) {
                if (c >= '0' && c <= '9') {  // ֻ����0-9�İ������
                    pure_num += c;
                }
            }

            // ����Ƿ���ȡ����Ч����
            if (pure_num.empty()) {
                cout << "�����Ϣ��ʽ����δ�ҵ���Ч���֣���֧�ְ��0-9����" << endl;
                player_file.close();
                return;
            }

            // ת�����ֲ������ܾ���ֵ
            try {
                sum_EP = stoi(pure_num) + EP;  
            }
            catch (const invalid_argument&) {
                cout << "�����Ϣ��ʽ�����޷���ȡ����ֵ��" << endl;
                player_file.close();
                return;
            }
            catch (const out_of_range&) {
                cout << "�����Ϣ�еľ���ֵ������Χ���޷���ȡ����ֵ��" << endl;
                player_file.close();
                return;
            }

            // �ر�ԭ�ļ�����truncateģʽ���´�д�루���truncate��Ա����
            player_file.close();
            ofstream out_file("player_information.txt", ios::out | ios::trunc | ios::binary);
            if (out_file.is_open()) {
                // д����������¾���ֵ�У���\r\n���⻻�з����룩
                out_file << first_line << "\r\n";
                out_file << "�ܾ���ֵ��" << sum_EP << "\r\n";
                out_file.close();
                cout << "����ֵ���³ɹ�����ǰ�ܾ���ֵ��" << sum_EP << endl;
            }
            else {
                cout << "�޷�д���ļ������ܱ�ռ�á�" << endl;
            }

        }
        else {
            // δ�ҵ�ð�ŵĴ�����
            cout << "�����Ϣ��ʽ����δ�ҵ�ð�ţ�����:����" << endl;
            player_file.close();
        }

    }
    else {
        // �ļ���ʧ�ܵĴ�����
        cout << "�޷��������Ϣ�ļ�������·�����ļ��Ƿ�ռ�á�" << endl;
    }
}

//��ʾ��Ϸ����������
void show_rules() {
	ifstream rule_file("game_rules.txt");
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
