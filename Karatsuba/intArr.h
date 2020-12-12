#pragma once
#include <vector>
using namespace std;
namespace Mult
{
    class intArr
    {
    private:
        vector <int> intArray;
    public:
        intArr(int size);
        intArr() {};
        ~intArr();
        void insert(int place, int value);
        void pushback(int value);
        int getActualSize()const;
        int getSize() { return intArray.size(); }
        int get(int place)const { return intArray[place]; }
        //int getback() { return intArray.back(); }
        void printArr();
        void resize();
        void shiftLeft(int toshift);
        void AddLeadingZeros(int numberOfZeros);
    };
}
