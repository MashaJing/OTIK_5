#include "LFSR.h"

std::vector<int> LFSR::Generate(int &seed)
{
	std::vector<int> S;
	std::vector<int> result;

	S = into_binary(seed);
	if (S.size() != A.size()) throw std::exception("The start number is out of range");

	std::vector<int> S_new;
	for (int i = 0; i < S.size(); i++) S_new.push_back(0);

	int sum = 0;
	int t = 0; 
	
	//for (int t = 0; t <  6; t++)
	do
	{
		if (t == 1) seed = result.at(0);
		for (int i = 0; i < S.size() - 1; i++)
		{
			S_new[i] = S[i + 1];
			sum = sum_mod2(sum, A[i] * S[i]);
		}
		sum = sum_mod2(sum, A[A.size()-1] * S[S.size() -1 ]);
		S_new[S_new.size() - 1] = sum;
		S = S_new;
		sum = 0;
		result.push_back( into_decimal(S_new));
		
		t++;
	} while ((result[result.size() - 1] != seed)/*&&(t <129)*/);

	if (t == 1) seed = t;
	else seed = t - 1;

	return result;
}

bool LFSR::Check_Pirsons_criterion(std::vector<int> sequence)
{
	int M = 0;
	int S = 0;
	int K;

	for (int elem : sequence) if (elem > M) M = elem; //находим максимальный элемент
	
	if (M < 10) K = M; //определяем число отрезков К
	else K = 5 * log10(M);

	if (K == 0) return 1;
	double p = 1.0 / K; //можно ссразу определить вероятность попадания в К-ый отрезок, т.к. распределение равномерно

	for (int i = 0; i < sequence.size(); i++)
	{
		double vi = 0;
		for (int elem : sequence)
			if (elem > K * i && elem < K * (i + 1)) vi++;
		S += pow(((double) vi/ sequence.size() - p),2);

	}
	S *= sequence.size() * K;
	
	return (S < Xi2_quantile[K - 1])? 1 : 0;
}

int sum_mod2(int a, int b)
{
	bool res;
	if ((a + b == 2) || (a + b == 0)) return 0;
	else if (a + b == 1) return 1;

}

//using namespace std;

std::vector<int> LFSR::into_binary(int a)
{
	std::vector<int> result;
	
	if (a == 0)
	{
		while (result.size() < A.size()) result.push_back(0);
	}
	else {
		while (a != 1)
		{
			result.push_back(a % 2);
			a /= 2;
		}
		result.push_back(1);
		while (result.size() < A.size()) result.push_back(0);
		std::reverse(result.begin(), result.end());
	}
	
	return result;
}

int LFSR::into_decimal(std::vector<int> a)
{
	int result = 0;
	int fac = 1;
	for (int i : a)
	{
		result += (fac * i);
		fac *= 2;
	}
	return result;
}