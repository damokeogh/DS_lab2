#include <iostream>
#include "SLinkedList.h"
#include "pch.h"


int main() {


	SLinkedList<int, SListIterator<int>> list;	
	list.insertLast(20);
	list.insertLast(10);
	list.insertLast(5);
	

	SListIterator<int> start = list.begin();
	
	std::cout << "First element: " << *start << std::endl;

	std::cout << list.size() << std::endl;

	/*++start;
	list.insertBefore(start, 15);
	start = list.begin;

	for (int i = 0; i < list.size; i++)
	{
		std::cout << *start << std::endl;
		++start;

	}*/
	
	system("PAUSE");
}


