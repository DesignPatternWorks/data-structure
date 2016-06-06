#ifndef _STACK_LK_H_
#define _STACK_LK_H_

/************************************************************************/
/* stack
栈(Stack)：是限制在表的一端进行插入和删除操作的线性表。又称为后进先出LIFO (Last In First Out)或
先进后出FILO (First In Last Out)线性表。
栈顶(Top)：允许进行插入、删除操作的一端，又称为表尾。用栈顶指针(top)来指示栈顶元素。
栈底(Bottom)：是固定端，又称为表头。
空栈：当表中没有元素时称为空栈
*/
/************************************************************************/

/*
栈的链式存储结构称为链栈，是运算受限的单链表。其插入和删除操作只能在表头位置上进行。
因此，链栈没有必要像单链表那样附加头结点，栈顶指针top就是链表的头指针
*/

typedef int ElemType;

typedef struct tag_Lk_StackNode
{
	ElemType element;
	tag_Lk_StackNode *next;
}Lk_Stack_Node;

class LkStack
{
public:
	LkStack();
	~LkStack();
	void pushStack(ElemType &e);
	ElemType popStack(void); // 此处不好处理为引用，否则要动态申请和释放内存
	bool isStackEmpty(void);
	ElemType& getStackByIndex(int index);
	int locateStack(ElemType &key);
	void traverseStack(void);
	int getStackSize(void);
private:
	void initStack(void);
private:
	Lk_Stack_Node *_stack;
	int _size;
};

#endif
