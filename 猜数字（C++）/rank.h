#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<memory>

using namespace std;

class Rank
{
public:
	string rank_name;
	int rank_EP;

	Rank(string name, int EP);
	
	static string update_rank(int sum_EP, const vector<Rank> arr);
	
};

extern vector<Rank> rankings;