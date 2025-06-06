#include "deque.h"


// 初始化双端队列
void initDeque(Deque* deque) {
	deque->front = -1;  // 初始化front为-1，表示空
	deque->rear = -1;   // 初始化rear为-1，表示空
	deque->error_id = 0;
	deque->size = 0;
}

// 判断队列是否为空
int isEmpty(Deque* deque) {
	return (deque->size == 0);
}

// 判断队列是否满
int isFull(Deque* deque) {
	return ((deque->rear + 1) % MAX_SIZE == deque->front);
}

int getSize(Deque* deque) {
	return deque->size;
}

// 从队列后端插入元素
void pushDeque(Deque* deque, DequeElement* data_ptr) {
	if (isFull(deque)) {
		// printf("Deque is full!\n");
		return;
	}
	if (isEmpty(deque)) {
		deque->front = 0;  // 如果队列为空，设置front为0
	}
	deque->rear = (deque->rear + 1) % MAX_SIZE;  // 更新rear
	// brsmemset(deque->cmd_data, 0, sizeof(DequeElement));
	brsmemcpy(&deque->cmd_data[deque->rear], data_ptr, sizeof(DequeElement));  // 插入元素
	deque->size++;	// 增加大小
}

// 从队列前端删除元素
void popDeque(Deque* deque, DequeElement* data_ptr) {
	if (isEmpty(deque)) {
		//printf("Deque is empty!\n");
		// 若空，将传入的data_ptr清空
		brsmemset(data_ptr, 0, sizeof(DequeElement));
		return;  // 返回一个无效值
	}
	brsmemcpy(data_ptr, &deque->cmd_data[deque->front], sizeof(DequeElement));  // 获取front的值	
	brsmemset(&deque->cmd_data[deque->front], 0, sizeof(DequeElement));
	if (deque->front == deque->rear) {  // 如果只有一个元素
		deque->front = deque->rear = -1;  // 重置队列
	} else {
		deque->front = (deque->front + 1) % MAX_SIZE;  // 更新front
	}
	
	deque->size--;
	return;  // 队列前端元素
}

