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

// rear赋值,然后rear++,rear最终指向下一待入队列的元素， rear追赶front
void SqCircleQueue::pushQueue(ElemType &e)
{
	if (isQueueFull())
	{
		std::cout << "circle queue is full" << std::endl;
		return;
	}

	_queue->element[_queue->rear] = e;
	_queue->rear = (_queue->rear+1) % MAX_SQ_CIRCLE_QUEUE; //注意非rear++,而是+1取MAX_SQ_CIRCLE_QUEUE的余数
	_size++;
}

// 若rear追赶上了front，则表明循环队列入列满了
bool SqCircleQueue::isQueueFull(void)
{
	return ((_queue->rear + 1) % MAX_SQ_CIRCLE_QUEUE == _queue->front);
}

//返回front的值，front++, front指向下一个待出队列的的元素，front追赶rear
ElemType& SqCircleQueue::popQueue(void)
{
	if (isQueueEmpty())
	{
		std::cout << "queue is empty" << std::endl;
		return _queue->element[0]; // 空默认返回init操作的索引为0的元素值(值为0，被清0了或初始化为0)
	}

	ElemType *e = &(_queue->element[_queue->front]);
	_queue->front = (_queue->front+1) % MAX_SQ_CIRCLE_QUEUE;// 注意非front++,而是+1取MAX_SQ_CIRCLE_QUEUE的余数
	_size--;
	return *e;

}

// 若front追赶上了rear，则表明循环队列清空了
bool SqCircleQueue::isQueueEmpty(void)
{
	return (_queue->rear == _queue->front);// or _size == 0
}


// 索引最大范围从0（包括0），直到MAX_SQ_CIRCLE_QUEUE(不包括MAX_SQ_CIRCLE_QUEUE）
// 索引实际范围为front --> rear: 分两种情况，rear > front（没跨圈） rear <= front（跨圈）
ElemType& SqCircleQueue::getQueueByIndex(int index)
{
	if (isQueueEmpty())
	{
		std::cout << "queue is empty" << std::endl;
		return _queue->element[0]; // 空默认返回init操作的索引为0的元素值(值为0，被清0了或初始化为0)
	}

	if (index < 0 || index > MAX_SQ_CIRCLE_QUEUE-1)
	{
		std::cout << "index [" << index << "] is out of range: [0 ," << MAX_SQ_CIRCLE_QUEUE - 1 << "]" << std::endl;
		return _queue->element[0]; // 空默认返回init操作的索引为0的元素值(值为0，被清0了或初始化为0)
	}

	if (_queue->rear > _queue->front) // 没有跨一圈
	{
		if ((index >= _queue->rear) || (index < _queue->front)) // index 范围限制为[front, rear)
		{
			std::cout << "index [" << index << "] is out of range: [" << _queue->front << ", " << _queue->rear << ")" << std::endl;
			return _queue->element[0]; // 空默认返回init操作的索引为0的元素值(值为0，被清0了或初始化为0)
		}

		return _queue->element[index];
	}

	if (_queue->rear < _queue->front) // 跨一圈了
	{
		if ((index >= _queue->rear) && (index < _queue->front)) // index 范围限制为[front, MAX_SQ_CIRCLE_QUEUE) && [0, rear)
		{
			std::cout << "index [" << index << "] is out of range: [" << _queue->front << ", " << _queue->rear << ")" << std::endl;
			return _queue->element[0]; // 空默认返回init操作的索引为0的元素值(值为0，被清0了或初始化为0)
		}

		return _queue->element[index];
	}

}

int SqCircleQueue::locateQueue(ElemType &key)
{
	if (isQueueEmpty())
	{
		std::cout << "queue is empty" << std::endl;
		return _queue->element[0]; // 空默认返回init操作的索引为0的元素值(值为0，初始化为0)
	}

	bool isFound = false;
	int i = 0;
	if (_queue->rear > _queue->front) // 没有跨一圈
	{
		for (i = _queue->front; i < _queue->rear; i++) // i 遍历 [front, rear)
		{
			if (_queue->element[i] == key)
			{
				isFound = true;
				return i;
			}
		}
	}

	if (_queue->rear < _queue->front) // 跨一圈了,i遍历[front, MAX_SQ_CIRCLE_QUEUE) && [0, rear)
	{
		for (i = _queue->front; i < MAX_SQ_CIRCLE_QUEUE; i++) // i遍历[front, MAX_SQ_CIRCLE_QUEUE)
		{
			if (_queue->element[i] == key)
			{
				isFound = true;
				return i;
			}
		}
		for (i = 0; i < _queue->rear; i++) // i遍历[0, rear)
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
		return _queue->element[0]; // 空默认返回init操作的索引为0的元素值(值为0，初始化为0)
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
	if (_queue->rear > _queue->front) // 没有跨一圈
	{
		for (loopIndex = _queue->front; loopIndex < _queue->rear; loopIndex++) // loopIndex 遍历 [front, rear)
		{
			std::cout << "queue[" << loopIndex << "]: " << _queue->element[loopIndex] << "  ";
		}
	}

	if (_queue->rear < _queue->front) // 跨一圈了,loopIndex遍历[front, MAX_SQ_CIRCLE_QUEUE) && [0, rear)
	{
		for (loopIndex = _queue->front; loopIndex < MAX_SQ_CIRCLE_QUEUE; loopIndex++) // loopIndex遍历[front, MAX_SQ_CIRCLE_QUEUE)
		{
			std::cout << "queue[" << loopIndex << "]: " << _queue->element[loopIndex] << "  ";
		}
		for (loopIndex = 0; loopIndex < _queue->rear; loopIndex++) // loopIndex遍历[0, rear)
		{
			std::cout << "queue[" << loopIndex << "]: " << _queue->element[loopIndex] << "  ";
		}
	}

	std::cout << std::endl;
	std::cout << "_________end traverse____________" << std::endl;
}