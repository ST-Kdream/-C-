#include "gameway.h"      //游戏方式函数头文件
#include "record.h"       //记录保存函数头文件

using namespace std;

//询问是否再玩一次函数定义
bool play_again(int& go_first) {
	int is_again;
	get_valid_int(is_again, 0, 1, "你想再玩一次吗？\n(0为再来一次，1为退出)");
	if (is_again == 0) {
		go_first = 0;
		return true;
	}
	else {
		cout << endl;
		go_first = 0;
		return false;
	}
}

//主函数
int main() {
	int init_choice;
	int go_first = 1;
	int error = 0;
	bool is_win;
	int difficulty, attempts, max_num, chance, EP;

	get_valid_int(init_choice, 1, 3, "欢迎来到猜数字游戏！\n按1为\t玩家信息\n按2为\t开始游戏\n按3为\t游戏规则\n");

	while (go_first == 1) {
		switch (init_choice) {
		case 1:
			try {
				bool file_exist = player_information();  //调用玩家信息显示函数
				if (!file_exist) {
					throw runtime_error("玩家首次游戏，未有玩家信息记录。");
				}
			}
			catch (const runtime_error&) {
				cout << "将收集玩家信息" << endl;
				error = 1;
				goto special_deal;
			}
		case 2:
			do {
				gameway_common(is_win, difficulty, attempts, max_num, chance, EP);   //调用游戏方式函数
				record_save(is_win, difficulty, attempts, max_num, chance, EP);  //调用记录保存函数
				if (is_win) {
					player_update(EP);
				}
			} while (play_again(go_first)); //询问是否再玩一次
			break;
		case 3:
			show_rules();
			get_valid_int(go_first, 0, 1, "返回请输入1，退出请输入0：");
		}

	//处理特殊情况
	special_deal:
		switch (error) {
		case 0:
			cout << "感谢游玩，期待下次再见！" << endl;
			break;
		case 1:
			cout << "请输入你的名字以初始化玩家信息：";
			string name;
			player_init(name, go_first);  //调用初始化玩家信息函数
			break;
		}
	}

	return 0;
	
}
