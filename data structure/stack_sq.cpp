#include "stdafx.h"
#include "stack_sq.h"
#include "DSComm.h"

/************************************************************************/
/* ��̬˳��stack  
bottomһֱΪ0������仯
top���ϵı仯
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
����ջ�����Ƚ�����Ԫ�ر��浽ջ��(top��ָ�ĵ�ǰλ��)��Ȼ��ִ��top��1��
ʹtopָ��ջ������һ���洢λ��
// ÿ�οռ䲻����ʱ����չDYN_SQ_STACK_EXTEND_SIZE��С����̬�仯
*/
void DynSqStack::pushStack(ElemType &e) // ����bottomָ���ֵ����topָ��ջ����û��Ԫ�صģ�ָ����һ����push��Ԫ��)
{
	if ((_stack->top - _stack->bottom) >= (_stack->stackSize -1))
	{
		ElemType *new_element = (ElemType*)realloc(_stack->bottom, sizeof(ElemType) * DYN_SQ_STACK_INIT_SIZE + DYN_SQ_STACK_EXTEND_SIZE);
		// new_element ������_stack��ַ��һ�£����·���ʱ��ԭ����_stack�ڴ�й©
		REALLOC_FAIL_NO_RETURN(new_element, _stack->bottom);
		_stack->bottom = new_element;

		_stack->top = _stack->bottom + DYN_SQ_STACK_INIT_SIZE-1; // ���¸�topָ�븳ֵ
		_stack->stackSize  += DYN_SQ_STACK_EXTEND_SIZE;		// ���¸���stackSize
	}
	*(_stack->top) = e;   // �ȸ�ֵ����topָ��++
	_stack->top++;
	_size++;
}

/*
����ջ������ִ��top��1��ʹtopָ��ջ��Ԫ�صĴ洢λ�ã�Ȼ��ջ��Ԫ��ȡ��
*/
ElemType& DynSqStack::popStack(void)
{
	if (isStackEmpty())
	{
		std::cout << "empty stack" << std::endl;
		return  *(_stack->bottom);
	}

	_stack->top--;      // ��topָ��--, �ٷ���ֵ
	_size--;
	return *(_stack->top);
}

bool DynSqStack::isStackEmpty(void)
{
	return (_stack->bottom == _stack->top); // or _size == 0
}

// ��ȡ��bottom��ʼ������bottom��ֱ��top(������top)֮���ĳ��index��Ԫ��
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
		return  *(_stack->bottom); // Ĭ�Ϸ���bottom����ֵ, Ĭ��ֵΪ0
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
		return *(_stack->bottom); // δ�ҵ����Ĭ�Ϸ���_stack���bottom, Ĭ��ֵΪ0
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
	int loopIndex = 0;//loopIndex��0��ʼ
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
/* ��̬˳��stack  
 bottomһֱΪ0������仯
 top���ϵı仯
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

//ʵ�ʴ�element[1]��ʼ���Ԫ�� ������bottom��ֵ,��topָ��ջ������Ԫ�ص�
void StaticSqStack::pushStack(ElemType &e)
{
	if (_stack->size >= MAX_STATIC_SQ_STACK-1)
	{
		std::cout << "stack is full" << std::endl;
		return;
	}
	_stack->top++;
	_stack->element[_stack->top] = e; // ��top++,�ٸ�ֵ��top(element[0]Ϊstack bottomΪ��)
	_stack->size++;
}

ElemType& StaticSqStack::popStack()
{
	if (isStackEmpty())
	{
		std::cout << "empty stack" << std::endl;
		return _stack->element[_stack->bottom]; // ��Ĭ�Ϸ���init������bottomָ���Ԫ��ֵ����ʼ��Ϊ0)
	}
	ElemType *e = &(_stack->element[_stack->top]); //�ȷ���top ��top--
	_stack->top--;
	_stack->size--;
	return *e;
}

bool StaticSqStack::isStackEmpty()
{
	return (_stack->top == _stack->bottom); // or _stack->size == 0
}

// ��ȡ��bottom��ʼ��������bottom��ֱ��top(����top)֮���ĳ��index��Ԫ��
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
		return  _stack->element[0]; // Ĭ�Ϸ���element[0]��ֵ, Ĭ��ֵΪ0
	}

	return _stack->element[index+1]; // element[0]Ϊbottomλ�ã������Ԫ��

}

// ����������ʵ�ʴ�element[1]��ʼ���Ԫ�أ������Ŵ�0��ʼ
int StaticSqStack::locateStack(ElemType &key)
{
	if (isStackEmpty())
	{
		std::cout << "empty stack" << std::endl;
		return  -1;
	}

	for (int i = _stack->bottom + 1; i < _stack->top + 1; i++) // bottomһֱΪ0������仯
	{
		if (_stack->element[i] == key)
		{
			return i-1; // �����������Ŵ���һ��λ�õĲ�����Ҫ-1(element[1]��ʼ���Ԫ��)
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

	for (int i = _stack->bottom + 1; i < _stack->top + 1; i++) // bottomһֱΪ0������仯
	{
		std::cout << "stack[" << i-1 << "]: " << _stack->element[i] << "  "; 
	}
	std::cout << std::endl;
	std::cout << "_________end traverse____________" << std::endl;
}