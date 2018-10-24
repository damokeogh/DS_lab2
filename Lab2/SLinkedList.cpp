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

	//test code for q1
	SListIterator<int> testIter = list.begin();
	++testIter;
	list.insertBefore(testIter, 15);
	testIter = list.begin();
	for (int i = 0; i < list.size(); i++)
	{
		std::cout << *testIter << std::endl;
		++testIter;
	}

	//test code for Q2
	list.reverse();
	testIter = list.begin();
	for (int i = 0; i < list.size(); i++)
	{
		std::cout << *testIter << std::endl;
		++testIter;
	}

	//test code for Q3
	SListIterator<int> testIter2 = list.begin();
	++testIter;
	list.makeNewHead(testIter2);
	testIter = list.begin();
	for (int i = 0; i < list.size(); i++)
	{
		std::cout << *testIter << std::endl;
		++testIter;
	}

	system("PAUSE");
}


