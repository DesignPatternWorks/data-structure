#ifndef _LINEAR_LIST_SQ_H_
#define _LINEAR_LIST_SQ_H_

#include "DSComm.h"

/************************************************************************/
/* 
顺序存储 ：把线性表的结点按逻辑顺序依次存放在一组地址连续的存储单元里。
用这种方法存储的线性表简称顺序表
特点：
◆ 线性表的逻辑顺序与物理顺序一致;
◆ 数据元素之间的关系是以元素在计算机内“物理位置相邻”来体现。
数组具有随机存取的特性，因此，借助数组来描述顺序表
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