//
//  main.c
//  Queue
//
//  Created by SK_Wang on 2020/4/13.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define QUEUE_INIT_SIZE 100

typedef int Status;
typedef int QElemType;

// 队列的顺序存储
typedef struct {
    QElemType data[QUEUE_INIT_SIZE];
    int front;
    int rear;
}SqQueue;

Status InitQueue(SqQueue *Q) {
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

Status ClearQueue(SqQueue *Q) {
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

Status QueueEmpty(SqQueue Q) {
    return Q.front == Q.rear;
}

Status GetHead(SqQueue Q, QElemType *e) {
    if (Q.front == Q.rear) {
        return ERROR;
    }
    *e = Q.data[Q.front];
    return OK;
}

Status EnQueue(SqQueue *Q, QElemType e) {
    if ((Q->rear + 1) % QUEUE_INIT_SIZE == Q->front) {
        return ERROR;
    }
    
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % QUEUE_INIT_SIZE;
    return OK;
}

Status DeQueue(SqQueue *Q, QElemType *e) {
    if (Q->front == Q->rear) {
        return ERROR;
    }
    
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % QUEUE_INIT_SIZE;
    return OK;
}

Status QueueTraverse(SqQueue Q) {
    int i;
    i = Q.front;
    while ((i + Q.front) != Q.rear) {
        printf("%d", Q.data[i]);
        i = (i + 1) % QUEUE_INIT_SIZE;
    }
    return OK;
}

int QueueLength(SqQueue Q) {
    return (Q.rear - Q.front + QUEUE_INIT_SIZE) % QUEUE_INIT_SIZE;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    return 0;
}