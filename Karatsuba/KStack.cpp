#define _CRT_SECURE_NO_WARNINGS
#include "intArr.h"
#include <iostream>
#include "Karatsuba.h"
#include "KStack.h"
using namespace std;
namespace Mult
{
	KStack::KStack()
	{
		top = nullptr;
	}
	KStack::~KStack()
	{
		MakeEmpty();
	}
	bool KStack::IsEmpty()
	{
		return (top == nullptr);
	}
	void KStack::MakeEmpty()
	{
		Node* temp;
		while (top != nullptr)
		{
			temp = top;
			top = top->_link;
			delete temp;
		}
	}
	void KStack::Push(Karatsuba item)
	{
		top = new Node(item, top);
	}
	Karatsuba KStack::Pop()
	{
		if (IsEmpty())
			exit(1);
		Node* temp = top;
		Karatsuba item = top->_data;
		top = top->_link;
		delete temp;
		return item;
	}
};
