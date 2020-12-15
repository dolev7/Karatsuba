#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "Long_Mult.h"
#include "Karatsuba.h"
#include "intArr.h"
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <iomanip>
static const int  MAX_SIZE = 100;
using namespace std;
using namespace Mult;
bool getN(int& n);
bool getXY(const int n, intArr& x, intArr& y, int* xclassic, int* yclassic);