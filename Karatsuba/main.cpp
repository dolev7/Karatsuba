#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "Long_Mult.h"
#include "Karatsuba.h"
#include "intArr.h"
using namespace std;
using namespace Mult;
int main()
{
	intArr arr1(1);
	intArr arr2(1);
	arr1.insert(0, 5);
	arr2.insert(0, 4);
	Karatsuba calc(arr1, arr2, 1);
	intArr res=calc.KaratsubaRec(arr1, arr2,1);
	res.printArr();
}