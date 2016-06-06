#ifndef _QUEUE_SQ_H_
#define _QUEUE_SQ_H_

/************************************************************************/
/* 
���У�
����(Queue)��Ҳ���������޵����Ա���һ���Ƚ��ȳ�(First In First Out �����FIFO)�����Ա�ֻ�����ڱ��һ�˽��в��룬������һ�˽���ɾ����
����(front) ���������ɾ����һ�˳�Ϊ���ס�
��β(rear) ��������в����һ�˳�Ϊ��β��
*/
/************************************************************************/

/*
����һ�������Ĵ洢��Ԫ(һά����) ���δ�ŴӶ��׵���β�ĸ���Ԫ�أ���Ϊ˳����С�
���ڶ��У���˳��ջ�����ƣ�Ҳ�ж�̬�;�̬֮��
*/

/*
��̬˳����У�
����һ������ָ��front ��һ����βָ��rear ���ֱ�ָ����׺Ͷ�βԪ�ء�
�ڷǿն��������ָ��ʼ��ָ���ͷԪ�أ�����βָ��ʼ��ָ���βԪ�ص���һλ�á�
��ʼ����front=rear=0��
��ӣ�����Ԫ�ز���rear��ָ��λ�ã�Ȼ��rear��1��
���ӣ�ɾȥfront��ָ��Ԫ�أ�Ȼ���1�����ر�ɾԪ�ء�
����Ϊ�գ�front=rear��
������rear=MAX_QUEUE_SIZE-1��front=rear

���������
˳������д��ڡ��������������Ϊ����Ӻͳ��Ӳ����У�ͷ��βָ��ֻ���Ӳ���С��
��ʹ��ɾ��Ԫ�صĿռ���Զ�޷��������á�
��ˣ����ܶ�����ʵ��Ԫ�ظ�������ԶԶС�������С��
����������βָ���ȳ��������ռ���Ͻ����������Ӳ������������Ϊ�����
*/


/*
ѭ������
Ϊ������������ռ䣬�˷������������������ķ���
��Ϊ���з���������ռ俴��Ϊһ����β��ӵ�Բ�����������ֶ���Ϊѭ������(Circular Queue)

��Ȼ��Ϊѭ������������Ŀռ���Ա�������ã����������ռ���ı�����Ԫ��ȫ��ռ�ã����򲻻����硣
��ˣ�����ʵ�õ�˳�������ѭ������

��ѭ�������н��г��ӡ���Ӳ���ʱ�����ס���βָ����Ҫ��1����ǰ�ƶ���
ֻ���������ס���βָ��ָ�������Ͻ�(MAX_QUEUE_SIZE-1)ʱ�����1�����Ľ����ָ���������½�0��
����
if(i+1==MAX_QUEUE_SIZE)   i=0; else     i++ ;
��
i=(i+1)%MAX_QUEUE_SIZE

�ж�ѭ�����еġ��ա���������
���ʱβָ����ǰ׷��ͷָ�룬����ʱͷָ����ǰ׷��βָ�룬�ʶӿպͶ���ʱͷβָ�����ȡ�
��ˣ��޷�ͨ��front=rear���ж϶��С��ա����ǡ�������

���������ķ����ǣ�Լ�����ǰ������βָ����ѭ�������¼�1���Ƿ����ͷָ�룬���������Ϊ������
�� rear��ָ�ĵ�Ԫʼ��Ϊ��
�� ѭ������Ϊ�գ�front=rear
�� ѭ����������(rear+1)%MAX_QUEUE_SIZE =front
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