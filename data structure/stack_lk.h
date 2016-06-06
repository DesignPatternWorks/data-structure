#ifndef _STACK_LK_H_
#define _STACK_LK_H_

/************************************************************************/
/* stack
ջ(Stack)���������ڱ��һ�˽��в����ɾ�����������Ա��ֳ�Ϊ����ȳ�LIFO (Last In First Out)��
�Ƚ����FILO (First In Last Out)���Ա�
ջ��(Top)��������в��롢ɾ��������һ�ˣ��ֳ�Ϊ��β����ջ��ָ��(top)��ָʾջ��Ԫ�ء�
ջ��(Bottom)���ǹ̶��ˣ��ֳ�Ϊ��ͷ��
��ջ��������û��Ԫ��ʱ��Ϊ��ջ
*/
/************************************************************************/

/*
ջ����ʽ�洢�ṹ��Ϊ��ջ�����������޵ĵ�����������ɾ������ֻ���ڱ�ͷλ���Ͻ��С�
��ˣ���ջû�б�Ҫ��������������ͷ��㣬ջ��ָ��top���������ͷָ��
*/

typedef int ElemType;

typedef struct tag_Lk_StackNode
{
	ElemType element;
	tag_Lk_StackNode *next;
}Lk_Stack_Node;

class LkStack
{
public:
	LkStack();
	~LkStack();
	void pushStack(ElemType &e);
	ElemType popStack(void); // �˴����ô���Ϊ���ã�����Ҫ��̬������ͷ��ڴ�
	bool isStackEmpty(void);
	ElemType& getStackByIndex(int index);
	int locateStack(ElemType &key);
	void traverseStack(void);
	int getStackSize(void);
private:
	void initStack(void);
private:
	Lk_Stack_Node *_stack;
	int _size;
};

#endif
