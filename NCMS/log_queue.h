//
// Created by root on 20-4-26.
//

#ifndef IPTEST_LOG_QUEUE_H
#define IPTEST_LOG_QUEUE_H
//
// Created by yang on 2019/12/4.
//

#ifndef NCMP_LOG_QUEUE_H
#define NCMP_LOG_QUEUE_H
#define log_max_size 65535
//文件日志队列
typedef struct
{
    char filename[256];
    char suffix[8];//文件后缀
    char saddr[64];
    int sport;
    char daddr[64];
    int dport;
    char time[64];
    char addr[256];//文件下载地址
}file_log;
typedef struct
{
    int front;
    int rear;
    file_log *data;
}file_log_queue;
//ip封堵日志队列
typedef struct
{
    char saddr[64];
    int sport;
    char daddr[64];
    int dport;
    char time[64];
}ip_log;
typedef struct
{
    int front;
    int rear;
    ip_log *data;
}ip_log_queue;

//telnet关键字封堵日志队列
typedef struct
{
    char saddr[64];
    int sport;
    char daddr[64];
    int dport;
    char time[64];
    char keyword[256];
}telnet_log;
typedef struct
{
    int front;
    int rear;
    telnet_log *data;
}telnet_log_queue;

//url封堵日志队列
typedef struct
{
    char saddr[64];
    int sport;
    char daddr[64];
    int dport;
    char time[64];
    char keyword[256];
}url_log;
typedef struct
{
    int front;
    int rear;
    url_log *data;
}url_log_queue;

//ftp关键字监测队列
typedef struct
{
    char saddr[64];
    int sport;
    char daddr[64];
    int dport;
    char time[64];
    char keyword[256];
}ftp_log;
typedef struct
{
    int front;
    int rear;
    ftp_log *data;
}ftp_log_queue;

//am文本文件日志队列
typedef struct
{
    char saddr[64];
    int sport;
    char daddr[64];
    int dport;
    char time[64];
    char keyword[256];
}am_txt_log;
typedef struct
{
    int front;
    int rear;
    am_txt_log *data;
}am_txt_log_queue;

//am消息日志队列
typedef struct
{
    char saddr[64];
    int sport;
    char daddr[64];
    int dport;
    char time[64];
    char keyword[256];
}am_message_log;
typedef struct
{
    int front;
    int rear;
    am_message_log *data;
}am_message_log_queue;

//爱唱app日志队列
typedef struct
{
    char saddr[64];
    int sport;
    char daddr[64];
    int dport;
    char time[64];
    char keyword[256];
}aichang_log;
typedef struct
{
    int front;
    int rear;
    aichang_log *data;
}aichang_log_queue;

//http关键字监测日志队列
typedef struct
{
    char saddr[64];
    int sport;
    char daddr[64];
    int dport;
    char time[64];
    char keyword[256];
}http_log;
typedef struct
{
    int front;
    int rear;
    http_log *data;
}http_log_queue;

http_log_queue *httpLogQueue;
//dns域名欺骗日志队列
typedef struct
{
    char saddr[64];
    int sport;
    char daddr[64];
    int dport;
    char time[64];
    char keyword[256];//请求域名
    char cheat_addr[256];//欺骗地址
}dns_log;
typedef struct
{
    int front;
    int rear;
    dns_log *data;
}dns_log_queue;
//文件日志队列
int init_filelog_queue(file_log_queue *lq);
int en_filelog_queue(file_log_queue *lq,file_log *data);
int de_filelog_queue(file_log_queue*lq,file_log *data);
//ip封堵日志队列
int init_iplog_queue(ip_log_queue *lq);
int en_iplog_queue(ip_log_queue *lq,ip_log *data);
int de_iplog_queue(ip_log_queue *lq,ip_log *data);
//telnet关键字封堵日志
int init_telnetlog_queue(telnet_log_queue *lq);
int en_telnetlog_queue(telnet_log_queue *lq,telnet_log *data);
int de_telnetlog_queue(telnet_log_queue *lq,telnet_log *data);
//url封堵日志队列
int init_urllog_queue(url_log_queue *lq);
int en_urllog_queue(url_log_queue *lq,url_log *data);
int de_urllog_queue(url_log_queue *lq,url_log *data);
//ftp关键字监测日志队列
int init_ftplog_queue(ftp_log_queue *lq);
int en_ftplog_queue(ftp_log_queue *lq,ftp_log *data);
int de_ftplog_queue(ftp_log_queue *lq,ftp_log *data);
//am文本保存日志队列
int init_amtxt_log_queue(am_txt_log_queue *lq);
int en_amtxt_log_queue(am_txt_log_queue *lq,am_txt_log *data);
int de_amtxt_log_queue(am_txt_log_queue *lq,am_txt_log *data);
//am消息监测日志队列
int init_ammessage_log_queue(am_message_log_queue *lq);
int en_ammessage_log_queue(am_message_log_queue *lq,am_message_log *data);
int de_ammessage_log_queue(am_message_log_queue *lq,am_message_log *data);
//爱唱消息监测日志队列
int init_aichanglog_queue(aichang_log_queue *lq);
int en_aichanglog_queue(aichang_log_queue *lq,aichang_log *data);
int de_aichanglog_queue(aichang_log_queue *lq,aichang_log *data);
//http关键字监测日志队列
int init_httplog_queue(http_log_queue *lq);
int en_httplog_queue(http_log_queue *lq,http_log *data);
int de_httplog_queue(http_log_queue *lq,http_log *data);
//dns欺骗日志队列
int init_dnslog_queue(dns_log_queue *lq);
int en_dnslog_queue(dns_log_queue *lq,dns_log *data);
int de_dnslog_queue(dns_log_queue *lq,dns_log *data);
#endif //NCMP_LOG_QUEUE_H

#endif //IPTEST_LOG_QUEUE_H
