#define _CRT_SECURE_NO_WARNINGS
#include "intArr.h"
#include <string.h>
#include <iostream>
#include <string> 
#include <vector>
using namespace std;

namespace Mult
{
    intArr::intArr(int size)
    {
        for (int i = 0; i < size; i++)
            intArray.push_back(0);
    }
    intArr::~intArr()
    {
     //   delete[] intArray;
    }
    void intArr::insert(int place, int value)
    {
        intArray[place] = value;
    }
    void intArr::pushback(int value)
    {
        intArray.push_back(value);
    }
    void intArr::printArr()
    {
        for (int i = 0; i < static_cast<int>(intArray.size()); i++)
            cout << intArray[i];
    }
    void intArr::shiftLeft(int toshift)
    {
        for (int i = 0; i < toshift; i++)
            intArray.push_back(0);

    }
    int intArr::getActualSize()const
    { 
        int counter = 0;
        bool leadZero = true;
        for (int i = 0; i < static_cast<int>(intArray.size()); i++)
        {
            if (leadZero)
            {
                if (intArray[i] != 0)
                    leadZero = false;
            }
            if (!leadZero)
                counter++;
        }
        
        return counter;
    }

    void intArr::resize()
    {
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
        }//
        for (int i = 0; i < size-zerocounter; i++)
            intArray[i] = intArray[i +zerocounter];
        intArray.resize(size-zerocounter);
    }
    void intArr::AddLeadingZeros(int numberOfZeros)
    {
        for (int i = 0; i < numberOfZeros; i++)
        {
            intArray.push_back(0);
            rotate(intArray.rbegin(), intArray.rbegin() + 1, intArray.rend());
        }
    }

};
