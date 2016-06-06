#include "stdafx.h"
#include "queue_sq.h"
#include "DSComm.h"

SqCircleQueue::SqCircleQueue()
{
	initQueue();
}

void SqCircleQueue::initQueue(void)
{
	_queue = (Sq_Circle_Queue *)malloc(sizeof(Sq_Circle_Queue));
	MALLOC_FAIL_NO_RETURN(_queue);

	_queue->front = 0;
	_queue->rear = 0;
	memset(_queue->element, 0, sizeof(ElemType)*MAX_SQ_CIRCLE_QUEUE);
	_size = 0;
}

SqCircleQueue::~SqCircleQueue()
{
	SAFE_DEL_PTR(_queue);
}

// rear��ֵ,Ȼ��rear++,rear����ָ����һ������е�Ԫ�أ� rear׷��front
void SqCircleQueue::pushQueue(ElemType &e)
{
	if (isQueueFull())
	{
		std::cout << "circle queue is full" << std::endl;
		return;
	}

	_queue->element[_queue->rear] = e;
	_queue->rear = (_queue->rear+1) % MAX_SQ_CIRCLE_QUEUE; //ע���rear++,����+1ȡMAX_SQ_CIRCLE_QUEUE������
	_size++;
}

// ��rear׷������front�������ѭ��������������
bool SqCircleQueue::isQueueFull(void)
{
	return ((_queue->rear + 1) % MAX_SQ_CIRCLE_QUEUE == _queue->front);
}

//����front��ֵ��front++, frontָ����һ���������еĵ�Ԫ�أ�front׷��rear
ElemType& SqCircleQueue::popQueue(void)
{
	if (isQueueEmpty())
	{
		std::cout << "queue is empty" << std::endl;
		return _queue->element[0]; // ��Ĭ�Ϸ���init����������Ϊ0��Ԫ��ֵ(ֵΪ0������0�˻��ʼ��Ϊ0)
	}

	ElemType *e = &(_queue->element[_queue->front]);
	_queue->front = (_queue->front+1) % MAX_SQ_CIRCLE_QUEUE;// ע���front++,����+1ȡMAX_SQ_CIRCLE_QUEUE������
	_size--;
	return *e;

}

// ��front׷������rear�������ѭ�����������
bool SqCircleQueue::isQueueEmpty(void)
{
	return (_queue->rear == _queue->front);// or _size == 0
}


// �������Χ��0������0����ֱ��MAX_SQ_CIRCLE_QUEUE(������MAX_SQ_CIRCLE_QUEUE��
// ����ʵ�ʷ�ΧΪfront --> rear: �����������rear > front��û��Ȧ�� rear <= front����Ȧ��
ElemType& SqCircleQueue::getQueueByIndex(int index)
{
	if (isQueueEmpty())
	{
		std::cout << "queue is empty" << std::endl;
		return _queue->element[0]; // ��Ĭ�Ϸ���init����������Ϊ0��Ԫ��ֵ(ֵΪ0������0�˻��ʼ��Ϊ0)
	}

	if (index < 0 || index > MAX_SQ_CIRCLE_QUEUE-1)
	{
		std::cout << "index [" << index << "] is out of range: [0 ," << MAX_SQ_CIRCLE_QUEUE - 1 << "]" << std::endl;
		return _queue->element[0]; // ��Ĭ�Ϸ���init����������Ϊ0��Ԫ��ֵ(ֵΪ0������0�˻��ʼ��Ϊ0)
	}

	if (_queue->rear > _queue->front) // û�п�һȦ
	{
		if ((index >= _queue->rear) || (index < _queue->front)) // index ��Χ����Ϊ[front, rear)
		{
			std::cout << "index [" << index << "] is out of range: [" << _queue->front << ", " << _queue->rear << ")" << std::endl;
			return _queue->element[0]; // ��Ĭ�Ϸ���init����������Ϊ0��Ԫ��ֵ(ֵΪ0������0�˻��ʼ��Ϊ0)
		}

		return _queue->element[index];
	}

	if (_queue->rear < _queue->front) // ��һȦ��
	{
		if ((index >= _queue->rear) && (index < _queue->front)) // index ��Χ����Ϊ[front, MAX_SQ_CIRCLE_QUEUE) && [0, rear)
		{
			std::cout << "index [" << index << "] is out of range: [" << _queue->front << ", " << _queue->rear << ")" << std::endl;
			return _queue->element[0]; // ��Ĭ�Ϸ���init����������Ϊ0��Ԫ��ֵ(ֵΪ0������0�˻��ʼ��Ϊ0)
		}

		return _queue->element[index];
	}

}

int SqCircleQueue::locateQueue(ElemType &key)
{
	if (isQueueEmpty())
	{
		std::cout << "queue is empty" << std::endl;
		return _queue->element[0]; // ��Ĭ�Ϸ���init����������Ϊ0��Ԫ��ֵ(ֵΪ0����ʼ��Ϊ0)
	}

	bool isFound = false;
	int i = 0;
	if (_queue->rear > _queue->front) // û�п�һȦ
	{
		for (i = _queue->front; i < _queue->rear; i++) // i ���� [front, rear)
		{
			if (_queue->element[i] == key)
			{
				isFound = true;
				return i;
			}
		}
	}

	if (_queue->rear < _queue->front) // ��һȦ��,i����[front, MAX_SQ_CIRCLE_QUEUE) && [0, rear)
	{
		for (i = _queue->front; i < MAX_SQ_CIRCLE_QUEUE; i++) // i����[front, MAX_SQ_CIRCLE_QUEUE)
		{
			if (_queue->element[i] == key)
			{
				isFound = true;
				return i;
			}
		}
		for (i = 0; i < _queue->rear; i++) // i����[0, rear)
		{
			if (_queue->element[i] == key)
			{
				isFound = true;
				return i;
			}
		}
	}

	if (!isFound)
	{
		std::cout << "not found key is " << key << std::endl;
		return _queue->element[0]; // ��Ĭ�Ϸ���init����������Ϊ0��Ԫ��ֵ(ֵΪ0����ʼ��Ϊ0)
	}
}

int SqCircleQueue::getQueueSize(void)
{
	return _size;
}

void SqCircleQueue::traverseQueue(void)
{
	if (isQueueEmpty())
	{
		std::cout << "queue is empty" << std::endl;
		return;
	}

	std::cout << "_________begin traverse____________" << std::endl;
	int loopIndex = 0;
	if (_queue->rear > _queue->front) // û�п�һȦ
	{
		for (loopIndex = _queue->front; loopIndex < _queue->rear; loopIndex++) // loopIndex ���� [front, rear)
		{
			std::cout << "queue[" << loopIndex << "]: " << _queue->element[loopIndex] << "  ";
		}
	}

	if (_queue->rear < _queue->front) // ��һȦ��,loopIndex����[front, MAX_SQ_CIRCLE_QUEUE) && [0, rear)
	{
		for (loopIndex = _queue->front; loopIndex < MAX_SQ_CIRCLE_QUEUE; loopIndex++) // loopIndex����[front, MAX_SQ_CIRCLE_QUEUE)
		{
			std::cout << "queue[" << loopIndex << "]: " << _queue->element[loopIndex] << "  ";
		}
		for (loopIndex = 0; loopIndex < _queue->rear; loopIndex++) // loopIndex����[0, rear)
		{
			std::cout << "queue[" << loopIndex << "]: " << _queue->element[loopIndex] << "  ";
		}
	}

	std::cout << std::endl;
	std::cout << "_________end traverse____________" << std::endl;
}