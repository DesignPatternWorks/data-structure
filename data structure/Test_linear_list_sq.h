#ifndef _TESTLINEARLIST_SQ_H_
#define _TESTLINEARLIST_SQ_H_

/*******************头文件包含****************/
#include "DSComm.h"

/*******************宏定义****************/
#define SQLIST_LEN (size_t)5 
#define ELEMENT_NUMBER(atElement) (sizeof(atElement)/sizeof(ElemType))

/*******************数据类型定义****************/


/********************变量声明****************/


/********************外部函数声明****************/
void testLinearListSq(void);





void TestPurge(WORD16 wFuncId);
void TestUnion(WORD16 wFuncId);
void TestIsSqListEqual(void);
void TestCompareList(void);
void TestExchangeList(WORD16 wFuncId);
#endif
