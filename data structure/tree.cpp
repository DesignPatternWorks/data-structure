#include "stdafx.h"
#include "tree.h"
#include <stack>
#include <map>
#include <queue>


/*
������������
��ָ��ָ���Ĺ��ɶԶ������е�ÿ��������һ���ҽ�����һ�Σ�������ָ�Խ����ĳ�ִ����磺�����Ϣ���޸Ľ���ֵ��)
����������
����L��D��R�ֱ��ʾ���������������������ͱ��������������ݸ��ڵ�ı�����λ�ÿ�������������ֱ��ǣ�
DLR������(��)�������
LDR������(��)�������
LRD������(��)�����

������ͺ�����ȷ��Ψһ������
���������������Ψһȷ������
��������ͺ���Ҳ��Ψһȷ������
*/

/*
�����������㷨���ࣺ
���ڶ������ı������еݹ�����㷨�ͷǵݹ�����㷨��
�ݹ�����㷨�����зǳ������Ľṹ��ʵ���ϣ��ݹ��㷨����ϵͳͨ��ʹ�ö�ջ��ʵ�ֿ��Ƶġ�
�ǵݹ��㷨���ǵݹ��㷨�еĿ�����������߶����ʹ�ö�ջ��ʵ�ֵ�
*/


void visit(ElemType &e)
{
	std::cout << e << std::endl;
}

/*
����������������ݹ��㷨
��������Ϊ�գ����������������
�� ���ʸ���㣻
�� �������������(�ݹ���ñ��㷨)��
�� �������������(�ݹ���ñ��㷨)
*/
//DLR Recursion
void preorderTraverseByRecursion(BTNode *tree)
{
	if (!NULL_PTR(tree)) // �ǿ������
	{
		visit(tree->data); // ���ʸ��ڵ�Ԫ��
		preorderTraverseByRecursion(tree->Lchild); //�ݹ����������
		preorderTraverseByRecursion(tree->Rchild); //�ݹ����������
	}
}

/*
����������������ǵݹ��㷨
����˼·����������ֵ������ջ��Ȼ�������������
��ջʱ������ջ������������
*/
void preorderTraverseByNoRecursion(BTNode *tree)
{
	if (NULL_PTR(tree))
	{
		std::cout << "tree is empty" << std::endl;
		return;
	}

	BTNode *p = tree; // ��ʼΪ���ڵ�
	std::stack<BTNode*> s;
	while (!NULL_PTR(p) || !s.empty())
	{
		while (!NULL_PTR(p))
		{
			//�������㣬�������ջ������������  
			visit(p->data); //����������������ڷ��ʵ��λ��

			s.push(p);
			p = p->Lchild;
		}

		if (!s.empty())
		{
			//�������ջ������������  
			p = s.top();
			s.pop();

			p = p->Rchild;
		}
	}
}

/*
����������������ݹ��㷨
��������Ϊ�գ����������������
�� �������������(�ݹ���ñ��㷨)��
�� ���ʸ���㣻
�� �������������(�ݹ���ñ��㷨)��
*/
void inorderTraverseByRecursion(BTNode *tree)
{
	if (!NULL_PTR(tree))
	{
		inorderTraverseByRecursion(tree->Lchild);  //�ݹ����������
		visit(tree->data); // ���ʸ��ڵ�Ԫ��
		inorderTraverseByRecursion(tree->Rchild);  //�ݹ����������
	} 
}

/*
����������������ǵݹ��㷨
������ͬ���ǣ��������Ƚ�ջ���ٱ�����������
��ջʱ����������ֵ��Ȼ�����������
*/
void inorderTraverseByNoRecursion(BTNode *tree)
{
	if (NULL_PTR(tree))
	{
		std::cout << "tree is empty" << std::endl;
		return;
	}

	std::stack<BTNode*> s;
	BTNode *p = tree; // ��ʼΪ���ڵ�
	while (!NULL_PTR(p) || !s.empty())
	{
		while (!NULL_PTR(p)) //���������ϵĽڵ�ȫ��ѹ�뵽ջ��
		{
			//��ָ���ջ ������������
			s.push(p);
			p = p->Lchild; 
		}
		if (!s.empty())
		{
			//��ָ����ջ�����ʸ���㣬����������   
			p = s.top();
			s.pop();     

			visit(p->data); //��ǰ������������ڷ��ʵ��λ��

			p = p->Rchild; // ת���Һ���
		}
	}
}

/*
����������������ݹ��㷨
��������Ϊ�գ����������������
(1) �������������(�ݹ���ñ��㷨)��
(2) �������������(�ݹ���ñ��㷨)��
(3) ���ʸ���㣻
*/
void postorderTraverseByRecursion(BTNode *tree)
{
	if (!NULL_PTR(tree))
	{
		postorderTraverseByRecursion(tree->Lchild);  //�ݹ����������
		postorderTraverseByRecursion(tree->Rchild);  //�ݹ����������
		visit(tree->data); // ���ʸ��ڵ�Ԫ��
	}
}

