#pragma once
#include <chrono>
#include <fstream>
#include <iomanip>
using namespace std;
namespace Mult
{
	class Multi
	{
	private:
		int _n;
		int _origSize;
		int* _x; 
		int* _y;
		int* _resRow;
		int* _currentRow;

	public:
		Multi(int n, int x[], int y[]);
		~Multi();
		void LongMult();
		void multX_Ydigit(int yDig, int start);
		void addRows(int start);
		void print();
		void LongMult_Print_and_TimeMeasure(ofstream& myfile);
	};
}