#ifndef __DEQUE_H__
#define __DEQUE_H__

#include <stdio.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif


#define MAX_SIZE 100  // ������е��������

typedef struct {
	STRING strBuffer[CMD_STR_SIZE+1];
} DequeElement;

typedef struct {
	DequeElement cmd_data[MAX_SIZE];  // �洢���ݵ�����
	int front;           // ָ����е�ǰ��
	int rear;            // ָ����еĺ��
	int size;  			 // ��¼deue�Ĵ�С
	int error_id;   	 // �����־λ 
} Deque;

// ��ʼ��˫�˶���
void initDeque(Deque* deque);
// �ж϶����Ƿ�Ϊ��
int isEmpty(Deque* deque);

// �ж϶����Ƿ���
int isFull(Deque* deque);

int getSize(Deque* deque);

// �Ӷ��к�˲���Ԫ��
void pushDeque(Deque* deque, DequeElement* data_ptr);

// �Ӷ���ǰ��ɾ��Ԫ��
void popDeque(Deque* deque, DequeElement* data_ptr);



#endif
