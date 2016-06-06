
/*******************头文件包含****************/
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "linear_list_sq.h"


SqLinearList::SqLinearList()
{
	initList();
}

void SqLinearList::initList(void)
{
	_list = (Sq_LinearList *)malloc(sizeof(Sq_LinearList));
	MALLOC_FAIL_NO_RETURN(_list);

	_list->size = 0;
	memset(_list->element, 0, sizeof(ElemType)*MAX_SQ_LINEAR_LIST);
}

SqLinearList::~SqLinearList()
{
	SAFE_DEL_PTR(_list);
}

/*
在线性表 L= (a[0]，…a[i-1]，a[i]， a[i+1]，…，a[size-1]) 中的第i(0≦i≦size-1)个位置上插入一个新结点e（包括size)，使其成为线性表：
L=(a[0]，…a[i-1]，e，a[i]，a[i+1]，…，a[size-1])
实现步骤
(1) 将线性表L中的第i个至第size-1个结点后移一个位置。
(2) 将结点e插入到结点a[i-1]之后。
(3) 线性表长度加1
*/
// index只能插入到【0，size】之间
void SqLinearList::insertList(int index, ElemType &e)
{
	ASSERT_TRUE_VOID((index >= 0) && (index <= (_list->size))); //index只能插入到已有的线性表【0，size】之间
	ASSERT_TRUE_VOID(_list->size <= MAX_SQ_LINEAR_LIST);

	// 在移动之前的原始数据a[0]~a[size-1]中插入a[index]
	for (int i = _list->size-1; i >= index; i--) // 后移（从后向前进行）
	{
		_list->element[i + 1] = _list->element[i]; // a[size-1] ~ a[index]索引范围的数据向后依次移动一位
	}
	_list->element[index] = e; // 结点e插入到结点a[index-1]之后
	_list->size++; // 线性表长度+1
}


/*
在线性表 L= (a[0]，…a[i-1]，a[i]， a[i+1]，…，a[size-1]) 中的第i(0≦i≦size-1)个位置上删除结点e，使其成为线性表：
L=(a[0]，…a[i-1]，a[i+1]，…，a[size-1])
实现步骤
(1) 将结点a[i]的值保存并删除。
(2) 将线性表L中的第i+1个至第size-1个结点前移一个位置。
(3) 线性表长度减1
*/
ElemType SqLinearList::deleteList(int index)
{
	ASSERT_TRUE_INT((index >= 0) && (index <= (_list->size-1)));
	if (isListEmpty())
	{
		std::cout << "sqence linear list is empty" << std::endl;
		return _list->element[0]; // 空情况默认返回第一个元素element[0], 默认值为0
	}

	ElemType e = _list->element[index]; // 保存待删除的元素a[index]
	for (int i = index+1; i <= _list->size-1; i++) // 从前往后依次把a[index+1]~a[size-1]向前移动一位
	{
		_list->element[i-1] = _list->element[i];
	}
	_list->size--;   //线性表减1

	return e; // 返回删除的元素
}

bool SqLinearList::isListEmpty(void)
{
	return (0 == _list->size);
}

// 获取索引为index的元素，从0开始
ElemType& SqLinearList::getListByIndex(int index)
{
	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return _list->element[0]; // 空情况默认返回第一个元素element[0], 默认值为0
	}
	if (index > _list->size-1)
	{
		std::cout << "index is out of range[0," << _list->size << "] " << std::endl;
		return _list->element[0]; // 默认返回第一个元素element[0], 默认值为0
	}

	return _list->element[index];
}

// 获取第一个元素值为key的索引index，从0开始
int SqLinearList::locateList(ElemType &key)
{
	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return -1; 
	}

	bool isFound = false;
	for (int i = 0; i < _list->size; i++)
	{
		if (key == _list->element[i])
		{
			isFound = true;
			return i;
		}
	}

	if (!isFound)
	{
		std::cout << "not found key is " << key << std::endl;
		return _list->element[0]; // 未找到情况默认返回第一个元素element[0], 默认值为0
	}
}

int SqLinearList::getListSize(void)
{
	return _list->size;
}

void SqLinearList::traverseList(void)
{
	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return;
	}

	std::cout << "_________begin traverse____________" << std::endl;
	for (int i= 0; i < _list->size; i++)
	{
		std::cout << "list[" << i << "]: " << _list->element[i] << "  ";
	}
	std::cout << std::endl;
	std::cout << "_________end traverse____________" << std::endl;
}
