#ifndef _LINEAR_LIST_LK_H_
#define _LINEAR_LIST_LK_H_

/*******************ͷ�ļ�����****************/
#include "DSComm.h"
/*******************�궨��****************/
/*******************�������Ͷ���****************/


/*
��ʽ�洢 ����һ������Ĵ洢��Ԫ�洢���Ա��е�����Ԫ�ء������ַ����洢�����Ա�����������
�洢�����н���һ������Ĵ洢��Ԫ�����������ģ�Ҳ�����ǲ������ģ���������ɢ�ֲ����ڴ��е�����λ���ϵġ�
�����н����߼�˳�������˳��һ����ͬ��

Ϊ�������㣬����������ĵ�һ�����֮ǰ����һ��ͷ���(ͷָ��)headָ���һ����㡣
ͷ������������Բ��洢�κ���Ϣ(�������ȵ���Ϣ)��
*/

typedef unsigned long ElemType;
//������
typedef struct LNode
{
	ElemType   data;
	LNode      *pNext;  // ֻ��һ�������ָ����
}LNode, *LList;            // tag ������������һ��LNode

class LkLinearList
{
public:
	LkLinearList();
	~LkLinearList();
	void insertList(ElemType &e);
	ElemType deleteList(ElemType &key);
	bool isListEmpty(void);
	ElemType& getListByIndex(int index);
	int locateList(ElemType &key);
	void traverseList(void);
	int getListSize(void);
private:
	void initList(void);
private:
	LNode *_list;
	int _size;
};


//˫����
typedef struct DbLNode
{
	ElemType data;
	DbLNode  *pPrior;
	DbLNode  *pNext;
}DbLNode;
//PS:˫�����LastNode��pNextָ��NULL������NULL������pPriorָ��LastNode

//PS:����ѭ������,ͨ���ڱ��еĵ�һ�����֮ǰ����һ����ͷ��㡱�����ͷָ�롱ָ�����һ�����

//PS:��ѭ�������ѭ������ʹ��ʱ��Ψһ����
//���ڷ�ѭ������ͨ���жϸ�ָ���Ƿ���NULL���ж��Ƿ��Ǳ�β�� ����ѭ������ͨ���ж��Ƿ���ͷָ�����ж��Ƿ��Ǳ�β
/********************��������****************/


/********************�ⲿ��������****************/
#endif