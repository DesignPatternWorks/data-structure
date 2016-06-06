
/*******************ͷ�ļ�����****************/
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
�����Ա� L= (a[0]����a[i-1]��a[i]�� a[i+1]������a[size-1]) �еĵ�i(0�Qi�Qsize-1)��λ���ϲ���һ���½��e������size)��ʹ���Ϊ���Ա�
L=(a[0]����a[i-1]��e��a[i]��a[i+1]������a[size-1])
ʵ�ֲ���
(1) �����Ա�L�еĵ�i������size-1��������һ��λ�á�
(2) �����e���뵽���a[i-1]֮��
(3) ���Ա��ȼ�1
*/
// indexֻ�ܲ��뵽��0��size��֮��
void SqLinearList::insertList(int index, ElemType &e)
{
	ASSERT_TRUE_VOID((index >= 0) && (index <= (_list->size))); //indexֻ�ܲ��뵽���е����Ա�0��size��֮��
	ASSERT_TRUE_VOID(_list->size <= MAX_SQ_LINEAR_LIST);

	// ���ƶ�֮ǰ��ԭʼ����a[0]~a[size-1]�в���a[index]
	for (int i = _list->size-1; i >= index; i--) // ���ƣ��Ӻ���ǰ���У�
	{
		_list->element[i + 1] = _list->element[i]; // a[size-1] ~ a[index]������Χ��������������ƶ�һλ
	}
	_list->element[index] = e; // ���e���뵽���a[index-1]֮��
	_list->size++; // ���Ա���+1
}


/*
�����Ա� L= (a[0]����a[i-1]��a[i]�� a[i+1]������a[size-1]) �еĵ�i(0�Qi�Qsize-1)��λ����ɾ�����e��ʹ���Ϊ���Ա�
L=(a[0]����a[i-1]��a[i+1]������a[size-1])
ʵ�ֲ���
(1) �����a[i]��ֵ���沢ɾ����
(2) �����Ա�L�еĵ�i+1������size-1�����ǰ��һ��λ�á�
(3) ���Ա��ȼ�1
*/
ElemType SqLinearList::deleteList(int index)
{
	ASSERT_TRUE_INT((index >= 0) && (index <= (_list->size-1)));
	if (isListEmpty())
	{
		std::cout << "sqence linear list is empty" << std::endl;
		return _list->element[0]; // �����Ĭ�Ϸ��ص�һ��Ԫ��element[0], Ĭ��ֵΪ0
	}

	ElemType e = _list->element[index]; // �����ɾ����Ԫ��a[index]
	for (int i = index+1; i <= _list->size-1; i++) // ��ǰ�������ΰ�a[index+1]~a[size-1]��ǰ�ƶ�һλ
	{
		_list->element[i-1] = _list->element[i];
	}
	_list->size--;   //���Ա��1

	return e; // ����ɾ����Ԫ��
}

bool SqLinearList::isListEmpty(void)
{
	return (0 == _list->size);
}

// ��ȡ����Ϊindex��Ԫ�أ���0��ʼ
ElemType& SqLinearList::getListByIndex(int index)
{
	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return _list->element[0]; // �����Ĭ�Ϸ��ص�һ��Ԫ��element[0], Ĭ��ֵΪ0
	}
	if (index > _list->size-1)
	{
		std::cout << "index is out of range[0," << _list->size << "] " << std::endl;
		return _list->element[0]; // Ĭ�Ϸ��ص�һ��Ԫ��element[0], Ĭ��ֵΪ0
	}

	return _list->element[index];
}

// ��ȡ��һ��Ԫ��ֵΪkey������index����0��ʼ
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
		return _list->element[0]; // δ�ҵ����Ĭ�Ϸ��ص�һ��Ԫ��element[0], Ĭ��ֵΪ0
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
