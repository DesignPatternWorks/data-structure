#ifndef _TREE_H_
#define _TREE_H_

#include "DSComm.h"

/************************************************************************/
/*
树相关名词：
⑴ 结点(node)：一个数据元素及其若干指向其子树的分支。
⑵ 结点的度(degree) 、树的度：结点所拥有的子树的棵数称为结点的度（结点孩子的个数）。树中结点度的最大值称为树的度
⑶ 叶子(left)结点、非叶子结点：树中度为0的结点称为叶子结点(或终端结点)。
相对应地，度不为0的结点称为非叶子结点(或非终端结点或分支结点)。除根结点外，分支结点又称为内部结点
⑷ 孩子结点、双亲结点、兄弟结点：
一个结点的子树的根称为该结点的孩子结点(child)或子结点；相应地，该结点是其孩子结点的双亲结点(parent)或父结点
(5) 树的深度(depth)：树中结点的最大层次值，又称为树的高度
(6) 有序树和无序树：对于一棵树，若其中每一个结点的子树（若有）具有一定的次序，则该树称为有序树，否则称为无序树
*/
/************************************************************************/

/*
二叉树:
二叉树(Binary tree)是n(n≥0)个结点的有限集合。若n=0时称为空树，否则：
⑴ 有且只有一个特殊的称为树的根(Root)结点；
⑵ 若n>1时，其余的结点被分成为二个互不相交的子集T1,T2，分别称之为左、右子树，并且左、右子树又都是二叉树。
由此可知，二叉树的定义是递归的

二叉树性质：
性质1：在非空二叉树中，第i层上至多有2的i-1次方个结点
性质2：深度为k的二叉树至多有2的k次方-1个结点（k≧1)
性质3：对任何一棵二叉树，若其叶子结点数为n0，度为2的结点数为n2，则n0=n2+1

满二叉树：
一棵深度为k且有2k-1个结点的二叉树称为满二叉树(Full Binary Tree)

满二叉树性质：
性质1：基本特点是每一层上的结点数总是最大结点数。
性质2：满二叉树的所有的支结点都有左、右子树。
性质3：可对满二叉树的结点进行连续编号，若规定从根结点开始，按“自上而下、自左至右”的原则进行

完全二叉树：
如果深度为k，由n个结点的二叉树，当且仅当其每一个结点都与深度为k的满二叉树中编号从1到n的结点一一对应，该二叉树称为完全二叉树
或深度为k的满二叉树中编号从1到n的前n个结点构成了一棵深度为k的完全二叉树。其中  2的k-1次方 ≦ n≦2的k次方-1
(完全二叉树是满二叉树的一部分，而满二叉树是完全二叉树的特例)

完全二叉树性质：
性质1：若完全二叉树的深度为k ，则所有的叶子结点都出现在第k层或k-1层。
对于任一结点，如果其右子树的最大层次为l，则其左子树的最大层次为l或l+1
性质2：n个结点的完全二叉树深度为：└㏒2n┘ +1。
	其中符号： |x」表示不大于x的最大整数。
			 「x|表示不小于x的最小整数
性质3：
若对一棵有n个结点的完全二叉树(深度为└㏒2n┘+1)的结点按层（从第1层到第└㏒2n┘ +1层)序自左至右进行编号,则对于编号为i（1≦i≦n)的结点：
⑴ 若i=1：则结点i是二叉树的根，无双亲结点；否则，若i>1，则其双亲结点编号是 i/2 。
⑵ 如果2i>n：则结点i为叶子结点，无左孩子；否则，其左孩子结点编号是2i。
⑶ 如果2i+1>n：则结点i无右孩子；否则，其右孩子结点编号是2i+1

*/

/*
二叉树的存储结构:

1. 顺序存储结构
用一组地址连续的存储单元依次“自上而下、自左至右”存储完全二叉树的数据元素

2. 链式存储结构
设计不同的结点结构可构成不同的链式存储结构
2.1 二叉链表

二叉链表结点。有三个域：一个数据域，两个分别指向左右子结点的指针域：
typedef struct BTNode
{  ElemType  data ;
   struct BTNode  *Lchild , *Rchild ;
}BTNode;

2.2 三叉链表
除二叉链表的三个域外，再增加一个指针域，用来指向结点的父结点：
typedef struct BTNode_3
{  ElemType  data ;
   struct BTNode_3  *Lchild , *Rchild , *parent ;
}BTNode_3;
*/

// 使用二叉链表法定义二叉树
typedef int ElemType;
typedef struct BTNode
{
	ElemType  data;
	struct BTNode  *Lchild, *Rchild;
}BTNode, *BTree;

void visit(ElemType &e);
void preorderTraverseByRecursion(BTNode *tree);
void preorderTraverseByNoRecursion(BTNode *tree);
void inorderTraverseByRecursion(BTNode *tree);
void inorderTraverseByNoRecursion(BTNode *tree);
void postorderTraverseByRecursion(BTNode *tree);
void postorderTraverseByNoRecursion(BTNode *tree);
void levelorderTraverse(BTNode *tree);
void createBTree(BTree &tree);
void destoryBTree(BTree &tree);
int getBTreeDepth(BTNode *tree);
int getBTreeNodeNumber(BTNode *tree);

#endif