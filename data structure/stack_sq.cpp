#include "stdafx.h"
#include "stack_sq.h"
#include "DSComm.h"

/************************************************************************/
/* 动态顺序stack  
bottom一直为0，不会变化
top不断的变化
*/
/************************************************************************/
DynSqStack::DynSqStack()
{
	initStack();
}

void DynSqStack::initStack(void)
{
	_stack = (Dyn_Sq_Stack*)malloc(sizeof(Dyn_Sq_Stack));
	MALLOC_FAIL_NO_RETURN(_stack);

	_stack->bottom = (ElemType*)malloc(sizeof(ElemType) * DYN_SQ_STACK_INIT_SIZE);
	MALLOC_FAIL_NO_RETURN(_stack->bottom);

	_stack->top = _stack->bottom;
	_stack->stackSize = DYN_SQ_STACK_INIT_SIZE;

	_size = 0;
}

DynSqStack::~DynSqStack()
{
	SAFE_DEL_PTR(_stack->bottom);
	SAFE_DEL_PTR(_stack);
}
/*
结点进栈：首先将数据元素保存到栈顶(top所指的当前位置)，然后执行top加1，
使top指向栈顶的下一个存储位置
// 每次空间不够的时候扩展DYN_SQ_STACK_EXTEND_SIZE大小，动态变化
*/
void DynSqStack::pushStack(ElemType &e) // 包括bottom指针的值，且top指向栈顶是没有元素的（指向下一个待push的元素)
{
	if ((_stack->top - _stack->bottom) >= (_stack->stackSize -1))
	{
		ElemType *new_element = (ElemType*)realloc(_stack->bottom, sizeof(ElemType) * DYN_SQ_STACK_INIT_SIZE + DYN_SQ_STACK_EXTEND_SIZE);
		// new_element 可能与_stack地址不一致，导致分配时候，原来的_stack内存泄漏
		REALLOC_FAIL_NO_RETURN(new_element, _stack->bottom);
		_stack->bottom = new_element;

		_stack->top = _stack->bottom + DYN_SQ_STACK_INIT_SIZE-1; // 重新给top指针赋值
		_stack->stackSize  += DYN_SQ_STACK_EXTEND_SIZE;		// 重新更新stackSize
	}
	*(_stack->top) = e;   // 先赋值，再top指针++
	_stack->top++;
	_size++;
}

/*
结点出栈：首先执行top减1，使top指向栈顶元素的存储位置，然后将栈顶元素取出
*/
ElemType& DynSqStack::popStack(void)
{
	if (isStackEmpty())
	{
		std::cout << "empty stack" << std::endl;
		return  *(_stack->bottom);
	}

	_stack->top--;      // 先top指针--, 再返回值
	_size--;
	return *(_stack->top);
}

bool DynSqStack::isStackEmpty(void)
{
	return (_stack->bottom == _stack->top); // or _size == 0
}

// 获取从bottom开始（包括bottom）直到top(不包括top)之间的某个index的元素
ElemType& DynSqStack::getStackByIndex(int index)
{
	if (isStackEmpty())
	{
		std::cout << "empty stack" << std::endl;
		return  *(_stack->bottom);
	}
	if (index > _size - 1)
	{
		std::cout << "index is out of range[0," << _size - 1 << "] " << std::endl;
		return  *(_stack->bottom); // 默认返回bottom结点的值, 默认值为0
	}

	ElemType *loopElement = _stack->bottom;
	int loopIndex = 0;
	while (loopElement != _stack->top)
	{
		if (loopIndex == index)
		{
			return *loopElement;
		}
		loopIndex++;
		loopElement++;
	}
}

int DynSqStack::locateStack(ElemType &key)
{
	if (isStackEmpty())
	{
		std::cout << "empty stack" << std::endl;
		return  -1;
	}

	ElemType *loopElement = _stack->bottom;
	int loopIndex = 0;
	bool isFound = false;
	while (loopElement != _stack->top)
	{
		if (*loopElement == key)
		{
			isFound = true;
			return loopIndex;
		}
		loopIndex++;
		loopElement++;
	}

	if (!isFound)
	{
		std::cout << "not found key is " << key << std::endl;
		return *(_stack->bottom); // 未找到情况默认返回_stack结点bottom, 默认值为0
	}
}

