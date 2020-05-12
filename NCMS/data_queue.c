//
// Created by root on 20-4-26.
//

#include "data_queue.h"
#include<stdlib.h>
#include <stdio.h>
#define TRUE 1
#define ERROR 0
//
// Created by yang on 2019/11/27.
//
int init_queue(data_queue*dq)
{
    dq->data=(struct tcp_stream *)malloc(MaxSize* sizeof(struct tcp_stream));
    if(!(dq->data))
        return ERROR;
    dq->front=0;
    dq->rear=0;
    return TRUE;
}
int en_queue(data_queue *dq,struct tcp_stream *data)
{
    if((dq->rear+1)%MaxSize==dq->front)//队满
        return ERROR;
    dq->data[dq->rear]=data[0];
    dq->rear=(dq->rear+1)%MaxSize;
    return TRUE;
}
int de_queue(data_queue *dq,struct tcp_stream *data)
{
    if(dq->front==dq->rear)//队空
        return ERROR;
    data[0]=dq->data[dq->front];
    dq->front=(dq->front+1)%MaxSize;
    return TRUE;
}