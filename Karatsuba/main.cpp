#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "Long_Mult.h"
#include "Karatsuba.h"
#include "intArr.h"
#include <vector>
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
	intArr x(n);
	intArr y(n);
	int current;
	for (int i = 0; i < n; i++)
	{
		cin >> current;
		x.insert(i,current);
	}
	for (int i = 0; i < n; i++)
	{
		cin >> current;
		y.insert(i,current);
	}
	x.resize();
	y.resize();
	x.printArr(); cout << endl;
	y.printArr(); cout << endl;
		
	Karatsuba calc(x,y,n);
	intArr res=calc.KaratsubaRec(x, y,n);
	res.printArr();
	cout << endl;
}