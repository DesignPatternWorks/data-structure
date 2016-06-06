
/*******************ͷ�ļ�����****************/
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
	_list = (LNode*)malloc(sizeof(LNode)); // ����ͷ���
	MALLOC_FAIL_NO_RETURN(_list);

	_list->data = 0;
	_list->pNext = NULL;

	_size = 0;
}

LkLinearList::~LkLinearList()
{
	LNode *insertNode = _list->pNext; 

	while (!NULL_PTR(insertNode)) // ��ͷ���뷨���ƣ�ÿ��ɾ��head����ֱ�Ӻ���
	{
		_list->pNext = insertNode->pNext; // �޸�head����ֱ�Ӻ���Ϊ��ɾ������ֱ�Ӻ���
		free(insertNode);              // �ͷ�ɾ�����
		insertNode = _list->pNext; // �����ж���һ����ɾ�����
	}

	free(_list); // �ͷ�ͷ���
}


void LkLinearList::insertList(ElemType &e)
{
	LNode *newNode = (LNode*)malloc(sizeof(LNode));
	MALLOC_FAIL_NO_RETURN(newNode);

// ͷ���뷨��ÿ�ΰ���Ԫ�ز��뵽��һ��λ��(����Ϊ�����ͷ����ֱ�Ӻ���)����ʱԪ����������˳��Ͳ���˳�����෴��
	newNode->data = e;
	newNode->pNext = _list->pNext; // ���������ҵ���
	_list->pNext = newNode;  //��Ԫ�ز��뵽��һ��λ��(����Ϊ�����ͷ����ֱ�Ӻ���)
	_size++;

// β���뷨��ÿ�ΰ���Ԫ�ز��뵽β���ĺ���(����Ϊ�����β����ֱ�Ӻ���)����ʱԪ����������˳��Ͳ���˳����һ�µ�
	//newNode->data = e;
	//newNode->pNext = NULL;
	//LNode *loopNode = _list;
	//while (!NULL_PTR(loopNode->pNext))
	//{
	//	loopNode = loopNode->pNext;
	//}  // �����������ҵ�β���(��pNext == NULL)
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
		return _list->data; // ��Ĭ�Ϸ���ͷ����Ĭ��ֵ0
	}

	while (!NULL_PTR(loopNode->pNext))
	{
		if (loopNode->pNext->data == key)
		{
			//find data��ΪkeyԪ��ɾ��֮
			isFound = true;
			LNode* delNode = loopNode->pNext; // �ȱ���ɾ������ָ�룬�������ͷ��ڴ�
			e = delNode->data; // ����ɾ�����loopNode->pnext��dataֵ
			loopNode->pNext = delNode->pNext; // ֱ���޸�delNode��loopNode->pnext����ֱ��ǰ��loopNode����ֱ�Ӻ���
			free(delNode);
			_size--;
			return e;
		}
		loopNode = loopNode->pNext;
	}
	if (!isFound)
	{
		std::cout << "not found key: " << key << std::endl;
		return _list->data; // δ�ҵ�Ĭ�Ϸ���ͷ����Ĭ��ֵ0
	}
}

bool LkLinearList::isListEmpty(void)
{
	return (NULL == _list->pNext); // or _size == 0
}

// ��ȡ����Ϊindex��Ԫ�أ���0��ʼ���Ҳ�����head��㣬����head��ֱ�Ӻ�����㿪ʼ����
ElemType& LkLinearList::getListByIndex(int index)
{
	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return _list->data; // �����Ĭ�Ϸ��ص�һ������data, Ĭ��ֵΪ0
	}

	if (index > _size-1)
	{
		std::cout << "index is out of range[0," << _size-1 << "] " << std::endl;
		return _list->data; // Ĭ�Ϸ��ص�һ������data, Ĭ��ֵΪ0
	}

	int loopIndex = 0;  //loopIndex��0��ʼ
	LNode *loopNode = _list;
	while (!NULL_PTR(loopNode->pNext))
	{
		if (loopIndex == index)
		{
			return loopNode->pNext->data; //loopNode->pNextΪ��ǰ��㣬���ظý���ֵ
		}
		loopNode = loopNode->pNext; // ѭ����һ�����
		loopIndex++; // ��¼��Ч���(��head�������)��Ŀ+1
	}
}

// ��ȡ��һ��Ԫ��ֵΪkey������index����0��ʼ
int LkLinearList::locateList(ElemType &key)
{
	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return -1; // -1
	}

	bool isFound = false;
	int loopIndex = 0; //loopIndex��0��ʼ
	LNode *loopNode = _list;
	while (!NULL_PTR(loopNode->pNext))
	{
		if (loopNode->pNext->data == key) //loopNode->pNextΪ��ǰ��㣬���ظý�������
		{
			isFound = true;
			return loopIndex; 
		}
		loopNode = loopNode->pNext; // ѭ����һ�����
		loopIndex++; // ��¼��Ч���(��head�������)��Ŀ+1
	}

	if (!isFound)
	{
		std::cout << "not found key is " << key << std::endl;
		return _list->data; // δ�ҵ����Ĭ�Ϸ��ص�һ�����data, Ĭ��ֵΪ0
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
	int loopIndex = 0; //loopIndex��0��ʼ
	LNode *loopNode = _list;
	while (!NULL_PTR(loopNode->pNext))
	{
		std::cout << "listNode[" << loopIndex <<"]: " << loopNode->pNext->data << "  "; //loopNode->pNextΪ��ǰ��㣬���ظý�������
		loopNode = loopNode->pNext; // ѭ����һ�����
		loopIndex++; // ��¼��Ч���(��head�������)��Ŀ+1
	}
	std::cout << std::endl;
	std::cout << "_________end traverse____________" << std::endl;
}
