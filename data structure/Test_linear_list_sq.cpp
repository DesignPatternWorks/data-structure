
/*******************头文件包含****************/
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "Test_linear_list_sq.h"
#include "linear_list_sq.h"

/*******************宏定义****************/

/*******************数据类型定义****************/

/*******************变量声明****************/

/*******************内部函数声明****************/

/*******************外部函数声明****************/


/*******************函数实现****************/

void testLinearListSq(void)
{
	std::cout << "begin list sequence table test:" << std::endl;

	SqLinearList s;
	ElemType a[] = {0,1,2,3,4,5,6,7,8,9};
	ElemType e;
	int locateIndex = 0;
	for (int i = 0; i < ARRAY_SIZE(a); i++)
	{
		s.insertList(i, a[i]);
	}
	std::cout << "size is :" << s.getListSize() << std::endl;
	s.traverseList(); // 0~9
	e = s.getListByIndex(4);
	std::cout << "getListByIndex(4) is: " << e << std::endl; // 4

	locateIndex = s.locateList(a[4]); 
	std::cout << "locateList(a[4]) is: " << locateIndex << std::endl; // 4

	for (int i = ARRAY_SIZE(a)-1; i >= 0; i--)
	{
		e = s.deleteList(i);
		std::cout << "list delete element is: " << e << std::endl; // 9~0
	}

	std::cout << "size is :" << s.getListSize() << std::endl; // 0
	s.traverseList(); //empty

	s.deleteList(0); //empty
}