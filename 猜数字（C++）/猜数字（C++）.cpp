#include "gameway.h"      //游戏方式函数头文件

using namespace std;

bool play_again() {
	int is_again;
	get_valid_int(is_again, 0, 1, "你想再玩一次吗？\n(0为再来一次，1为退出)");
	if (is_again == 0) {
		return true;
	}
	else {
		cout << "感谢游玩，期待下次再见！" << endl;
		return false;
	}
}



//主函数
int main() {
	bool is_win;
	int difficulty, attempts, max_num, chance;
	do {
		gameway(is_win, difficulty, attempts, max_num, chance);   //调用游戏方式函数
		record_save(is_win,difficulty, attempts, max_num, chance);  //调用记录保存函数
	} while (play_again()); //询问是否再玩一次
	
	return 0;
}
