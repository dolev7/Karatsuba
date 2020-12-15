#pragma once
#include "Karatsuba.h"

namespace Mult
{
	struct Item
	{
		Karatsuba k;
		intArr returnVal;
		int line;
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
		//Node* Top();
	};
}
