#ifndef __DEQUE_H__
#define __DEQUE_H__

#include <stdio.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif


#define MAX_SIZE 100  // 定义队列的最大容量

typedef struct {
	STRING strBuffer[CMD_STR_SIZE+1];
} DequeElement;

typedef struct {
	DequeElement cmd_data[MAX_SIZE];  // 存储数据的数组
	int front;           // 指向队列的前端
	int rear;            // 指向队列的后端
	int size;  			 // 记录deue的大小
	int error_id;   	 // 报错标志位 
} Deque;

// 初始化双端队列
void initDeque(Deque* deque);
// 判断队列是否为空
int isEmpty(Deque* deque);

// 判断队列是否满
int isFull(Deque* deque);

int getSize(Deque* deque);

// 从队列后端插入元素
void pushDeque(Deque* deque, DequeElement* data_ptr);

// 从队列前端删除元素
void popDeque(Deque* deque, DequeElement* data_ptr);



#endif
