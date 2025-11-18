#include "gameway.h"

std::stringstream gameway_judge(int guess,int answer,int chance, int attempts)
{
	std::stringstream ss;
	if (guess > answer) 
			ss << "猜大了，还有" << (chance - attempts) << "次机会，" << "请再试一次：" << std::endl;
	else if (guess < answer) 
			ss << "猜小了，还有" << (chance - attempts) << "次机会，" << "请再试一次：" << std::endl;
	else
	{
		ss << "恭喜你，猜对了！\n" << "你一共猜了" << attempts << "次" << std::endl;
	}
	return ss;
}

	
//普通模式函数定义
void gameway_common(int& difficulty,int& max_num, int& chance , int& EP) 
{
	//难度设置
	class DifficultySetting 
	{
	public:
		int max_num;
		int chance;
		int EP;
		std::string name;

		DifficultySetting(int Difficulty_max_num, int Difficulty_chance, int Difficulty_EP, std::string difficulty_name) {
			max_num = Difficulty_max_num;
			chance = Difficulty_chance;
			EP = Difficulty_EP;
			name = difficulty_name;
		}
	};
	
	// 定义并初始化难度参数
	std::vector <DifficultySetting> difficulty_settings = 
	{
	{100,10, 5, "简单"},
	{100, 7, 10, "普通"},
	{2000, 15, 15, "困难"},
	{10000, 20, 20, "噩梦"},
	{500000, 25, 30, "地狱"},
	};
	
    //根据选择设置参数
	DifficultySetting chosen_difficulty = difficulty_settings[difficulty - 1];
	max_num = chosen_difficulty.max_num;
	chance = chosen_difficulty.chance;
	EP = chosen_difficulty.EP;

}

//挑战模式函数定义
void gameway_challenge(int& level,int& max_num, int& chance, int& EP)
{
		
	//根据选择设置参数
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

	// 定义并初始化难度参数
	std::vector <LevelSetting> level_settings = 
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

	//根据选择设置参数
	max_num = level_settings[level - 1].max_num;
	chance = level_settings[level - 1].chance;
	EP = level_settings[level - 1].EP;
	level = level_settings[level - 1].level_num;
	
}

//无尽模式函数定义
void gameway_endless(bool& is_win, int& episode, int& attempts, int& max_num, int& chance, int& EP, int& update_EP)
{

	update_EP = 0;
	is_win = true;
	episode = 1;
	max_num = 100;
	chance = 10;
	EP = 5;
}


// 获取难度设置的描述信息
QString getdiffinfo(int difficulty, int max_num, int chance, int EP)
{
	QStringList difficultyNames = { "简单", "普通", "困难", "噩梦", "地狱", "自定义" };

	if (difficulty >= 1 && difficulty <= 6) {
		return QString("难度: %1\n数字范围: 1-%2\n尝试次数: %3\n奖励经验: %4").arg(difficultyNames[difficulty - 1]).arg(max_num).arg(chance).arg(EP);
	}

	return "未知难度";
}

// 获取等级设置的描述信息
QString getlevelinfo(int level, int max_num, int chance, int EP)
{
	return QString("等级: %1\n数字范围: 1-%2\n尝试次数: %3\n奖励经验: %4").arg(level).arg(max_num).arg(chance).arg(EP);
}

QString endlessgammemessage(int episode)
{
	if (episode <= 6) 
	{
		return "继续前进！";
	}
	else if (episode <= 15) 
	{
		return "不错啊，继续加油！";
	}
	else if (episode <= 30) 
	{
		return "你真厉害，继续保持！";
	}
	else if (episode <= 40) 
	{
		return "上难度了，继续前进！";
	}
	else if (episode <= 55) 
	{
		return "不可思议，你居然还在继续！";
	}
	else if (episode <= 75) 
	{
		return "你是无敌的吧！";
	}
	else if (episode <= 100) 
	{
		return "史诗级别的挑战！";
	}
	else 
	{
		return "享受无尽的挑战吧！";
	}
}