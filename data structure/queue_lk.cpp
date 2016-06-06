#include "stdafx.h"
#include "queue_lk.h"
#include "DSComm.h"

LkQueue::LkQueue()
{
	initQueue();
}

void LkQueue::initQueue(void)
{
	QNode *head = (QNode*)malloc(sizeof(QNode)); // ����������е�ͷ��㲢��ʼ��
	MALLOC_FAIL_NO_RETURN(head);
	head->element = 0;
	head->next = NULL;

	_queue = (Lk_Queue *)malloc(sizeof(Lk_Queue)); // ����������в���ʼ����front��rearָ��Ϊhead
	MALLOC_FAIL_NO_RETURN(_queue);

	_queue->front = head;
	_queue->rear = head; 

	_size = 0;
}

LkQueue::~LkQueue()
{
	QNode *head = _queue->front;
	QNode *pushedNode = head->next;

	while (!NULL_PTR(pushedNode)) // �ͷ�����push��������ĳ���head����������Ԫ�ؽ���ڴ�
	{
		head->next = pushedNode->next; // �ͷ�pushedNode��㣬������pop����
		free(pushedNode);
		pushedNode = head->next;  // �ѵ�ǰpushedNode����ֱ�Ӻ�����Ϊ��һ�ε�pushedNode���
	}

	free(head); //�ͷ�init���������head����ڴ�
	free(_queue); // �ͷ�init����������������ڴ�
}

// ÿ����rearָ��ָ��Ľ����������½ڵ㣬Ȼ���޸�rearָ��ָ���µĽ��
void LkQueue::pushQueue(ElemType &e)
{
	QNode *newNode = (QNode*)malloc(sizeof(QNode));
	MALLOC_FAIL_NO_RETURN(newNode);
	
	newNode->element = e;
	newNode->next = NULL;

	_queue->rear->next = newNode; // rearָ��ָ��Ľ����������½ڵ㣬���½ڵ�Ϊ��ǰrearָ��Ľ���ֱ�Ӻ���
	_queue->rear = newNode; // �޸�rearָ��ָ��Ϊ���һ�������ӵĽ�㣬��֤ÿ��push����֮��rearָ�����һ��node
	_size++;
}

// ÿ��pop����pop frontָ��ָ��Ľ�����һ������Ԫ�أ�Ҳ��headָ���ֱ�Ӻ�������Ϊ��ʼ��frontָ��ָ��head,��һ��û�仯��
ElemType LkQueue::popQueue(void) //pop�Ľ�㱻�ͷ��ˣ�����ʹ������
{
	if (isQueueEmpty())
	{
		std::cout << "queue is empty" << std::endl;
		return _queue->front->element; // Ĭ�Ͽշ���init������head���Ԫ��ֵ����ʼ��Ϊ0)
	}

	QNode *head = _queue->front; // ͷ���
	QNode *popNode = head->next; // popNode = _queque->front->next;
	ElemType e = popNode->element; //ÿ�ζ���head->nextָ��ָ��Ľ�㱻pop, pop����û�ı�frontָ��ָ��
	head->next = popNode->next; // ɾ��head->nextָ��Ľ��,��_queue->front->next = _queue->front->next->next;
	free(popNode);
	
	// pop���һ��Ԫ�ؽ��֮����Ҫ��rearָ������ָ��head,�����ʱ��������Ϊ�գ�����rearû��ָ���˳�ΪҰָ����
	if (NULL_PTR(head->next))
	{
		_queue->rear = head; // pop������Ԫ�ؽ��(��head��)����Ҫ������rearָ��Ϊhead,����rearΪҰָ��
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
		return _queue->front->element; // Ĭ�Ͽշ���init������head���Ԫ��ֵ����ʼ��Ϊ0)
	}

	if (index < 0 || index > _size-1)
	{
		std::cout << "index [" << index << "] is out of range: [0, "<< _size << ")" << std::endl;
		return _queue->front->element; // Ĭ�Ͽշ���init������head���Ԫ��ֵ����ʼ��Ϊ0)
	}

	int loopIndex = 0;
	QNode *loopNode = _queue->front->next;

	while (!NULL_PTR(loopNode)) // ��(front--> rear]��rearΪβ��� rear->next == NULL
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
		return _queue->front->element; // Ĭ�Ͽշ���init������head���Ԫ��ֵ����ʼ��Ϊ0)
	}

	int loopIndex = 0;
	QNode *loopNode = _queue->front->next;
	bool isFound = false;

	while (!NULL_PTR(loopNode)) // ��(front--> rear]��rearΪβ��� rear->next == NULL
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
		return _queue->front->element; // ��Ĭ�Ϸ���init������front��Ԫ��ֵ(ֵΪ0����ʼ��Ϊ0)
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

	while (!NULL_PTR(loopNode)) // ��(front--> rear]��rearΪβ��� rear->next == NULL
	{
		std::cout << "queue[" << loopIndex << "]: " << loopNode->element << "  ";
		loopNode = loopNode->next;
		loopIndex++;
	}

	std::cout << std::endl;
	std::cout << "_________end traverse____________" << std::endl;
}