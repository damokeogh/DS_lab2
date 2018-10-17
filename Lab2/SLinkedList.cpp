#include <iostream>
#include "SLinkedList.h"
#include "pch.h"


int main() {


	SLinkedList<int, SListIterator<int>> list;	
	list.insertFirst(20);
	list.insertFirst(10);
	list.insertFirst(5);

	SListIterator<int> start = list.begin();
	
	std::cout << "First element: " << *start << std::endl;

	std::cout << list.size() << std::endl;
	
	system("PAUSE");
}


