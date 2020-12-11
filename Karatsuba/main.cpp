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
//#include <iostream>
//#include <cstdlib>
//#include <vector>
//	using std::vector;
//	using std::cout;
//	using std::endl;
//
//	class A {
//	private:
//		vector<int> vec;
//	public:
//		void AddToVector(int i)
//		{
//			vec.push_back(i);
//		}
//		void FunctionA()
//		{
//			cout << vec.size() << endl;
//		}
//		void FunctionB(int x, int y)
//		{
//			AddToVector(x);
//			AddToVector(y);
//		}
//	};

	/*int main() {
		A a;
		int x = 23, y = 3;
		a.FunctionB(2, 2);
		a.FunctionA();
		return 0;
	}*/



	intArr arr1(2);
	intArr arr2(2);
	arr1.insert(0, 1);
	arr1.insert(1, 2);
	//arr1.insert(2, 3);
	//arr1.insert(3, 2);
	arr2.insert(0, 3);
	arr2.insert(1, 4);
	//arr2.insert(2, 8);
	//arr2.insert(3, 9);
	Karatsuba calc(arr1, arr2, 4);
	intArr res=calc.KaratsubaRec(arr1, arr2,2);
	res.printArr();
	//cout << "addarrs : "; calc.addArrays(arr1, arr2, 4).printArr();
	//cout << endl << "subarrs : "; calc.subtractArrays(arr1,arr2 , 4).printArr();
	//
}