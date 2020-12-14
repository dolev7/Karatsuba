#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "Long_Mult.h"
#include "Karatsuba.h"
#include "intArr.h"
#include <vector>
static const int  MAX_SIZE = 100;
using namespace std;
using namespace Mult;
int main()
{
	//char ntoget[MAX_SIZE];
	//char k = getchar()-48;
	//int i = 0;
/*	if (k == 0)
	{
		cout << "wrong input - N With leading zero." <<endl;
		return 0;
	}
	while (k != 0)
	{
		ntoget[i]=k-48
	}*/
	int n;
	cin >> n;
	if (n == 0)
	{
		cout << "You have entered empty numbers";
		return 0;
	}
	getchar();// skip "\n"
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
		current = c-48;
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
		current = c - 48;
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
		classic.LongMult();
		classic.print();
		cout << "Karatsuba(recursive) : x * y = " ; 
		intArr printREC=calc.KaratsubaRec(x, y, n);
		printREC.printArr();
		cout << "Karatsuba(iterative) : x * y = "; 
		printREC.printArr();
	}
}