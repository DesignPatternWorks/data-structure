#ifndef _TESTLINEARLIST_SQ_H_
#define _TESTLINEARLIST_SQ_H_

/*******************ͷ�ļ�����****************/
#include "DSComm.h"

/*******************�궨��****************/
#define SQLIST_LEN (size_t)5 
#define ELEMENT_NUMBER(atElement) (sizeof(atElement)/sizeof(ElemType))

/*******************�������Ͷ���****************/


/********************��������****************/


/********************�ⲿ��������****************/
void testLinearListSq(void);





void TestPurge(WORD16 wFuncId);
void TestUnion(WORD16 wFuncId);
void TestIsSqListEqual(void);
void TestCompareList(void);
void TestExchangeList(WORD16 wFuncId);
#endif
