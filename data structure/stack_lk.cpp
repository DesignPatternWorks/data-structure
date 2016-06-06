#include "stdafx.h"
#include "stack_lk.h"
#include "DSComm.h"

LkStack::LkStack()
{
	initStack();
}

void LkStack::initStack()
{
	_stack = (Lk_Stack_Node*)malloc(sizeof(Lk_Stack_Node)); // ���� _stack���
	MALLOC_FAIL_NO_RETURN(_stack);

	_stack->element = 0;
	_stack->next = NULL; // ��ʼ��ΪNULL
	_size = 0;
}

LkStack::~LkStack()
{
	Lk_Stack_Node *pushedNode = _stack->next;

	while (!NULL_PTR(pushedNode)) // �ͷ�push���������node�ڴ�
	{
		_stack->next = pushedNode->next;
		SAFE_DEL_PTR(pushedNode);
		pushedNode = _stack->next;
	}

	SAFE_DEL_PTR(_stack); // �ͷ�init���������_stack node�ڴ�
}


// ÿ����push�Ľ�����_stack�����ĺ���(��Ϊ_stack��ֱ�Ӻ���),�����ڵ������ͷ�����뷽��
void LkStack::pushStack(ElemType &e) 
{
	Lk_Stack_Node *newNode = (Lk_Stack_Node*)malloc(sizeof(Lk_Stack_Node));
	MALLOC_FAIL_NO_RETURN(newNode);

	newNode->element = e;
	newNode->next = _stack->next; // �½ڵ���뵽ԭ��ջ�������ǰ(������_stack,������_stack�ĺ���)
	//�½����Ϊ_stack��ֱ�Ӻ���
	_stack->next = newNode;   //  ����  
	_size++;
}


ElemType LkStack::popStack(void) // ���÷������ã���Ϊpop�Ľ���ͷ���
{
	if (isStackEmpty())
	{
		std::cout << "stack is empty" << std::endl;
		return -1; // Ĭ��-1
	}

	Lk_Stack_Node *popNode = _stack->next;
	ElemType e = popNode->element;
	_stack->next = popNode->next; // pop����ֱ�Ӻ�����Ϊ_stack��ֱ�Ӻ���
	free(popNode); // �ͷ�pop�Ľ��
	_size--;

	return e; // ����pop����Ԫ��ֵ
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
		return  _stack->element; // Ĭ�Ϸ���_stack����elementֵ, Ĭ��ֵΪ0
	}
	if (index > _size - 1)
	{
		std::cout << "index is out of range[0," << _size - 1 << "] " << std::endl;
		return  _stack->element; // Ĭ�Ϸ���_stack����elementֵ, Ĭ��ֵΪ0
	}

	int loopIndex = 0;  //loopIndex��0��ʼ
	Lk_Stack_Node *loopNode = _stack;
	while (!NULL_PTR(loopNode->next))
	{
		if (loopIndex == index)
		{
			return loopNode->next->element; //loopNode->nextΪ��ǰ��㣬���ظý���ֵ
		}
		loopNode = loopNode->next; // ѭ����һ�����
		loopIndex++; // ��¼��Ч���(��head�������)��Ŀ+1
	}
}

// ��ȡ��һ��Ԫ��ֵΪkey������index����0��ʼ
int LkStack::locateStack(ElemType &key)
{
	if (isStackEmpty())
	{
		std::cout << "stack is empty" << std::endl;
		return -1; // -1
	}

	bool isFound = false;
	int loopIndex = 0; //loopIndex��0��ʼ
	Lk_Stack_Node *loopNode = _stack;
	while (!NULL_PTR(loopNode->next))
	{
		if (loopNode->next->element == key) //loopNode->nextΪ��ǰ��㣬���ظý�������
		{
			isFound = true;
			return loopIndex;
		}
		loopNode = loopNode->next; // ѭ����һ�����
		loopIndex++; // ��¼��Ч���(��head�������)��Ŀ+1
	}

	if (!isFound)
	{
		std::cout << "not found key is " << key << std::endl;
		return _stack->element; // δ�ҵ����Ĭ�Ϸ���_stack���element, Ĭ��ֵΪ0
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
	int loopIndex = 0; //loopIndex��0��ʼ
	Lk_Stack_Node *loopNode = _stack;
	while (!NULL_PTR(loopNode->next))
	{
		std::cout << "stackNode[" << loopIndex << "]: " << loopNode->next->element << "  "; //loopNode->nextΪ��ǰ��㣬���ظý�������
		loopNode = loopNode->next; // ѭ����һ�����
		loopIndex++; // ��¼��Ч���(��head�������)��Ŀ+1
	}
	std::cout << std::endl;
	std::cout << "_________end traverse____________" << std::endl;
}