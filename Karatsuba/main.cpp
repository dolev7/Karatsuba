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
	intArr arr1(4);
	intArr arr2(4);
	arr1.insert(0, 7);
	arr1.insert(1, 5);
	arr1.insert(2, 3);
	arr1.insert(3, 2);
	arr2.insert(0, 4);
	arr2.insert(1, 2);
	arr2.insert(2, 8);
	arr2.insert(3, 9);
	Karatsuba calc(arr1, arr2, 4);
	intArr res=calc.KaratsubaRec(arr1, arr2,4);
	res.printArr();
	//cout << "addarrs : "; calc.addArrays(arr1, arr2, 4).printArr();
	//cout << endl << "subarrs : "; calc.subtractArrays(arr1,arr2 , 4).printArr();
}