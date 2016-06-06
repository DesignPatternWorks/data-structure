
/*******************头文件包含****************/
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "linear_list_lk.h"


LkLinearList::LkLinearList()
{
	initList();
}

void LkLinearList::initList(void)
{
	_list = (LNode*)malloc(sizeof(LNode)); // 开辟头结点
	MALLOC_FAIL_NO_RETURN(_list);

	_list->data = 0;
	_list->pNext = NULL;

	_size = 0;
}

LkLinearList::~LkLinearList()
{
	LNode *insertNode = _list->pNext; 

	while (!NULL_PTR(insertNode)) // 与头插入法类似，每次删除head结点的直接后驱
	{
		_list->pNext = insertNode->pNext; // 修改head结点的直接后驱为待删除结点的直接后驱
		free(insertNode);              // 释放删除结点
		insertNode = _list->pNext; // 重新判断下一个待删除结点
	}

	free(_list); // 释放头结点
}


void LkLinearList::insertList(ElemType &e)
{
	LNode *newNode = (LNode*)malloc(sizeof(LNode));
	MALLOC_FAIL_NO_RETURN(newNode);

// 头插入法，每次把新元素插入到第一个位置(即作为链表的头结点的直接后驱)，此时元素在链表中顺序和插入顺序是相反的
	newNode->data = e;
	newNode->pNext = _list->pNext; // 钩链，从右到左
	_list->pNext = newNode;  //新元素插入到第一个位置(即作为链表的头结点的直接后驱)
	_size++;

// 尾插入法，每次把新元素插入到尾结点的后面(即作为链表的尾结点的直接后驱)，此时元素在链表中顺序和插入顺序是一致的
	//newNode->data = e;
	//newNode->pNext = NULL;
	//LNode *loopNode = _list;
	//while (!NULL_PTR(loopNode->pNext))
	//{
	//	loopNode = loopNode->pNext;
	//}  // 不断向后遍历找到尾结点(其pNext == NULL)
	//loopNode->pNext = newNode;
	//_size++;
}

ElemType LkLinearList::deleteList(ElemType &key)
{
	LNode *loopNode = _list;
	bool isFound = false;
	ElemType e;

	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return _list->data; // 空默认返回头结点的默认值0
	}

	while (!NULL_PTR(loopNode->pNext))
	{
		if (loopNode->pNext->data == key)
		{
			//find data域为key元素删除之
			isFound = true;
			LNode* delNode = loopNode->pNext; // 先保存删除结点的指针，待后续释放内存
			e = delNode->data; // 保存删除结点loopNode->pnext的data值
			loopNode->pNext = delNode->pNext; // 直接修改delNode（loopNode->pnext）的直接前驱loopNode结点的直接后驱
			free(delNode);
			_size--;
			return e;
		}
		loopNode = loopNode->pNext;
	}
	if (!isFound)
	{
		std::cout << "not found key: " << key << std::endl;
		return _list->data; // 未找到默认返回头结点的默认值0
	}
}

bool LkLinearList::isListEmpty(void)
{
	return (NULL == _list->pNext); // or _size == 0
}

// 获取索引为index的元素，从0开始（且不包括head结点，即从head的直接后驱结点开始算起）
ElemType& LkLinearList::getListByIndex(int index)
{
	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return _list->data; // 空情况默认返回第一个结点的data, 默认值为0
	}

	if (index > _size-1)
	{
		std::cout << "index is out of range[0," << _size-1 << "] " << std::endl;
		return _list->data; // 默认返回第一个结点的data, 默认值为0
	}

	int loopIndex = 0;  //loopIndex从0开始
	LNode *loopNode = _list;
	while (!NULL_PTR(loopNode->pNext))
	{
		if (loopIndex == index)
		{
			return loopNode->pNext->data; //loopNode->pNext为当前结点，返回该结点的值
		}
		loopNode = loopNode->pNext; // 循环下一个结点
		loopIndex++; // 记录有效结点(除head结点以外)数目+1
	}
}

// 获取第一个元素值为key的索引index，从0开始
int LkLinearList::locateList(ElemType &key)
{
	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return -1; // -1
	}

	bool isFound = false;
	int loopIndex = 0; //loopIndex从0开始
	LNode *loopNode = _list;
	while (!NULL_PTR(loopNode->pNext))
	{
		if (loopNode->pNext->data == key) //loopNode->pNext为当前结点，返回该结点的索引
		{
			isFound = true;
			return loopIndex; 
		}
		loopNode = loopNode->pNext; // 循环下一个结点
		loopIndex++; // 记录有效结点(除head结点以外)数目+1
	}

	if (!isFound)
	{
		std::cout << "not found key is " << key << std::endl;
		return _list->data; // 未找到情况默认返回第一个结点data, 默认值为0
	}
}

int LkLinearList::getListSize(void)
{
	return _size;
}

void LkLinearList::traverseList(void)
{
	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return;
	}

	std::cout << "_________begin traverse____________" << std::endl;
	int loopIndex = 0; //loopIndex从0开始
	LNode *loopNode = _list;
	while (!NULL_PTR(loopNode->pNext))
	{
		std::cout << "listNode[" << loopIndex <<"]: " << loopNode->pNext->data << "  "; //loopNode->pNext为当前结点，返回该结点的索引
		loopNode = loopNode->pNext; // 循环下一个结点
		loopIndex++; // 记录有效结点(除head结点以外)数目+1
	}
	std::cout << std::endl;
	std::cout << "_________end traverse____________" << std::endl;
}
