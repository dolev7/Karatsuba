#include "mainHead.h"
int main()
{
	ofstream myfile("Measure.txt");
	int n=0;
	bool inputOK=getN(n);
	if (!inputOK)
		return 0;
	int* xclassic = new int[n];
	int* yclassic = new int[n];
	intArr x(n);
	intArr y(n);
	inputOK=getXY(n,x, y, xclassic, yclassic);
	if (!inputOK)
		return 0;
	x.cutLeadingZeros();
	y.cutLeadingZeros();
	Karatsuba calc(x,y,n);
	Multi classic(n, xclassic, yclassic);
	classic.LongMult_Print_and_TimeMeasure(myfile);
	calc.KaratsubaRec_Print_and_TimeMeasure(myfile);
	calc.KaratsubaIterative_Print_and_TimeMeasure(myfile);
	myfile.close();
	delete[] xclassic;
	delete[] yclassic;
	return 0;
}