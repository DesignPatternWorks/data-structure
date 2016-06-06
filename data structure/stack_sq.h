#ifndef _STACK_SQ_H_
#define _STACK_SQ_H_

/************************************************************************/
/* stack
栈(Stack)：是限制在表的一端进行插入和删除操作的线性表。又称为后进先出LIFO (Last In First Out)或
          先进后出FILO (First In Last Out)线性表。
栈顶(Top)：允许进行插入、删除操作的一端，又称为表尾。用栈顶指针(top)来指示栈顶元素。
栈底(Bottom)：是固定端，又称为表头。
空栈：当表中没有元素时称为空栈

栈的顺序存储结构简称为顺序栈，和线性表相类似，用一维数组来存储栈分为：
1.动态顺序栈
2.静态顺序栈
*/
/************************************************************************/

/*
动态顺序栈

采用动态一维数组来存储栈。所谓动态，指的是栈的大小可以根据需要增加
特点：
动态顺序栈可以根据需要增大栈的存储空间，但实现稍为复杂

用bottom表示栈底指针，栈底固定不变的；
用top表示栈顶指针，指示当前栈顶位置。栈顶则随着进栈和退栈操作而变化；
用top=bottom作为栈空的标记，每次top指向栈顶数组中的下一个存储位置

进出栈：
结点进栈：首先将数据元素保存到栈顶(top所指的当前位置)，然后执行top加1，使top指向栈顶的下一个存储位置
结点出栈：首先执行top减1，使top指向栈顶元素的存储位置，然后将栈顶元素取出
*/

#define  DYN_SQ_STACK_INIT_SIZE    100
#define  DYN_SQ_STACK_EXTEND_SIZE  50

typedef int ElemType;

typedef struct tag_Dyn_Sq_Stack
{
	ElemType *bottom;
	ElemType *top;
	int stackSize;  // 当前已分配栈大小
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
静态顺序栈

采用静态一维数组来存储栈。
特点：
静态顺序栈实现简单，但不能根据需要增大栈的存储空间

栈底固定不变的，而栈顶则随着进栈和退栈操作变化的，
栈底固定不变的；栈顶则随着进栈和退栈操作而变化，用一个整型变量top(称为栈顶指针)来指示当前栈顶位置。
用top=0表示栈空的初始状态，每次top指向栈顶在数组中的存储位置

进出栈：
结点进栈：首先执行top加1，使top指向新的栈顶位置，然后将数据元素保存到栈顶(top所指的当前位置)
结点出栈：首先把top指向的栈顶元素取出，然后执行top减1，使top指向新的栈顶位置。
若栈的数组有Maxsize个元素，则top=Maxsize-1时栈满
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