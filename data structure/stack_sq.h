#ifndef _STACK_SQ_H_
#define _STACK_SQ_H_

/************************************************************************/
/* stack
ջ(Stack)���������ڱ��һ�˽��в����ɾ�����������Ա��ֳ�Ϊ����ȳ�LIFO (Last In First Out)��
          �Ƚ����FILO (First In Last Out)���Ա�
ջ��(Top)��������в��롢ɾ��������һ�ˣ��ֳ�Ϊ��β����ջ��ָ��(top)��ָʾջ��Ԫ�ء�
ջ��(Bottom)���ǹ̶��ˣ��ֳ�Ϊ��ͷ��
��ջ��������û��Ԫ��ʱ��Ϊ��ջ

ջ��˳��洢�ṹ���Ϊ˳��ջ�������Ա������ƣ���һά�������洢ջ��Ϊ��
1.��̬˳��ջ
2.��̬˳��ջ
*/
/************************************************************************/

/*
��̬˳��ջ

���ö�̬һά�������洢ջ����ν��̬��ָ����ջ�Ĵ�С���Ը�����Ҫ����
�ص㣺
��̬˳��ջ���Ը�����Ҫ����ջ�Ĵ洢�ռ䣬��ʵ����Ϊ����

��bottom��ʾջ��ָ�룬ջ�׹̶�����ģ�
��top��ʾջ��ָ�룬ָʾ��ǰջ��λ�á�ջ�������Ž�ջ����ջ�������仯��
��top=bottom��Ϊջ�յı�ǣ�ÿ��topָ��ջ�������е���һ���洢λ��

����ջ��
����ջ�����Ƚ�����Ԫ�ر��浽ջ��(top��ָ�ĵ�ǰλ��)��Ȼ��ִ��top��1��ʹtopָ��ջ������һ���洢λ��
����ջ������ִ��top��1��ʹtopָ��ջ��Ԫ�صĴ洢λ�ã�Ȼ��ջ��Ԫ��ȡ��
*/

#define  DYN_SQ_STACK_INIT_SIZE    100
#define  DYN_SQ_STACK_EXTEND_SIZE  50

typedef int ElemType;

typedef struct tag_Dyn_Sq_Stack
{
	ElemType *bottom;
	ElemType *top;
	int stackSize;  // ��ǰ�ѷ���ջ��С
}Dyn_Sq_Stack;

class DynSqStack
{
public:
	DynSqStack();
	~DynSqStack();
	void pushStack(ElemType &e);
	ElemType& popStack(void);
	bool isStackEmpty(void);
	ElemType& getStackByIndex(int index);
	int locateStack(ElemType &key);
	void traverseStack(void);
	int getStackSize(void);
private:
	void initStack(void);
private:
	Dyn_Sq_Stack *_stack;
	int _size;
};




/*
��̬˳��ջ

���þ�̬һά�������洢ջ��
�ص㣺
��̬˳��ջʵ�ּ򵥣������ܸ�����Ҫ����ջ�Ĵ洢�ռ�

ջ�׹̶�����ģ���ջ�������Ž�ջ����ջ�����仯�ģ�
ջ�׹̶�����ģ�ջ�������Ž�ջ����ջ�������仯����һ�����ͱ���top(��Ϊջ��ָ��)��ָʾ��ǰջ��λ�á�
��top=0��ʾջ�յĳ�ʼ״̬��ÿ��topָ��ջ���������еĴ洢λ��

����ջ��
����ջ������ִ��top��1��ʹtopָ���µ�ջ��λ�ã�Ȼ������Ԫ�ر��浽ջ��(top��ָ�ĵ�ǰλ��)
����ջ�����Ȱ�topָ���ջ��Ԫ��ȡ����Ȼ��ִ��top��1��ʹtopָ���µ�ջ��λ�á�
��ջ��������Maxsize��Ԫ�أ���top=Maxsize-1ʱջ��
*/

#define MAX_STATIC_SQ_STACK 100

typedef struct tag_Stack_Sq_Stack
{
	int top;
	int bottom;
	int size;
	ElemType element[MAX_STATIC_SQ_STACK];
}Static_Sq_Stack;

class StaticSqStack
{
public:
	StaticSqStack();
	~StaticSqStack();
	void pushStack(ElemType &e);
	ElemType& popStack(void);
	bool isStackEmpty(void);
	ElemType& getStackByIndex(int index);
	int locateStack(ElemType &key);
	void traverseStack(void);
	int getStackSize(void);
private:
	void initStack(void);
private:
	Static_Sq_Stack *_stack;
};

#endif