#include "record.h"

//记录保存函数定义
void record_save(bool& is_win, string mode, int& difficulty, int& attempts, int& max_num, int& chance,int& EP) {
	time_t now = time(0);
	char time_str[26];
	ctime_s(time_str, sizeof time_str, &now);
	ofstream record_file("game_record.txt", ios::app);
	if (record_file.is_open()) {
		record_file << "游戏时间: " << time_str;
		record_file << "游戏结果：" << (is_win ? "胜利" : "失败") << "  ";
		record_file << "获得经验：" << (is_win ? EP : 0) << endl;
        record_file << "游戏模式：" << mode << "   ";
		record_file << "难度等级: " << difficulty << endl;
		record_file << "最大数字: " << max_num << endl;
		record_file << "猜测次数: " << attempts << "/" << chance << endl;
		record_file << "----------------------------------------" << endl;
		record_file.close();
		cout << "游戏记录已保存到'game_record.txt'" << endl;
	}
	else {
		cout << "无法打开记录文件，游戏记录未保存。" << endl;
	}
}

//玩家信息显示函数定义
bool player_information() {
   	ifstream player_file("player_information.txt");
	if (player_file.is_open()) {
		string player_line;
		cout << "玩家信息记录：" << endl;
		while (getline(player_file, player_line)) {
			cout << player_line << endl;
		}
		player_file.close();
		return true;
	}
	else {
		cout << "无法打开记录文件，无法显示玩家信息。" << endl;
		return false;
	}
}

//初始化玩家信息函数定义
void player_init(string name,int& go_first) {
	cin >> name;
	ofstream player_init("player_information.txt");
	if (player_init.is_open()) {
		player_init << name << endl;
		player_init << "总经验值:" << 0 << endl;
        player_init << "段位：迷雾探索者" << endl;
		player_init.close();
	}
	else {
		cout << "无法创建玩家信息文件，玩家信息未保存。" << endl;
	}
	cout << "玩家信息已保存，欢迎你，" << name << "！" << endl;
	go_first = 1;
	
}

//玩家经验值信息更新函数定义
int player_update(int& EP) 
{
    int sum_EP;  
    string EP_line;  
    string first_line;  
    string rank_line;
    // 用binary模式打开，避免换行符转换导致的乱码
    fstream player_file("player_information.txt", ios::in | ios::out | ios::binary);  

    if (player_file.is_open()) {
        // 读取第一行（玩家名）和第二行（经验值行）
        getline(player_file, first_line);
        getline(player_file, EP_line);
        getline(player_file, rank_line);

        // 查找冒号（兼容中文“：”和英文“:”）
        size_t pos = EP_line.find("：");
        if (pos == string::npos) {
            pos = EP_line.find(":");  // 补充英文冒号兼容
        }

        if (pos != string::npos) 
        {
            // 截取冒号后内容，并过滤出纯半角数字（解决格式错误核心）
            string num_str = EP_line.substr(pos + 1);  // 跳过冒号
            string pure_num;  // 临时变量，用于存储过滤后的数字
            // 用ASCII范围判断半角数字（替代isdigit，避免误判）
            for (char c : num_str) 
            {
                if (c >= '0' && c <= '9')    // 只保留0-9的半角数字
                {  
                    pure_num += c;
                }
            }

            // 检查是否提取到有效数字
            try
            {
                if (pure_num.empty())
                {
                    player_file.close();
                    throw runtime_error("更新玩家信息错误");
                }
            }
            catch (const exception& e)
            {
                cout << "玩家信息格式错误，未找到有效数字（仅支持半角0-9）。" << endl;
                exit(12);
            }
            

            // 转换数字并计算总经验值
            try {
                sum_EP = stoi(pure_num) + EP;  
            }
            catch (const invalid_argument&) {
                cout << "玩家信息格式错误，无法读取经验值。" << endl;
                player_file.close();
                exit(13);
            }
            catch (const out_of_range&) {
                cout << "玩家信息中的经验值超出范围，无法读取经验值。" << endl;
                player_file.close();;
                exit(14);
            }

            // 关闭原文件，用truncate模式重新打开写入（解决truncate成员错误）
            player_file.close();
            ofstream out_file("player_information.txt", ios::out | ios::trunc | ios::binary);
            if (out_file.is_open()) {
                // 写回玩家名和新经验值行（用\r\n避免换行符乱码）
                out_file << first_line << "\r\n";
                out_file << "总经验值：" << sum_EP << "\r\n";
                out_file << rank_line << "\r\n";
                out_file.close();
                cout << "经验值更新成功！当前总经验值：" << sum_EP << endl;
                return sum_EP;
            }
            else {
                cout << "无法写入文件，可能被占用。" << endl;
            }

        }
        else {
            // 未找到冒号的错误处理
            cout << "玩家信息格式错误，未找到冒号（：或:）。" << endl;
            player_file.close();
        }

    }
    else {
        // 文件打开失败的错误处理
        cout << "无法打开玩家信息文件，请检查路径或文件是否被占用。" << endl;
    }
}

//段位更新函数头文件
void rank_update(string rank_name)
{
    string rank_line = "玩家段位为：" + rank_name;
    vector <string> fline;
    ifstream in_file("player_information.txt");
    if (in_file.is_open())
    {
        string line;
        while (getline(in_file, line))
        {
            fline.push_back(line);
        }
        in_file.close();
    }
    else
        cout << "更新段位时文件打开失败！" << endl;

    if (fline.size() == 3)
    {
        fline[2] = rank_line;
    }
    else
        cout << "玩家信息格式错误！" << endl;

    ofstream out_file("player_information.txt");
    if (out_file.is_open())
    {
        for (const auto& out_line : fline)
        {
            out_file << out_line << "\r\n";
        }
        cout << "段位更新成功，你现在的段位是：" << rank_name << endl;
    }
    else
    {
        cout << "玩家信息文件无法打开" << endl;
    }
}

//显示游戏规则函数定义
void show_rules() {
	ifstream rule_file("game_rules.txt");
	if (rule_file.is_open()) {
		string rule_line;
		while (getline(rule_file, rule_line)) 
        {
			cout << rule_line << endl;
		}
		rule_file.close();
    }
	else
    {
		cout << "无法打开规则文件，无法显示游戏规则。" << endl;
	}
}
