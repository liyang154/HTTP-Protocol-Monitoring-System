//
// Created by root on 20-4-26.
//

//
// Created by yang on 2019/12/4.
//
#include <stdlib.h>
#include <stdio.h>
#include "log_queue.h"
#define TRUE 1
#define ERROR 0
//文件日志队列操作
int init_filelog_queue(file_log_queue *lq)
{
    lq->data=(file_log*)malloc(log_max_size * sizeof(file_log));
    if(!(lq->data))
        return ERROR;
    lq->front=0;
    lq->rear=0;
    return TRUE;
}
int en_filelog_queue(file_log_queue *lq,file_log *data)
{
    if((lq->rear+1)%log_max_size==lq->front)//队满
        return ERROR;
    lq->data[lq->rear]=data[0];
    lq->rear=(lq->rear+1)%log_max_size;
    return TRUE;
}
int de_filelog_queue(file_log_queue *lq,file_log *data)
{
    if(lq->front==lq->rear)//队空
        return ERROR;
    data[0]=lq->data[lq->front];
    lq->front=(lq->front+1)%log_max_size;
    return TRUE;
}
//ip封堵日志队列操作
int init_iplog_queue(ip_log_queue *lq)
{
    lq->data=(ip_log*)malloc(log_max_size * sizeof(ip_log));
    if(!(lq->data))
        return ERROR;
    lq->front=0;
    lq->rear=0;
    return TRUE;
}
int en_iplog_queue(ip_log_queue *lq,ip_log *data)
{
    if((lq->rear+1)%log_max_size==lq->front)//队满
        return ERROR;
    lq->data[lq->rear]=data[0];
    lq->rear=(lq->rear+1)%log_max_size;
    return TRUE;
}
int de_iplog_queue(ip_log_queue *lq,ip_log *data)
{
    if(lq->front==lq->rear)//队空
        return ERROR;
    data[0]=lq->data[lq->front];
    lq->front=(lq->front+1)%log_max_size;
    return TRUE;
}
//telnet关键字封堵队列操作
int init_telnetlog_queue(telnet_log_queue *lq)
{
    lq->data=(telnet_log*)malloc(log_max_size * sizeof(telnet_log));
    if(!(lq->data))
        return ERROR;
    lq->front=0;
    lq->rear=0;
    return TRUE;
}
int en_telnetlog_queue(telnet_log_queue *lq,telnet_log *data)
{
    if((lq->rear+1)%log_max_size==lq->front)//队满
        return ERROR;
    lq->data[lq->rear]=data[0];
    lq->rear=(lq->rear+1)%log_max_size;
    return TRUE;
}
int de_telnetlog_queue(telnet_log_queue *lq,telnet_log *data)
{
    if(lq->front==lq->rear)//队空
        return ERROR;
    data[0]=lq->data[lq->front];
    lq->front=(lq->front+1)%log_max_size;
    return TRUE;
}
//url封堵日志队列操作
int init_urllog_queue(url_log_queue *lq)
{
    lq->data=(url_log*)malloc(log_max_size * sizeof(url_log));
    if(!(lq->data))
        return ERROR;
    lq->front=0;
    lq->rear=0;
    return TRUE;
}
int en_urllog_queue(url_log_queue *lq,url_log *data)
{
    if((lq->rear+1)%log_max_size==lq->front)//队满
        return ERROR;
    lq->data[lq->rear]=data[0];
    lq->rear=(lq->rear+1)%log_max_size;
    return TRUE;
}
int de_urllog_queue(url_log_queue *lq,url_log *data)
{
    if(lq->front==lq->rear)//队空
        return ERROR;
    data[0]=lq->data[lq->front];
    lq->front=(lq->front+1)%log_max_size;
    return TRUE;
}
//ftp关键字监测队列操作
int init_ftplog_queue(ftp_log_queue *lq)
{
    lq->data=(ftp_log*)malloc(log_max_size * sizeof(ftp_log));
    if(!(lq->data))
        return ERROR;
    lq->front=0;
    lq->rear=0;
    return TRUE;
}
int en_ftplog_queue(ftp_log_queue *lq,ftp_log *data)
{
    if((lq->rear+1)%log_max_size==lq->front)//队满
        return ERROR;
    lq->data[lq->rear]=data[0];
    lq->rear=(lq->rear+1)%log_max_size;
    return TRUE;
}
int de_ftplog_queue(ftp_log_queue *lq,ftp_log *data)
{
    if(lq->front==lq->rear)//队空
        return ERROR;
    data[0]=lq->data[lq->front];
    lq->front=(lq->front+1)%log_max_size;
    return TRUE;
}
//am文件监测队列操作
int init_amtxt_log_queue(am_txt_log_queue *lq)
{
    lq->data=(am_txt_log*)malloc(log_max_size * sizeof(am_txt_log));
    if(!(lq->data))
        return ERROR;
    lq->front=0;
    lq->rear=0;
    return TRUE;
}
int en_amtxt_log_queue(am_txt_log_queue *lq,am_txt_log *data)
{
    if((lq->rear+1)%log_max_size==lq->front)//队满
        return ERROR;
    lq->data[lq->rear]=data[0];
    lq->rear=(lq->rear+1)%log_max_size;
    return TRUE;
}
int de_amtxt_log_queue(am_txt_log_queue *lq,am_txt_log *data)
{
    if(lq->front==lq->rear)//队空
        return ERROR;
    data[0]=lq->data[lq->front];
    lq->front=(lq->front+1)%log_max_size;
    return TRUE;
}
//am消息监测队列操作
int init_ammessage_log_queue(am_message_log_queue *lq)
{
    lq->data=(am_message_log*)malloc(log_max_size * sizeof(am_message_log));
    if(!(lq->data))
        return ERROR;
    lq->front=0;
    lq->rear=0;
    return TRUE;
}
int en_ammessage_log_queue(am_message_log_queue *lq,am_message_log *data)
{
    if((lq->rear+1)%log_max_size==lq->front)//队满
        return ERROR;
    lq->data[lq->rear]=data[0];
    lq->rear=(lq->rear+1)%log_max_size;
    return TRUE;
}
int de_ammessage_log_queue(am_message_log_queue *lq,am_message_log *data)
{
    if(lq->front==lq->rear)//队空
        return ERROR;
    data[0]=lq->data[lq->front];
    lq->front=(lq->front+1)%log_max_size;
    return TRUE;
}
//爱唱消息监测队列操作
int init_aichanglog_queue(aichang_log_queue *lq)
{
    lq->data=(aichang_log*)malloc(log_max_size * sizeof(aichang_log));
    if(!(lq->data))
        return ERROR;
    lq->front=0;
    lq->rear=0;
    return TRUE;
}
int en_aichanglog_queue(aichang_log_queue *lq,aichang_log *data)
{
    if((lq->rear+1)%log_max_size==lq->front)//队满
        return ERROR;
    lq->data[lq->rear]=data[0];
    lq->rear=(lq->rear+1)%log_max_size;
    return TRUE;
}
int de_aichanglog_queue(aichang_log_queue *lq,aichang_log *data)
{
    if(lq->front==lq->rear)//队空
        return ERROR;
    data[0]=lq->data[lq->front];
    lq->front=(lq->front+1)%log_max_size;
    return TRUE;
}
//http关键字监测队列操作
int init_httplog_queue(http_log_queue *lq)
{
    lq->data=(http_log*)malloc(log_max_size * sizeof(http_log));
    if(!(lq->data))
        return ERROR;
    lq->front=0;
    lq->rear=0;
    return TRUE;
}
int en_httplog_queue(http_log_queue *lq,http_log *data)
{
    if((lq->rear+1)%log_max_size==lq->front)//队满
        return ERROR;
    lq->data[lq->rear]=data[0];
    /*printf("rear=%d\n", lq->rear);
    printf("lq->data[rear].keyword%s\n",lq->data[lq->rear].keyword);*/
    lq->rear=(lq->rear+1)%log_max_size;
    //printf("rear=%d\n", lq->rear);
    return TRUE;
}
int de_httplog_queue(http_log_queue *lq,http_log *data)
{
    if(lq->front==lq->rear)//队空
        return ERROR;
    data[0]=lq->data[lq->front];
    /* printf("front=%d\n", lq->front);
     printf("lq->data[front].keyword%s\n",lq->data[lq->front].keyword);*/
    lq->front=(lq->front+1)%log_max_size;
    //printf("front=%d\n", lq->front);
    return TRUE;
}
//dns欺骗日志队列操作
int init_dnslog_queue(dns_log_queue *lq)
{
    lq->data=(dns_log*)malloc(log_max_size * sizeof(dns_log));
    if(!(lq->data))
        return ERROR;
    lq->front=0;
    lq->rear=0;
    return TRUE;
}
int en_dnslog_queue(dns_log_queue *lq,dns_log *data)
{
    if((lq->rear+1)%log_max_size==lq->front)//队满
        return ERROR;
    lq->data[lq->rear]=data[0];
    lq->rear=(lq->rear+1)%log_max_size;
    return TRUE;
}
int de_dnslog_queue(dns_log_queue *lq,dns_log *data)
{
    if(lq->front==lq->rear)//队空
        return ERROR;
    data[0]=lq->data[lq->front];
    lq->front=(lq->front+1)%log_max_size;
    return TRUE;
}

