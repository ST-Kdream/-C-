#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<memory>

class Rank
{
public:
	std::string rank_name;
	int rank_EP;

	Rank(std::string name, int EP);
	
	static std::string update_rank(int sum_EP, const std::vector<Rank> arr);
	
};

extern std::vector<Rank> rankings;