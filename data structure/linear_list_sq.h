#ifndef _LINEAR_LIST_SQ_H_
#define _LINEAR_LIST_SQ_H_

#include "DSComm.h"

/************************************************************************/
/* 
˳��洢 �������Ա�Ľ�㰴�߼�˳�����δ����һ���ַ�����Ĵ洢��Ԫ�
�����ַ����洢�����Ա���˳���
�ص㣺
�� ���Ա���߼�˳��������˳��һ��;
�� ����Ԫ��֮��Ĺ�ϵ����Ԫ���ڼ�����ڡ�����λ�����ڡ������֡�
������������ȡ�����ԣ���ˣ���������������˳���
*/
/************************************************************************/

#define MAX_SQ_LINEAR_LIST 100

typedef int ElemType;
typedef struct tag_Sq_LinearList
{
	ElemType element[MAX_SQ_LINEAR_LIST];
	int size;
}Sq_LinearList;


class SqLinearList
{
public:
	SqLinearList();
	~SqLinearList();
	void insertList(int index, ElemType &e);
	ElemType deleteList(int index);
	bool isListEmpty(void);
	ElemType& getListByIndex(int index);
	int locateList(ElemType &key);
	void traverseList(void);
	int getListSize(void);
private:
	void initList(void);
private:
	Sq_LinearList *_list;
};

#endif