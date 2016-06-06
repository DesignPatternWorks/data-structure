#include "stdafx.h"
#include "Test_stack_lk.h"
#include "DSComm.h"

void testStackLk(void)
{
	std::cout << "begin stack link table test:" << std::endl;

	LkStack s;
	ElemType a[] = { 0,1,2,3,4,5,6,7,8,9 };
	ElemType e;
	int locateIndex = 0;
	int i = 0;

	for (i = 0; i < ARRAY_SIZE(a); i++)
	{
		s.pushStack(a[i]);
	}
	std::cout << "size is :" << s.getStackSize() << std::endl;
	s.traverseStack(); // 0~9
	e = s.getStackByIndex(4);
	std::cout << "getStackByIndex(4) is: " << e << std::endl; // 4

	locateIndex = s.locateStack(a[4]);
	std::cout << "locateStack(a[4]) is: " << locateIndex << std::endl; // 4

	for (i = ARRAY_SIZE(a) - 1; i >= 0; i--)
	{
		e = s.popStack();
		std::cout << "stack pop element is: " << e << std::endl; // 9~0
	}

	std::cout << "size is :" << s.getStackSize() << std::endl; // 0
	s.traverseStack(); //empty

	s.popStack(); //empty

	std::cout << std::endl;

}