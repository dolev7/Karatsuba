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
	intArr arr1(2);
	intArr arr2(2);
	arr1.insert(0, 1);
	arr1.insert(1, 2);
	arr2.insert(0, 3);
	arr2.insert(1, 4);
	Karatsuba calc(arr1, arr2, 2);
	intArr res=calc.KaratsubaRec(arr1, arr2,2);
	res.printArr();
}