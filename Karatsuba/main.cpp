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
int main()
{
	ofstream myfile("Measure.txt"); // The name of the file
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
			return 0;
		}
		if (d == '0' && i == 0)
			leadzero = true;
		ntoget[i] =d-'0';
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
		return 0;
	}
	int n=0;
	int multiply = 1;
	for (int k = strlen(ntoget)-1; k >=0 ; k--)
	{
		 n += ntoget[k] * multiply;
		multiply *= 10;
	}
	int* xclassic = new int[n];
	int* yclassic = new int[n];
	intArr x(n);
	intArr y(n);
	int current;
	char c;
	for (int i = 0; i < n; i++)
	{
		c = getchar();
		if (c < '0' || c> '9')
		{
			cout << "wrong output";
			return 0;
		}
		current = c - '0';
		x.insert(i,current);
		xclassic[i] = current;
	}
	c=getchar(); //skip \n
	if (c != '\n')
	{
		cout << "wrong output";
		return 0;
	}
	for (int i = 0; i < n; i++)
	{
		c = getchar();
		current = c - '0';
		y.insert(i,current);
		yclassic[i] = current;
	}
	c = getchar();
	if (c != '\n')
	{
		cout << "wrong output";
		return 0;
	}
	x.cutLeadingZeros();
	y.cutLeadingZeros();
	
	Karatsuba calc(x,y,n);
	bool inputOK = true;
	if (inputOK)
	{
		Multi classic(n, xclassic, yclassic);
		classic.LongMult_Print_and_TimeMeasure("mesure");
		calc.KaratsubaRec_Print_and_TimeMeasure(myfile);
		
		//cout << "Karatsuba(iterative) : x * y = "; 
		//printREC.printArr();
	}
	myfile.close();
	return 0;
}