/*
����������������ǵݹ��㷨
�������ĺ���ǵݹ�����������������ǵݹ��������΢���ӵ㡣
��Ϊ���������˳����������->������->����㣬���������ڱ�����������Ҫ�������������״̬��
����������һ��bool������ʶ���p������������״̬��false��ʾ������δ������true���ʾ�������ѱ���
*/
void postorderTraverseByNoRecursion(BTNode *tree)
{
	if (NULL_PTR(tree))
	{
		std::cout << "tree is empty" << std::endl;
		return;
	}

	std::stack<std::pair<BTNode*,bool>> s;
	BTNode *p = tree; // ��ʼΪ���ڵ�

	while (!NULL_PTR(p) || !s.empty())
	{
		while (!NULL_PTR(p)) //���������ϵĽڵ�ȫ��ѹ�뵽ջ��
		{
			s.push(std::make_pair(p, false)); //false��ʾ�����p��������δ����  
			p = p->Lchild;
		}
		if (!s.empty())
		{
			//��ָ����ջ������������ ,���ʸ����
			if (s.top().second == false) //������������δ����  
			{
				s.top().second = true; //��־������Ϊ�ѷ���
				p = s.top().first->Rchild; ////����������
			}
			else //�������ѷ���
			{
				visit(s.top().first->data); //��������ֵ
				s.pop(); // ������ջ
			}
		}
	}
}


/*
�������Ĳ�λ�������
��α������������ǴӸ���㿪ʼ����������δ������϶��£��������ҡ��������еĸ���㡣
Ϊ��֤�ǰ���α�������������һ�����У���ʼ��ʱΪ�ա�
��tree��ָ�������ָ���������α����ǵݹ��㷨�ǣ�
��������Ϊ�գ��򷵻أ�������p=tree��p��ӣ�
�� ����Ԫ�س��ӵ�p��
�� ����p��ָ��Ľ�㣻
�ǽ� p��ָ��Ľ��������ӽ��������ӡ�ֱ���ӿ�Ϊֹ
*/
void levelorderTraverse(BTNode *tree)
{
	if (NULL_PTR(tree))
	{
		std::cout << "tree is empty" << std::endl;
		return;
	}

	std::queue<BTNode*> q;
	BTNode *p;

	if (!NULL_PTR(tree))
	{
		q.push(tree); //�������ǿգ�������� 
	}

	while (!q.empty()) //���зǿ�
	{
		p = q.front(); 
		q.pop();

		visit(p->data); // ����Ԫ��

		if (!NULL_PTR(p->Lchild)) //���Ӳ��գ�����У�����������У���ΪҪ�ȱ�����(FIFO)
		{
			q.push(p->Lchild);
		}
		if (!NULL_PTR(p->Rchild)) //�Һ��Ӳ��գ������
		{
			q.push(p->Rchild);
		}
	}
}





/*
�������Ľ��������٣�
*/

//�ݹ�Ľ���һ�ö�����   
//����Ϊ����������������

//BTree* createBTree(void);
//void createBTree(BTNode **tree);
void createBTree(BTree &tree) // treeΪ����ָ�������
{
	ElemType data;
	std::cin  >> data;
	if (data == 0)
	{
		tree = NULL;
	}
	else
	{
		tree = (BTNode*)malloc(sizeof(BTNode));
		tree->data = data;

		std::cout << "please input " << data << " left child: " << std::endl;
		createBTree(tree->Lchild);
		std::cout << "please input " << data << " right child: " << std::endl;
		createBTree(tree->Rchild);
	}
}

//�ݹ��ɾ��һ�ö�����   
void destoryBTree(BTree &tree)
{
	if (!NULL_PTR(tree))
	{
		destoryBTree(tree->Lchild);
		destoryBTree(tree->Rchild);
		free(tree);
		tree = NULL;
	}
}

/*
��������Ⱥͽڵ���(�ݹ��㷨��
*/
int getBTreeDepth(BTNode *tree)
{
	if (NULL_PTR(tree))
	{
		return 0;
	}

	int ldepth;
	int rdepth;

	ldepth = getBTreeDepth(tree->Lchild);
	rdepth = getBTreeDepth(tree->Rchild);

	return (ldepth > rdepth) ? ldepth + 1 : rdepth + 1;
}

int getBTreeNodeNumber(BTNode *tree)
{
	if (NULL_PTR(tree))
	{
		return 0;
	}

	return 1 + getBTreeNodeNumber(tree->Lchild) + getBTreeNodeNumber(tree->Rchild);
}