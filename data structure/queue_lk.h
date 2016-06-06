#ifndef _QUEUE_LK_H_
#define _QUEUE_LK_H_

/************************************************************************/
/*
队列：
队列(Queue)：也是运算受限的线性表。是一种先进先出(First In First Out ，简称FIFO)的线性表。只允许在表的一端进行插入，而在另一端进行删除。
队首(front) ：允许进行删除的一端称为队首。
队尾(rear) ：允许进行插入的一端称为队尾。
*/
/************************************************************************/


/*
队列的链式存储结构简称为链队列，它是限制仅在表头进行删除操作和表尾进行插入操作的单链表。
需要两类不同的结点：
1.数据元素结点
2.队列的队首指针和队尾指针的结点

链队的操作实际上是单链表的操作，只不过是删除在表头进行，插入在表尾进行。
插入、删除时分别修改不同的指针
*/

typedef int ElemType;

typedef struct QNode // 元素结点
{
	ElemType element;
	QNode* next;
}QNode; 

typedef struct Lk_Queue   // 链式队列结构体，包含头指针front和尾指针rear, 指针类型为QNode
{
	QNode *front;
	QNode *rear;
}Lk_Queue;

class LkQueue
{
public:
	LkQueue();
	~LkQueue();
	void pushQueue(ElemType &e);
	ElemType popQueue(void);
	bool isQueueEmpty(void);
	ElemType& getQueueByIndex(int index);
	int locateQueue(ElemType &key);
	void traverseQueue(void);
	int getQueueSize(void);
private:
	void initQueue(void);
private:
	Lk_Queue *_queue;
	int _size;
};

#endif