int DynSqStack::getStackSize(void)
{
	return _size;
}

void DynSqStack::traverseStack(void)
{
	if (isStackEmpty())
	{
		std::cout << "empty stack" << std::endl;
		return;
	}

	std::cout << "_________begin traverse____________" << std::endl;

	ElemType *loopElement = _stack->bottom;
	int loopIndex = 0;//loopIndex从0开始
	while (loopElement != _stack->top)
	{
		std::cout << "stack[" << loopIndex << "]: " << *loopElement << "  ";
		loopElement++;
		loopIndex++;
	}
	std::cout << std::endl;
	std::cout << "_________end traverse____________" << std::endl;
}



/************************************************************************/
/* 静态顺序stack  
 bottom一直为0，不会变化
 top不断的变化
*/
/************************************************************************/
StaticSqStack::StaticSqStack()
{
	initStack();
}

void StaticSqStack::initStack(void)
{
	_stack = (Static_Sq_Stack *)malloc(sizeof(Static_Sq_Stack));
	MALLOC_FAIL_NO_RETURN(_stack);
	_stack->top = 0;
	_stack->bottom = 0;
	_stack->size = 0;
	memset(_stack->element, 0, sizeof(ElemType)*MAX_STATIC_SQ_STACK);
}

StaticSqStack::~StaticSqStack()
{
	SAFE_DEL_PTR(_stack);
}

//实际从element[1]开始存放元素 不包括bottom的值,且top指向栈顶是有元素的
void StaticSqStack::pushStack(ElemType &e)
{
	if (_stack->size >= MAX_STATIC_SQ_STACK-1)
	{
		std::cout << "stack is full" << std::endl;
		return;
	}
	_stack->top++;
	_stack->element[_stack->top] = e; // 先top++,再赋值给top(element[0]为stack bottom为空)
	_stack->size++;
}

ElemType& StaticSqStack::popStack()
{
	if (isStackEmpty())
	{
		std::cout << "empty stack" << std::endl;
		return _stack->element[_stack->bottom]; // 空默认返回init操作的bottom指针的元素值（初始化为0)
	}
	ElemType *e = &(_stack->element[_stack->top]); //先返回top 再top--
	_stack->top--;
	_stack->size--;
	return *e;
}

bool StaticSqStack::isStackEmpty()
{
	return (_stack->top == _stack->bottom); // or _stack->size == 0
}

// 获取从bottom开始（不包括bottom）直到top(包括top)之间的某个index的元素
ElemType& StaticSqStack::getStackByIndex(int index)
{
	if (isStackEmpty())
	{
		std::cout << "empty stack" << std::endl;
		return  _stack->element[0];
	}
	if (index > _stack->size - 1)
	{
		std::cout << "index is out of range[0," << _stack->size - 1 << "] " << std::endl;
		return  _stack->element[0]; // 默认返回element[0]的值, 默认值为0
	}

	return _stack->element[index+1]; // element[0]为bottom位置，不存放元素

}

// 返回索引，实际从element[1]开始存放元素，索引号从0开始
int StaticSqStack::locateStack(ElemType &key)
{
	if (isStackEmpty())
	{
		std::cout << "empty stack" << std::endl;
		return  -1;
	}

	for (int i = _stack->bottom + 1; i < _stack->top + 1; i++) // bottom一直为0，不会变化
	{
		if (_stack->element[i] == key)
		{
			return i-1; // 由于索引与存放存在一个位置的差距故需要-1(element[1]开始存放元素)
		}
	}
}

int StaticSqStack::getStackSize(void)
{
	return _stack->size;
}

void StaticSqStack::traverseStack(void)
{
	if (isStackEmpty())
	{
		std::cout << "empty stack" << std::endl;
		return;
	}

	std::cout << "_________begin traverse____________" << std::endl;

	for (int i = _stack->bottom + 1; i < _stack->top + 1; i++) // bottom一直为0，不会变化
	{
		std::cout << "stack[" << i-1 << "]: " << _stack->element[i] << "  "; 
	}
	std::cout << std::endl;
	std::cout << "_________end traverse____________" << std::endl;
}