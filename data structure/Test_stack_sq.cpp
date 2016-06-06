#include "stdafx.h"
#include "Test_stack_sq.h"
#include "DSComm.h"

void testStackSq(void)
{
	std::cout << "begin dyn stack sequence table test:" << std::endl;

	DynSqStack s;
	ElemType a[] = { 0,1,2,3,4,5,6,7,8,9};
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

	std::cout << "begin static stack sequence table test:" << std::endl;
	StaticSqStack s2;

	for (i = 0; i < ARRAY_SIZE(a); i++)
	{
		s2.pushStack(a[i]);
	}
	std::cout << "size is :" << s2.getStackSize() << std::endl;
	s2.traverseStack(); // 0~9
	e = s2.getStackByIndex(4);
	std::cout << "getStackByIndex(4) is: " << e << std::endl; // 4

	locateIndex = s2.locateStack(a[4]);
	std::cout << "locateStack(a[4]) is: " << locateIndex << std::endl; // 4

	for (i = ARRAY_SIZE(a) - 1; i >= 0; i--)
	{
		e = s2.popStack();
		std::cout << "stack pop element is: " << e << std::endl; // 9~0
	}

	std::cout << "size is :" << s2.getStackSize() << std::endl; // 0
	s2.traverseStack(); //empty

	s2.popStack(); //empty
}