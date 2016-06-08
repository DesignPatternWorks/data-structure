#ifndef _LINEAR_LIST_LK_H_
#define _LINEAR_LIST_LK_H_

/*******************头文件包含****************/
#include "DSComm.h"
/*******************宏定义****************/
/*******************数据类型定义****************/


/*
链式存储 ：用一组任意的存储单元存储线性表中的数据元素。用这种方法存储的线性表简称线性链表。
存储链表中结点的一组任意的存储单元可以是连续的，也可以是不连续的，甚至是零散分布在内存中的任意位置上的。
链表中结点的逻辑顺序和物理顺序不一定相同。

为操作方便，总是在链表的第一个结点之前附设一个头结点(头指针)head指向第一个结点。
头结点的数据域可以不存储任何信息(或链表长度等信息)。
*/

typedef unsigned long ElemType;
//单链表
typedef struct LNode
{
	ElemType   data;
	LNode      *pNext;  // 只有一个方向的指针域
}LNode, *LList;            // tag 和类型名保持一致LNode

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


//双链表
typedef struct DbLNode
{
	ElemType data;
	DbLNode  *pPrior;
	DbLNode  *pNext;
}DbLNode;
//PS:双链表的LastNode的pNext指向NULL，但是NULL不存在pPrior指向LastNode

//PS:对于循环链表,通常在表中的第一个结点之前附加一个“头结点”，并令“头指针”指向最后一个结点

//PS:非循环链表和循环链表使用时的唯一区别：
//对于非循环链表通过判断该指针是否是NULL来判断是否是表尾， 对于循环链表，通过判断是否是头指针来判断是否是表尾
/********************变量声明****************/


/********************外部函数声明****************/
#endif