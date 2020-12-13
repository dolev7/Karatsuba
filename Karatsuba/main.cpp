#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "Long_Mult.h"
#include "Karatsuba.h"
#include "intArr.h"
#include <vector>
static int MAX_SIZE = 100;
using namespace std;
using namespace Mult;
int main()
{
	int n;
	cin >> n;
	if (n == 0)
	{
		cout << "0";
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
		current = c-48;
		x.insert(i,current);
		xclassic[i] = current;
	}
	getchar(); //skip \n
	for (int i = 0; i < n; i++)
	{
		c = getchar();
		current = c - 48;
		y.insert(i,current);
		yclassic[i] = current;
	}
	x.resize();
	y.resize();
		
	Karatsuba calc(x,y,n);
	bool inputOK = true;
	char a[2]="d";
	inputOK=calc.inputcheck(x,y,a);
	if (inputOK)
	{
		Multi classic(n, xclassic, yclassic);
		classic.LongMult();
		classic.print();
		
		cout << "Karatsuba(recursive) : x * y = " ; 
		intArr printREC=calc.KaratsubaRec(x, y, n);
		printREC.printArr();

		cout << "Karatsuba(iterative) : x * y = ";
		
	}
}