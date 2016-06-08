#include "stdafx.h"
#include "Test_tree.h"


void testTree(void)
{
	BTree tree = NULL;
	createBTree(tree); // 先序递归建立二叉树(0表示空)，输入1 2 4 0 0 5 0 0 3 6 0 0 7 0 0 
	/*
	                      1
						/   \
					   2     3
	                  /  \  /  \
	                 4    5 6   7
	*/

	std::cout << "preOrder Recursion Traverse BTree: " << std::endl;
	preorderTraverseByRecursion(tree);

	std::cout << "preOrder No Recursion  Traverse BTree: " << std::endl;
	preorderTraverseByNoRecursion(tree);

	std::cout << "inOrder Recursion Traverse BTree: " << std::endl;
	inorderTraverseByRecursion(tree);

	std::cout << "inOrder No Recursion Traverse BTree: " << std::endl;
	inorderTraverseByNoRecursion(tree);

	std::cout << "postOrder Recursion Traverse BTree: " << std::endl;
	postorderTraverseByRecursion(tree);

	std::cout << "postOrder No Recursion Traverse BTree: " << std::endl;
	postorderTraverseByNoRecursion(tree);

	std::cout << "levelOrder Traverse BTree: " << std::endl;
	levelorderTraverse(tree);

	std::cout << "BTree Depths is: " << getBTreeDepth(tree) << std::endl;
	std::cout << "BTree Node Number is: " << getBTreeNodeNumber(tree) << std::endl;

	destoryBTree(tree);
}

/*
运行结果：
1
please input 1 left child:
2
please input 2 left child:
4
please input 4 left child:
0
please input 4 right child:
0
please input 2 right child:
5
please input 5 left child:
0
please input 5 right child:
0
please input 1 right child:
3
please input 3 left child:
6
please input 6 left child:
0
please input 6 right child:
0
please input 3 right child:
7
please input 7 left child:
0
please input 7 right child:
0
preOrder Recursion Traverse BTree:
1
2
4
5
3
6
7
preOrder No Recursion  Traverse BTree:
1
2
4
5
3
6
7
inOrder Recursion Traverse BTree:
4
2
5
1
6
3
7
inOrder No Recursion Traverse BTree:
4
2
5
1
6
3
7
postOrder Recursion Traverse BTree:
4
5
2
6
7
3
1
postOrder No Recursion Traverse BTree:
4
5
2
6
7
3
1
levelOrder Traverse BTree:
1
2
3
4
5
6
7
BTree Depths is: 3
BTree Node Number is: 7
*/