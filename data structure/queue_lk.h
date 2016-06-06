#ifndef _QUEUE_LK_H_
#define _QUEUE_LK_H_

/************************************************************************/
/*
���У�
����(Queue)��Ҳ���������޵����Ա���һ���Ƚ��ȳ�(First In First Out �����FIFO)�����Ա�ֻ�����ڱ��һ�˽��в��룬������һ�˽���ɾ����
����(front) ���������ɾ����һ�˳�Ϊ���ס�
��β(rear) ��������в����һ�˳�Ϊ��β��
*/
/************************************************************************/


/*
���е���ʽ�洢�ṹ���Ϊ�����У��������ƽ��ڱ�ͷ����ɾ�������ͱ�β���в�������ĵ�����
��Ҫ���಻ͬ�Ľ�㣺
1.����Ԫ�ؽ��
2.���еĶ���ָ��Ͷ�βָ��Ľ��

���ӵĲ���ʵ�����ǵ�����Ĳ�����ֻ������ɾ���ڱ�ͷ���У������ڱ�β���С�
���롢ɾ��ʱ�ֱ��޸Ĳ�ͬ��ָ��
*/

typedef int ElemType;

typedef struct QNode // Ԫ�ؽ��
{
	ElemType element;
	QNode* next;
}QNode; 

typedef struct Lk_Queue   // ��ʽ���нṹ�壬����ͷָ��front��βָ��rear, ָ������ΪQNode
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



