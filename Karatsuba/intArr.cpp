#define _CRT_SECURE_NO_WARNINGS
#include "intArr.h"
#include <string.h>
#include <iostream>
#include <string> 
#include <vector>
#include "Karatsuba.h"
using namespace std;
namespace Mult
{
    intArr::intArr(int size)
    {
        intArray.resize(size);
    }
    void intArr::insert(int place, int value)
    {
        intArray[place] = value;
    }
    void intArr::printArr()
    {
        bool printed = false;
        bool leadZero = true;
        for (int i = 0; i < this->getSize(); i++)
        {
            if (leadZero)
            {
                if (this->intArray[i] != 0)
                    leadZero = false;
            }
            if (!leadZero)
            {
                cout << this->intArray[i];
                printed = true;
            }
        }
        if (!printed)
            cout << "0";
        cout << endl;
    }
    void intArr::shiftLeft(int toshift)
    {
            int newsize =(int)intArray.size() + toshift;
            intArray.resize(newsize);
            for (int i =(int)intArray.size(); i < newsize; i++)
                intArray[i] = 0;
    }
    void intArr::changeSize(int size)
    {
        intArray.resize(size);
    }
    int intArr::getActualSize()const
    { 
        int zeros = 0;
        int size = static_cast<int>(intArray.size());
        for (int i = 0; i < size; i++)
        {
            if (intArray[i] == 0)
                zeros++;
            else
                break;
        }
        return size-zeros;
    }

    void intArr::cutLeadingZeros()
    {
        if (this->getActualSize() == 0)
            return;
        int size = static_cast<int>(intArray.size());
        int zerocounter = 0;
        bool leadZero = true;
        for (int i = 0; i < size; i++)
        {
            if (leadZero)
            {
                if (intArray[i] != 0)
                    leadZero = false;
                else zerocounter++;
            }
        }
        for (int i = 0; i < size-zerocounter; i++)
            intArray[i] = intArray[i +zerocounter];
        intArray.resize(size-zerocounter);
    }

    intArr intArr::AddZeros(int numberOfZeros)
    {
        int sizeAfter = this->getSize() + numberOfZeros;
        intArr res(sizeAfter);
        for (int i = 0; i < numberOfZeros; i++)
        {
            res.insert(i, 0);
        }
        for (int i = numberOfZeros; i < sizeAfter; i++)
        {
            res.insert(i, this->get(i-numberOfZeros));
        }
        return res;
    }

};
