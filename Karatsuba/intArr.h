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
        intArr AddZeros(int numberOfZeros);
        void insert(int place, int value);
        void pushback(int value);
        int getActualSize()const;
        int getSize() { return (int)intArray.size(); }
        int get(int place)const { return intArray[place]; }
        void printArr();
        void resize();
        void shiftLeft(int toshift);
 //       void AddLeadingZeros(int numberOfZeros);
    };
}
