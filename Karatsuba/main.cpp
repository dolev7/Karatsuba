#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "Long_Mult.h"

using namespace std;

int main()
{
	int num1[] = { 1,2,3,4 };
	int num2[] = { 2,4,5,9 };
	int num3[8];
	LongMult(4, num1, num2);
	
}