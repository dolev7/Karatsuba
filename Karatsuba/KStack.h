#pragma once
#include "Karatsuba.h"

namespace Mult
{
	class Node
	{
		friend class KStack;
	private:
		Karatsuba _data;
		Node* _link;
		public:
		Node(Karatsuba data, Node* link)
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
		void Push(Karatsuba item);
		Karatsuba Pop();
		Karatsuba Top();
	};
}
