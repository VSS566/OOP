#include <iostream>

#include <LinkedList.hpp>

int main()
{
	LinkedList list{ 1,2,3,4 };
	list.add(5);

	std::cout << list[4];

	return 0; 
}