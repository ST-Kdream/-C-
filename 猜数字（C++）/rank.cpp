#include"rank.h"


	Rank::Rank(string name, int EP)
	{
		rank_name = name;
		rank_EP = EP;
	}

	string Rank::update_rank(int sum_EP, const vector<Rank> arr)
	{
		try
		{
			int* sum_EP_ptr = &sum_EP;
			if (sum_EP_ptr == nullptr)
				throw runtime_error("更新函数运行失败的系列错误！");
		}
		catch (const exception& e)
		{
			exit(11);
		}

		string each_name;

		for (Rank each_arr : arr)
		{
			if (each_arr.rank_EP < sum_EP)
				each_name = each_arr.rank_name;
			else
				break;
		}
		if (each_name.empty())
			return "预备队员";
		else
			return each_name;
	}

vector <Rank> rankings =
{
	{"迷雾探索者",0},
	{"数字探员",100},
	{"线索捕手",600},
	{"精准捕手",2200},
	{"逻辑侦探",7000},
	{"数字督察",12000},
	{"推理总长",60000},
	{"猜局主宰",150000},
	{"终极破译者",500000},
	{"时空王者",1200000}
};
