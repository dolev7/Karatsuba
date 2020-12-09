#pragma once
namespace Mult
{
	class Karatsuba
	{
	private:
		int _n;
		int _origSize;
		int* _x;
		int* _y;
		int* _resRow;
		int* _currentRow;
		int* _a;
		int* _b;
		int* _c;
		int* _d;

	public:
		Karatsuba(int n, int x[], int y[]);
		~Karatsuba();
		//bool inputCheck(char* n, int x[], int y[]) ;
		int* addArrays(int* arr1, int* arr2, int size);
		int* subtractArrays(int* arr1, int* arr2, int size);
		int* getLeftDigits(int* w, int sizeLeft, int sizeRight);
		int* getRightDigits(int* w, int sizeLeft);
		int* KaratsubaRec(int* x, int* y, int size);
		void print();
	};
}