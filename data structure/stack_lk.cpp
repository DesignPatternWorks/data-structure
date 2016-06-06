#include "stdafx.h"
#include "stack_lk.h"
#include "DSComm.h"

LkStack::LkStack()
{
	initStack();
}

void LkStack::initStack()
{
	_stack = (Lk_Stack_Node*)malloc(sizeof(Lk_Stack_Node)); // 开辟 _stack结点
	MALLOC_FAIL_NO_RETURN(_stack);

	_stack->element = 0;
	_stack->next = NULL; // 初始化为NULL
	_size = 0;
}

LkStack::~LkStack()
{
	Lk_Stack_Node *pushedNode = _stack->next;

	while (!NULL_PTR(pushedNode)) // 释放push操作申请的node内存
	{
		_stack->next = pushedNode->next;
		SAFE_DEL_PTR(pushedNode);
		pushedNode = _stack->next;
	}

	SAFE_DEL_PTR(_stack); // 释放init操作申请的_stack node内存
}


// 每次新push的结点放在_stack紧跟的后面(作为_stack的直接后驱),类似于单链表的头结点插入方法
void LkStack::pushStack(ElemType &e) 
{
	Lk_Stack_Node *newNode = (Lk_Stack_Node*)malloc(sizeof(Lk_Stack_Node));
	MALLOC_FAIL_NO_RETURN(newNode);

	newNode->element = e;
	newNode->next = _stack->next; // 新节点插入到原来栈链表的最前(不包括_stack,即放在_stack的后面)
	//新结点作为_stack的直接后驱
	_stack->next = newNode;   //  钩链  
	_size++;
}


ElemType LkStack::popStack(void) // 不好返回引用，因为pop的结点释放了
{
	if (isStackEmpty())
	{
		std::cout << "stack is empty" << std::endl;
		return -1; // 默认-1
	}

	Lk_Stack_Node *popNode = _stack->next;
	ElemType e = popNode->element;
	_stack->next = popNode->next; // pop结点的直接后驱作为_stack的直接后驱
	free(popNode); // 释放pop的结点
	_size--;

	return e; // 返回pop结点的元素值
}

bool LkStack::isStackEmpty(void)
{
	return (NULL_PTR(_stack->next)); // or _size == 0
}


ElemType& LkStack::getStackByIndex(int index)
{
	if (isStackEmpty())
	{
		std::cout << "empty stack" << std::endl;
		return  _stack->element; // 默认返回_stack结点的element值, 默认值为0
	}
	if (index > _size - 1)
	{
		std::cout << "index is out of range[0," << _size - 1 << "] " << std::endl;
		return  _stack->element; // 默认返回_stack结点的element值, 默认值为0
	}

	int loopIndex = 0;  //loopIndex从0开始
	Lk_Stack_Node *loopNode = _stack;
	while (!NULL_PTR(loopNode->next))
	{
		if (loopIndex == index)
		{
			return loopNode->next->element; //loopNode->next为当前结点，返回该结点的值
		}
		loopNode = loopNode->next; // 循环下一个结点
		loopIndex++; // 记录有效结点(除head结点以外)数目+1
	}
}

// 获取第一个元素值为key的索引index，从0开始
int LkStack::locateStack(ElemType &key)
{
	if (isStackEmpty())
	{
		std::cout << "stack is empty" << std::endl;
		return -1; // -1
	}

	bool isFound = false;
	int loopIndex = 0; //loopIndex从0开始
	Lk_Stack_Node *loopNode = _stack;
	while (!NULL_PTR(loopNode->next))
	{
		if (loopNode->next->element == key) //loopNode->next为当前结点，返回该结点的索引
		{
			isFound = true;
			return loopIndex;
		}
		loopNode = loopNode->next; // 循环下一个结点
		loopIndex++; // 记录有效结点(除head结点以外)数目+1
	}

	if (!isFound)
	{
		std::cout << "not found key is " << key << std::endl;
		return _stack->element; // 未找到情况默认返回_stack结点element, 默认值为0
	}
}

int LkStack::getStackSize(void)
{
	return _size;
}

void LkStack::traverseStack(void)
{
	if (isStackEmpty())
	{
		std::cout << "stack is empty" << std::endl;
		return;
	}

	std::cout << "_________begin traverse____________" << std::endl;
	int loopIndex = 0; //loopIndex从0开始
	Lk_Stack_Node *loopNode = _stack;
	while (!NULL_PTR(loopNode->next))
	{
		std::cout << "stackNode[" << loopIndex << "]: " << loopNode->next->element << "  "; //loopNode->next为当前结点，返回该结点的索引
		loopNode = loopNode->next; // 循环下一个结点
		loopIndex++; // 记录有效结点(除head结点以外)数目+1
	}
	std::cout << std::endl;
	std::cout << "_________end traverse____________" << std::endl;
}