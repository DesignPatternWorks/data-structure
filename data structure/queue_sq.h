#ifndef _QUEUE_SQ_H_
#define _QUEUE_SQ_H_

/************************************************************************/
/* 
队列：
队列(Queue)：也是运算受限的线性表。是一种先进先出(First In First Out ，简称FIFO)的线性表。只允许在表的一端进行插入，而在另一端进行删除。
队首(front) ：允许进行删除的一端称为队首。
队尾(rear) ：允许进行插入的一端称为队尾。
*/
/************************************************************************/

/*
利用一组连续的存储单元(一维数组) 依次存放从队首到队尾的各个元素，称为顺序队列。
对于队列，和顺序栈相类似，也有动态和静态之分
*/

/*
静态顺序队列：
设立一个队首指针front ，一个队尾指针rear ，分别指向队首和队尾元素。
在非空队列里，队首指针始终指向队头元素，而队尾指针始终指向队尾元素的下一位置。
初始化：front=rear=0。
入队：将新元素插入rear所指的位置，然后rear加1。
出队：删去front所指的元素，然后加1并返回被删元素。
队列为空：front=rear。
队满：rear=MAX_QUEUE_SIZE-1或front=rear

假溢出现象：
顺序队列中存在“假溢出”现象。因为在入队和出队操作中，头、尾指针只增加不减小，
致使被删除元素的空间永远无法重新利用。
因此，尽管队列中实际元素个数可能远远小于数组大小，
但可能由于尾指针巳超出向量空间的上界而不能做入队操作。该现象称为假溢出
*/


/*
循环队列
为充分利用向量空间，克服上述“假溢出”现象的方法
将为队列分配的向量空间看成为一个首尾相接的圆环，并称这种队列为循环队列(Circular Queue)

显然，为循环队列所分配的空间可以被充分利用，除非向量空间真的被队列元素全部占用，否则不会上溢。
因此，真正实用的顺序队列是循环队列

在循环队列中进行出队、入队操作时，队首、队尾指针仍要加1，朝前移动。
只不过当队首、队尾指针指向向量上界(MAX_QUEUE_SIZE-1)时，其加1操作的结果是指向向量的下界0。
即：
if(i+1==MAX_QUEUE_SIZE)   i=0; else     i++ ;
或：
i=(i+1)%MAX_QUEUE_SIZE

判断循环队列的“空”或“满”：
入队时尾指针向前追赶头指针，出队时头指针向前追赶尾指针，故队空和队满时头尾指针均相等。
因此，无法通过front=rear来判断队列“空”还是“满”。

解决此问题的方法是：约定入队前，测试尾指针在循环意义下加1后是否等于头指针，若相等则认为队满：
◆ rear所指的单元始终为空
◆ 循环队列为空：front=rear
◆ 循环队列满：(rear+1)%MAX_QUEUE_SIZE =front
*/

#define  MAX_SQ_CIRCLE_QUEUE  100

typedef int ElemType;

typedef struct tag_Sq_Circle_Queue
{
	int front;
	int rear;
	ElemType element[MAX_SQ_CIRCLE_QUEUE];
}Sq_Circle_Queue;

class SqCircleQueue
{
public:
	SqCircleQueue();
	~SqCircleQueue();
	void pushQueue(ElemType &e);
	ElemType& popQueue(void);
	bool isQueueEmpty(void);
	bool isQueueFull(void);
	ElemType& getQueueByIndex(int index);
	int locateQueue(ElemType &key);
	void traverseQueue(void);
	int getQueueSize(void);
private:
	void initQueue(void);
private:
	Sq_Circle_Queue *_queue;
	int _size;
};

#endif