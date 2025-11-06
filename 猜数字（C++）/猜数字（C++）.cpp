#include "gameway.h"      //游戏系统头文件
#include "record.h"       //记录系统头文件
#include "rank.h"        //段位系统头文件
#include "V_update.h"    //更新系统头文件


//询问是否再玩一次函数定义
bool play_again(int& go_first, int& error) 
{
	int is_again;
	get_valid_int(is_again, 0, 1, "你想再玩一次吗？\n(0为再来一次，1为退出)");
	if (is_again == 0) 
	{
		go_first = 0;
		return true;
	}
	else 
	{
		std::cout << std::endl;
		go_first = 0;
		error = 1;
		return false;
	}
}

//主函数
int main() 
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	version_check();
	std::cout << "按回车键进入游戏..." << std::endl;
	std::cin.get();
	curl_global_cleanup();


	int init_choice;
	int go_first = 1;
	int error = 0;
	bool is_win;
	int difficulty, attempts, max_num, chance, level, EP, episode=1, update_EP, sum_EP;
	int gameway_choice;
	std::string rank_name;

	while (go_first == 1) 
	{
		get_valid_int(init_choice, 1, 3, "欢迎来到猜数字游戏！\n按1为\t玩家信息\n按2为\t开始游戏\n按3为\t游戏规则\n你选择：");

		switch (init_choice) 
		{
		case 1:
			try 
			{
				bool file_exist = player_information();  //调用玩家信息显示函数
				if (!file_exist) 
				{
					throw std::runtime_error("玩家首次游戏，未有玩家信息记录。");
				}
			}
			catch (const std::runtime_error&) 
			{
				std::cout << "将收集玩家信息" << std::endl;
				error = 2;
				goto special_deal;
			}
			break;
		case 2:
			do 
			{
				get_valid_int(gameway_choice, 1, 3, "请选择游戏模式：\n按1为\t普通模式\n按2为\t挑战模式\n按3为\t无尽模式\n");
				if (gameway_choice == 1)
				{
					gameway_common(is_win, difficulty, attempts, max_num, chance, EP);   //调用游戏方式函数
					record_save(is_win, "普通模式", difficulty, attempts, max_num, chance, EP);  //调用记录保存函数
					update_EP = is_win ? EP : 0;
					update_all(update_EP);
				}

				else if (gameway_choice == 2)
				{
					gameway_challenge(is_win, level, attempts, max_num, chance, EP);   //调用游戏方式函数
					update_EP = is_win ? EP : -EP;
					record_save(is_win, "挑战模式", level, attempts, max_num, chance, update_EP);  //调用记录保存函数
					update_all(update_EP);
				}

				else if (gameway_choice == 3)
				{
					gameway_endless(is_win, episode, attempts, max_num, chance, EP, update_EP);   //调用游戏方式函数
					record_save(is_win, "无尽模式", episode, attempts, max_num, chance, update_EP);  //调用记录保存函数
					update_all(update_EP);
				}
			} while (play_again(go_first,error)); //询问是否再玩一次
			break;
		case 3:
			show_rules();
		}

	//处理特殊情况
	special_deal:
		switch (error) 
		{
		case 0:
			break;
		case 1:
			std::cout << "感谢游玩，期待下次再见！" << std::endl;
			break;
		case 2:
			std::cout << "请输入你的名字以初始化玩家信息：";
			std::string name;
			player_init(name, go_first);  //调用初始化玩家信息函数
			error = 0;
			break;
		}
	}

	return 0;
	
}
