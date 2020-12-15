#pragma once
#include "Karatsuba.h"

namespace Mult
{
	class Item
	{
	public:
		intArr _x;
		intArr _y;
		int _n;
		intArr _returnVal;
		int _line;
		intArr ac;
		intArr z2;
		intArr abcd;
		intArr z0;
		intArr z1z0z2;
		intArr restemp;
		Item(intArr x, intArr y, int n,intArr res, int line)
		{
			_x = x;
			_y = y;
			_n = n;
			_returnVal = res;
			_line = line;
		}
		Item() { _n = 0; _line = 0; };
	};
	class Node
	{
		friend class KStack;
	private:
		Node* _link;
		Item _data;
		public:
		Node(Item data, Node* link)
		{
			_data = data;
			_link = link;
		}
	};
	class KStack
	{
	private:
		Node* top;
	public:
		KStack();
		~KStack();
		void MakeEmpty();
		bool IsEmpty();
		void Push(Item item);
		Item Pop();
	};
}
