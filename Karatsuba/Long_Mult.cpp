#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <math.h>
#include "Long_Mult.h"

using namespace std;

namespace Mult
{
	Multi::Multi(int n, int x[], int y[])
	{
		_origSize = n;
		_n = n;
		_x = x;
		_y = y;
		int initsize = 2 * n;
		_resRow = new int[initsize];
		_currentRow = new int[initsize];
		for (int i = 0; i < 2 * n; i++)
			_resRow[i] = _currentRow[i] = 0;
	}
	Multi::~Multi()
	{
		  delete[] _currentRow;
		  delete[] _resRow;
	}
	void Multi::LongMult()
	{
		for (int i = 0; i < _n; i++)
		{
			if (_y[_n - i - 1] != 0)
			{
				multX_Ydigit(_y[_n - i - 1], (2 * _n - i - 1));
				addRows(2 * _n - i - 1);
			}
		}
	}
	void Multi::LongMult_Print_and_TimeMeasure(ofstream& myfile)
	{
		auto start = chrono::high_resolution_clock::now();
		ios_base::sync_with_stdio(false);
		this->LongMult();
		auto end = chrono::high_resolution_clock::now();
		double time_taken = static_cast<double>(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
		time_taken *= 1e-9;
		
		myfile << "Time taken by function <Long Multipication> is : " << fixed
			<< time_taken << setprecision(9);
		myfile << " sec" << endl;
		this->print();
	}
	void Multi::multX_Ydigit(int yDig, int start)
	{
		_currentRow[start] = 0;
		for (int k = 0, i = start; k < _n; k++, i--)
		{
			_currentRow[i] += _x[_n - k - 1] * yDig;
			_currentRow[i - 1] = _currentRow[i] / 10;
			_currentRow[i] %= 10;

		}
	}
	void Multi::addRows(int start)
	{
		for (int k = 0, i = start; k <= _n; k++, i--)
		{
			_resRow[i] += _currentRow[i];
			_resRow[i - 1] += _resRow[i] / 10;
			_resRow[i] %= 10;
		}
	}
	void Multi::print()
	{
		bool printed = false;
		bool leadZero = true;
		cout << "Long multiplication : x * y = ";
		for (int i = 0; i < 2 * _n; i++)
		{
			if (leadZero)
			{
				if (_resRow[i] != 0)
					leadZero = false;
			}
			if (!leadZero)
			{
				cout << _resRow[i];
				printed = true;
			}
		}
		if (!printed)
			cout << "0";
		cout << endl;
	} 
}
