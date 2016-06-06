#ifndef _DSCOMM_H_
#define _DSCOMM_H_


/********************头文件包含****************/
#include <malloc.h>
#include <iostream>
/*******************宏定义****************/
typedef unsigned char BYTE;
typedef int BOOL;
typedef unsigned short WORD16;

#ifndef TRUE
#define TRUE (BYTE)1
#endif

#ifndef FALSE
#define FALSE (BYTE)0
#endif

#define  RETURN_VOID 
#define  RETURN_NULL  NULL
#define  RETURN_INT    0

#define ASSERT_TRUE(expr, ret) if (!(expr)) \
{\
	std::cout << "assert failed in function[" << __FUNCTION__ << "] and line:[" << __LINE__ << "] "<< std::endl;\
	return ret;\
}

#define  ASSERT_TRUE_VOID(expr) ASSERT_TRUE(expr, RETURN_VOID)
#define  ASSERT_TRUE_NULL(expr) ASSERT_TRUE(expr, RETURN_NULL)
#define  ASSERT_TRUE_INT(expr)  ASSERT_TRUE(expr, RETURN_INT)


#define  ARRAY_SIZE(array)  sizeof(array)/sizeof(array[0])
#define NULL_PTR(ptr) ((ptr) == NULL)
#define SAFE_DEL_PTR(ptr) if (!(NULL_PTR(ptr))) {delete ptr; ptr = NULL;}

#define MALLOC_FAIL_RETURN_NULL(ptr) if (NULL_PTR(ptr))\
{\
	std::cout << "malloc failed" << std::endl;\
	return NULL;\
}
#define MALLOC_FAIL_NO_RETURN(ptr) if (NULL_PTR(ptr))\
{\
	std::cout << "malloc failed" << std::endl;\
	return;\
}
#define REALLOC_FAIL_NO_RETURN(ptr, delPtr) if (NULL_PTR(ptr))\
{\
	std::cout << "malloc failed" << std::endl;\
	delete delPtr;\
	delPtr = NULL;\
	return;\
}
#define REALLOC_FAIL_RETURN_NULL(ptr, delPtr) if (NULL_PTR(ptr))\
{\
	std::cout << "malloc failed" << std::endl;\
	delete delPtr;\
	delPtr = NULL;\
	return NULL;\
}
/********************数据类型定义****************/

/********************变量声明****************/

/********************外部函数声明****************/

#endif