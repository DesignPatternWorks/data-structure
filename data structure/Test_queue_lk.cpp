#include "stdafx.h"
#include "Test_queue_lk.h"
#include "DSComm.h"

void testQueueLk(void)
{
	std::cout << "begin  queue link table test:" << std::endl;

	LkQueue s;
	ElemType a[] = { 0,1,2,3,4,5,6,7,8,9 };
	ElemType e;
	int locateIndex = 0;
	int i = 0;

	for (i = 0; i < ARRAY_SIZE(a); i++)
	{
		s.pushQueue(a[i]);
	}
	std::cout << "size is :" << s.getQueueSize() << std::endl;
	s.traverseQueue(); // 0~9
	e = s.getQueueByIndex(4);
	std::cout << "getQueueByIndex(4) is: " << e << std::endl; // 4

	locateIndex = s.locateQueue(a[4]);
	std::cout << "locateQueue(a[4]) is: " << locateIndex << std::endl; // 4

	for (i = ARRAY_SIZE(a) - 1; i >= 0; i--)
	{
		e = s.popQueue();
		std::cout << "queue pop element is: " << e << std::endl; // 9~0
	}

	std::cout << "size is :" << s.getQueueSize() << std::endl; // 0
	s.traverseQueue(); //empty

	s.popQueue(); //empty

	std::cout << std::endl;

}