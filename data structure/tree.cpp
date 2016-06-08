#include "stdafx.h"
#include "tree.h"
#include <stack>
#include <map>
#include <queue>


/*
遍历二叉树：
是指按指定的规律对二叉树中的每个结点访问一次且仅访问一次（访问是指对结点做某种处理。如：输出信息、修改结点的值等)
遍历方法：
若以L、D、R分别表示遍历左子树、遍历根结点和遍历右子树，根据根节点的遍历的位置可以三种情况，分别是：
DLR——先(根)序遍历。
LDR——中(根)序遍历。
LRD——后(根)序遍历

由先序和后序不能确定唯一的中序
而由先序和中序能唯一确定后序
而由中序和后序也能唯一确定先序
*/

/*
二叉树遍历算法分类：
对于二叉树的遍历，有递归遍历算法和非递归遍历算法。
递归遍历算法：具有非常清晰的结构，实际上，递归算法是由系统通过使用堆栈来实现控制的。
非递归算法：非递归算法中的控制是由设计者定义和使用堆栈来实现的
*/


void visit(ElemType &e)
{
	std::cout << e << std::endl;
}

/*
先序遍历二叉树：递归算法
若二叉树为空，则遍历结束；否则
⑴ 访问根结点；
⑵ 先序遍历左子树(递归调用本算法)；
⑶ 先序遍历右子树(递归调用本算法)
*/
//DLR Recursion
void preorderTraverseByRecursion(BTNode *tree)
{
	if (!NULL_PTR(tree)) // 非空则继续
	{
		visit(tree->data); // 访问根节点元素
		preorderTraverseByRecursion(tree->Lchild); //递归访问左子树
		preorderTraverseByRecursion(tree->Rchild); //递归访问右子树
	}
}

/*
先序遍历二叉树：非递归算法
基本思路是先输出结点值，再入栈，然后遍历左子树。
退栈时，遍历栈顶结点的右子树
*/
void preorderTraverseByNoRecursion(BTNode *tree)
{
	if (NULL_PTR(tree))
	{
		std::cout << "tree is empty" << std::endl;
		return;
	}

	BTNode *p = tree; // 初始为根节点
	std::stack<BTNode*> s;
	while (!NULL_PTR(p) || !s.empty())
	{
		while (!NULL_PTR(p))
		{
			//输出根结点，根结点入栈，遍历左子树  
			visit(p->data); //与中序遍历的区别在访问点的位置

			s.push(p);
			p = p->Lchild;
		}

		if (!s.empty())
		{
			//根结点退栈，遍历右子树  
			p = s.top();
			s.pop();

			p = p->Rchild;
		}
	}
}

/*
中序遍历二叉树：递归算法
若二叉树为空，则遍历结束；否则
⑴ 中序遍历左子树(递归调用本算法)；
⑵ 访问根结点；
⑶ 中序遍历右子树(递归调用本算法)。
*/
void inorderTraverseByRecursion(BTNode *tree)
{
	if (!NULL_PTR(tree))
	{
		inorderTraverseByRecursion(tree->Lchild);  //递归访问左子树
		visit(tree->data); // 访问根节点元素
		inorderTraverseByRecursion(tree->Rchild);  //递归访问右子树
	} 
}

/*
中序遍历二叉树：非递归算法
和先序不同的是，中序是先进栈，再遍历左子树；
出栈时，才输出结点值，然后遍历右子树
*/
void inorderTraverseByNoRecursion(BTNode *tree)
{
	if (NULL_PTR(tree))
	{
		std::cout << "tree is empty" << std::endl;
		return;
	}

	std::stack<BTNode*> s;
	BTNode *p = tree; // 初始为根节点
	while (!NULL_PTR(p) || !s.empty())
	{
		while (!NULL_PTR(p)) //把左子树上的节点全部压入到栈中
		{
			//根指针进栈 ，遍历左子树
			s.push(p);
			p = p->Lchild; 
		}
		if (!s.empty())
		{
			//根指针退栈，访问根结点，遍历右子树   
			p = s.top();
			s.pop();     

			visit(p->data); //与前序遍历的区别在访问点的位置

			p = p->Rchild; // 转向右孩子
		}
	}
}

/*
后序遍历二叉树：递归算法
若二叉树为空，则遍历结束；否则
(1) 后序遍历左子树(递归调用本算法)；
(2) 后序遍历右子树(递归调用本算法)；
(3) 访问根结点；
*/
void postorderTraverseByRecursion(BTNode *tree)
{
	if (!NULL_PTR(tree))
	{
		postorderTraverseByRecursion(tree->Lchild);  //递归访问左子树
		postorderTraverseByRecursion(tree->Rchild);  //递归访问右子树
		visit(tree->data); // 访问根节点元素
	}
}

/*
后序遍历二叉树：非递归算法
二叉树的后序非递归遍历，比先序和中序非递归遍历，稍微复杂点。
因为后序遍历的顺序是左子树->右子树->根结点，所以我们在遍历过程中需要标记左右子树的状态。
这里我们用一个bool变量标识结点p的右子树遍历状态，false表示右子树未遍历，true则表示右子树已遍历
*/
void postorderTraverseByNoRecursion(BTNode *tree)
{
	if (NULL_PTR(tree))
	{
		std::cout << "tree is empty" << std::endl;
		return;
	}

	std::stack<std::pair<BTNode*,bool>> s;
	BTNode *p = tree; // 初始为根节点

	while (!NULL_PTR(p) || !s.empty())
	{
		while (!NULL_PTR(p)) //把左子树上的节点全部压入到栈中
		{
			s.push(std::make_pair(p, false)); //false表示根结点p的右子树未访问  
			p = p->Lchild;
		}
		if (!s.empty())
		{
			//根指针退栈，遍历右子树 ,访问根结点
			if (s.top().second == false) //根结点的右子树未访问  
			{
				s.top().second = true; //标志右子树为已访问
				p = s.top().first->Rchild; ////遍历右子树
			}
			else //右子树已访问
			{
				visit(s.top().first->data); //输出根结点值
				s.pop(); // 根结点出栈
			}
		}
	}
}


/*
二叉树的层次化遍历：
层次遍历二叉树，是从根结点开始遍历，按层次次序“自上而下，从左至右”访问树中的各结点。
为保证是按层次遍历，必须设置一个队列，初始化时为空。
设tree是指向根结点的指针变量，层次遍历非递归算法是：
若二叉树为空，则返回；否则，令p=tree，p入队；
⑴ 队首元素出队到p；
⑵ 访问p所指向的结点；
⑶将 p所指向的结点的左、右子结点依次入队。直到队空为止
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
		q.push(tree); //若根结点非空，则入队列 
	}

	while (!q.empty()) //队列非空
	{
		p = q.front(); 
		q.pop();

		visit(p->data); // 访问元素

		if (!NULL_PTR(p->Lchild)) //左孩子不空，入队列，左孩子先入队列，因为要先被访问(FIFO)
		{
			q.push(p->Lchild);
		}
		if (!NULL_PTR(p->Rchild)) //右孩子不空，入队列
		{
			q.push(p->Rchild);
		}
	}
}





/*
二叉树的建立和销毁：
*/

//递归的建立一棵二叉树   
//输入为二叉树的先序序列

//BTree* createBTree(void);
//void createBTree(BTNode **tree);
void createBTree(BTree &tree) // tree为树根指针的引用
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

//递归的删除一棵二叉树   
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
二叉树深度和节点数(递归算法）
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