#include <iostream>
#include <fstream>
#include "LFSR.h"

using namespace std;

int main()
{
	try {
		ifstream Data;
		
		char* DATA;
		bool enterfile = false;
		char filename[100];

		while (!enterfile)//пока не введено имя существующего файла
		{
			cout << "Enter the file name: ";
			cin >> filename;
			Data.open(filename);
			if (Data.is_open()) enterfile = true;
			else if (filename[0] == '0') return 0;
			else cout << "This one does not exist! Try again or enter 0 to exit.\n\n";

		}
		
		//if (!Data.is_open()) throw exception("Data1: file not found...");

		LFSR G1;
		//считываем последовательность коэффициентов a
		int a;
		do
		{
			Data >> a;
			G1.A.push_back(a);

		} while (Data.peek() != '\n');

		//считываем вектор стартовых значений 

		if (Data.peek() != (char) Data.peek()) throw exception("File contains invalid simbols...");

		Data >> a;
		
		Data.close();
		
		
		
		ofstream fout("Result.txt");
		a = abs(a);
		vector<int> result = G1.Generate(a);

		fout << "Generated sequence: " << endl;

		for (int j = 0; j < result.size(); j++)
		{
			fout << result[j];
			fout << " ";
		}

		fout << endl;
		fout << "T = ";
		fout << a;
		fout << "\nPirsons criterion: ";
		fout << G1.Check_Pirsons_criterion(result) << endl;
		fout.close();

		cout << "\nReady! Watch file Result.txt for more details..." << endl;
		system("pause");
		return 0;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	
}