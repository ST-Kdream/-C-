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
				throw runtime_error("���º�������ʧ�ܵ�ϵ�д���");
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
			return "Ԥ����Ա";
		else
			return each_name;
	}

vector <Rank> rankings =
{
	{"����̽����",0},
	{"����̽Ա",100},
	{"��������",600},
	{"��׼����",2200},
	{"�߼���̽",7000},
	{"���ֶ���",12000},
	{"�����ܳ�",60000},
	{"�¾�����",150000},
	{"�ռ�������",500000},
	{"ʱ������",1200000}
};
