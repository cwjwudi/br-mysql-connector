#include "deque.h"


// ��ʼ��˫�˶���
void initDeque(Deque* deque) {
	deque->front = -1;  // ��ʼ��frontΪ-1����ʾ��
	deque->rear = -1;   // ��ʼ��rearΪ-1����ʾ��
	deque->error_id = 0;
	deque->size = 0;
}

// �ж϶����Ƿ�Ϊ��
int isEmpty(Deque* deque) {
	return (deque->size == 0);
}

// �ж϶����Ƿ���
int isFull(Deque* deque) {
	return ((deque->rear + 1) % MAX_SIZE == deque->front);
}

int getSize(Deque* deque) {
	return deque->size;
}

// �Ӷ��к�˲���Ԫ��
void pushDeque(Deque* deque, DequeElement* data_ptr) {
	if (isFull(deque)) {
		// printf("Deque is full!\n");
		return;
	}
	if (isEmpty(deque)) {
		deque->front = 0;  // �������Ϊ�գ�����frontΪ0
	}
	deque->rear = (deque->rear + 1) % MAX_SIZE;  // ����rear
	// brsmemset(deque->cmd_data, 0, sizeof(DequeElement));
	brsmemcpy(&deque->cmd_data[deque->rear], data_ptr, sizeof(DequeElement));  // ����Ԫ��
	deque->size++;	// ���Ӵ�С
}

// �Ӷ���ǰ��ɾ��Ԫ��
void popDeque(Deque* deque, DequeElement* data_ptr) {
	if (isEmpty(deque)) {
		//printf("Deque is empty!\n");
		// ���գ��������data_ptr���
		brsmemset(data_ptr, 0, sizeof(DequeElement));
		return;  // ����һ����Чֵ
	}
	brsmemcpy(data_ptr, &deque->cmd_data[deque->front], sizeof(DequeElement));  // ��ȡfront��ֵ	
	brsmemset(&deque->cmd_data[deque->front], 0, sizeof(DequeElement));
	if (deque->front == deque->rear) {  // ���ֻ��һ��Ԫ��
		deque->front = deque->rear = -1;  // ���ö���
	} else {
		deque->front = (deque->front + 1) % MAX_SIZE;  // ����front
	}
	
	deque->size--;
	return;  // ����ǰ��Ԫ��
}

