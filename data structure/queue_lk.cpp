#include "stdafx.h"
#include "queue_lk.h"
#include "DSComm.h"

LkQueue::LkQueue()
{
	initQueue();
}

void LkQueue::initQueue(void)
{
	QNode *head = (QNode*)malloc(sizeof(QNode)); // 开辟链表队列的头结点并初始化
	MALLOC_FAIL_NO_RETURN(head);
	head->element = 0;
	head->next = NULL;

	_queue = (Lk_Queue *)malloc(sizeof(Lk_Queue)); // 开辟链表队列并初始化其front和rear指针为head
	MALLOC_FAIL_NO_RETURN(_queue);

	_queue->front = head;
	_queue->rear = head; 

	_size = 0;
}

LkQueue::~LkQueue()
{
	QNode *head = _queue->front;
	QNode *pushedNode = head->next;

	while (!NULL_PTR(pushedNode)) // 释放由于push操作申请的除开head结点外的所有元素结点内存
	{
		head->next = pushedNode->next; // 释放pushedNode结点，类似于pop操作
		free(pushedNode);
		pushedNode = head->next;  // 把当前pushedNode结点的直接后驱作为下一次的pushedNode结点
	}

	free(head); //释放init操作申请的head结点内存
	free(_queue); // 释放init操作申请的链队列内存
}

// 每次在rear指针指向的结点后面增加新节点，然后修改rear指针指向新的结点
void LkQueue::pushQueue(ElemType &e)
{
	QNode *newNode = (QNode*)malloc(sizeof(QNode));
	MALLOC_FAIL_NO_RETURN(newNode);
	
	newNode->element = e;
	newNode->next = NULL;

	_queue->rear->next = newNode; // rear指针指向的结点后面增加新节点，即新节点为当前rear指向的结点的直接后驱
	_queue->rear = newNode; // 修改rear指针指向为最后一个新增加的结点，保证每次push操作之后rear指向最后一个node
	_size++;
}

// 每次pop都是pop front指针指向的结点的下一个结点的元素（也是head指针的直接后驱，因为初始化front指针指向head,且一致没变化）
ElemType LkQueue::popQueue(void) //pop的结点被释放了，不好使用引用
{
	if (isQueueEmpty())
	{
		std::cout << "queue is empty" << std::endl;
		return _queue->front->element; // 默认空返回init操作的head结点元素值（初始化为0)
	}

	QNode *head = _queue->front; // 头结点
	QNode *popNode = head->next; // popNode = _queque->front->next;
	ElemType e = popNode->element; //每次都是head->next指针指向的结点被pop, pop操作没改变front指针指向
	head->next = popNode->next; // 删除head->next指向的结点,亦_queue->front->next = _queue->front->next->next;
	free(popNode);
	
	// pop最后一个元素结点之后，需要将rear指针重新指向head,否则此时队列链表为空，但是rear没有指向了成为野指针了
	if (NULL_PTR(head->next))
	{
		_queue->rear = head; // pop完所有元素结点(除head外)后需要重新置rear指针为head,否则rear为野指针
	}
	_size--;

	return e;
}

bool LkQueue::isQueueEmpty(void)
{
	return (_queue->rear == _queue->front);  // or _size == 0
}

ElemType& LkQueue::getQueueByIndex(int index)
{
	if (isQueueEmpty())
	{
		std::cout << "queue is empty" << std::endl;
		return _queue->front->element; // 默认空返回init操作的head结点元素值（初始化为0)
	}

	if (index < 0 || index > _size-1)
	{
		std::cout << "index [" << index << "] is out of range: [0, "<< _size << ")" << std::endl;
		return _queue->front->element; // 默认空返回init操作的head结点元素值（初始化为0)
	}

	int loopIndex = 0;
	QNode *loopNode = _queue->front->next;

	while (!NULL_PTR(loopNode)) // 从(front--> rear]，rear为尾结点 rear->next == NULL
	{
		if (loopIndex == index)
		{
			return loopNode->element;
		}
		loopNode = loopNode->next;
		loopIndex++;
	}
}

int LkQueue::locateQueue(ElemType &key)
{
	if (isQueueEmpty())
	{
		std::cout << "queue is empty" << std::endl;
		return _queue->front->element; // 默认空返回init操作的head结点元素值（初始化为0)
	}

	int loopIndex = 0;
	QNode *loopNode = _queue->front->next;
	bool isFound = false;

	while (!NULL_PTR(loopNode)) // 从(front--> rear]，rear为尾结点 rear->next == NULL
	{
		if (loopNode->element == key)
		{
			isFound = true;
			return loopIndex;
		}
		loopNode = loopNode->next;
		loopIndex++;
	}

	if (!isFound)
	{
		std::cout << "not found key is " << key << std::endl;
		return _queue->front->element; // 空默认返回init操作的front的元素值(值为0，初始化为0)
	}
}

int LkQueue::getQueueSize(void)
{
	return _size;
}

void LkQueue::traverseQueue(void)
{
	if (isQueueEmpty())
	{
		std::cout << "queue is empty" << std::endl;
		return;
	}

	std::cout << "_________begin traverse____________" << std::endl;

	int loopIndex = 0;
	QNode *loopNode = _queue->front->next;

	while (!NULL_PTR(loopNode)) // 从(front--> rear]，rear为尾结点 rear->next == NULL
	{
		std::cout << "queue[" << loopIndex << "]: " << loopNode->element << "  ";
		loopNode = loopNode->next;
		loopIndex++;
	}

	std::cout << std::endl;
	std::cout << "_________end traverse____________" << std::endl;
}