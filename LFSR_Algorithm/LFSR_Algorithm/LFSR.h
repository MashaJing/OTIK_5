#pragma once
#include <vector>
#include <algorithm>
#include <map>

class LFSR {
	
public:
	
	std::vector<int> A; //Массив коэффициентов а
	std::map<int, double> Xi2_quantile = { //для alpha = 0.05 и r = [1, 16] приведены значения (1-alpha)-квантили X^2-распределния
		{1, 3.841},
	{2, 5.991 },
	{3, 7.815},
	{4, 9.488},
	{5, 11.07},
	{6, 12.592},
	{7, 14.067},
	{8, 15.507},
	{9, 16.919},
	{10, 18.307},
	{11, 19.675},
	{12, 21.026},
	{13, 22.362},
	{14, 23.685},
	{15, 24.996},
	{16, 26.296}
	};

	LFSR() {};

	std::vector<int> Generate(int &seed);
	bool Check_Pirsons_criterion(std::vector<int> sequence);
	int into_decimal(std::vector<int> a);
	std::vector<int> into_binary(int a);
};

int sum_mod2(int a, int b);


