#include "mainHead.h"
bool getN(int& n)
{
	char d;
	char ntoget[MAX_SIZE];
	d=getchar();//skip space
	while(d==' ')
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
			cout << "Long multiplication : x * y = 0" << endl << "Karatsuba(recursive) : x * y = 0" <<endl<< "Karatsuba(iterative) : x * y = 0";
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
bool getXY(const int n, intArr& x, intArr& y, int* xclassic, int* yclassic)
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