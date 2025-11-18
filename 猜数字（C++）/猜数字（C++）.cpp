#include "gameway.h"      //游戏系统头文件
#include "record.h"       //记录系统头文件
#include "rank.h"        //段位系统头文件
#include "V_update.h"    //更新系统头文件
#include "Qt_gui.h"      //gui文件

bool is_win,endless=false;
int difficulty, attempts = 0, max_num = 100, chance = 10, level, EP = 5, episode = 1, update_EP=0, sum_EP = 0;
int mode;
std::string rank_name;

//主函数
int main(int argc,char* argv[])
{
	
	QApplication app(argc, argv);

	app.setApplicationName("猜数字");
	app.setApplicationVersion("4.0.0");
	app.setOrganizationName("ST-Kdream");

	QFont defaultFont("Microsoft YaHei", 9);  
	app.setFont(defaultFont);

	Mainwindow* mainwindow = new Mainwindow(nullptr);
	CheckVwin checkVwin(mainwindow);
	checkVwin.show();

	return app.exec();
	
}
