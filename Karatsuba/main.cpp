#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "Long_Mult.h"
#include "Karatsuba.h"
#include "intArr.h"
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <iomanip>
static const int  MAX_SIZE = 100;
using namespace std;
using namespace Mult;
bool getN(int& n);
bool getXY(const int n,intArr& x, intArr& y, int* xclassic, int* yclassic);
int main()
{
	ofstream myfile("Measure.txt");
	int n=0;
	bool inputOK=getN(n);
	if (!inputOK)
		return 0;
	int* xclassic = new int[n];
	int* yclassic = new int[n];
	intArr x(n);
	intArr y(n);
	inputOK=getXY(n,x, y, xclassic, yclassic);
	if (!inputOK)
		return 0;
	x.cutLeadingZeros();
	y.cutLeadingZeros();
	Karatsuba calc(x,y,n);
	Multi classic(n, xclassic, yclassic);
	classic.LongMult_Print_and_TimeMeasure(myfile);
	calc.KaratsubaRec_Print_and_TimeMeasure(myfile);
		//cout << "Karatsuba(iterative) : x * y = "; 
		//printREC.printArr();
	myfile.close();
	return 0;
}
bool getN(int& n)
{
	char d;
	char ntoget[MAX_SIZE];
	getchar();//skip space
	d = getchar();
	int i = 0;
	bool leadzero = false;
	while (d != '\n')
	{
		if (d < '0' || d> '9')
		{
			cout << "wrong output";
			return false;
		}
		if (d == '0' && i == 0)
			leadzero = true;
		ntoget[i] = d - '0';
		d = getchar();
		i++;
	}
	ntoget[i] = '\0';
	if (leadzero)
	{
		if (i == 1)
			cout << "you have entered n=0 therefore x and y are empty numbers";
		else
			cout << "wrong output";
		return false;
	}
	int multiply = 1;
	for (int k = i - 1; k >= 0; k--)
	{
		n += ntoget[k] * multiply;
		multiply *= 10;
	}
	return true;
}
bool getXY(const int n,intArr& x, intArr& y, int* xclassic, int* yclassic)
{
	int current;
	char c;
	for (int i = 0; i < n; i++)
	{
		c = getchar();
		if (c < '0' || c> '9')
		{
			cout << "wrong output";
			return false;
		}
		current = c - '0';
		x.insert(i, current);
		xclassic[i] = current;
	}
	c = getchar(); //skip \n
	if (c != '\n')
	{
		cout << "wrong output";
		return false;
	}
	for (int i = 0; i < n; i++)
	{
		c = getchar();
		if (c < '0' || c> '9')
		{
			cout << "wrong output";
			return false;;
		}
		current = c - '0';

		y.insert(i, current);
		yclassic[i] = current;
	}
	c = getchar();
	if (c != '\n')
	{
		cout << "wrong output";
		return false;;
	}
	return true;
}