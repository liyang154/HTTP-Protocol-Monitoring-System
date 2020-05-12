//
// Created by root on 20-4-26.
//

#ifndef IPTEST_HTTP_HASH_H
#define IPTEST_HTTP_HASH_H
//
// Created by wmd on 19-11-28.
//
#include "actrie.h"
#include "nids.h"
#define HashMaxSize 65535
typedef struct hash_list   //哈希表
{
    struct hash_node *first;   //指向的第一个节点
}hash_list[HashMaxSize];
typedef struct hash_node   //冲突结点
{
    struct tuple4 tupl4; //四元组
    //long int length;//长度
    unsigned short is_chunked;//标记是否为chunk传输
    unsigned short is_compresss; //标记是否为压缩，0代表不压缩，1代表gzip，2代表deflate
    struct hash_node *next; //处理冲突用的指针
    unsigned short is_text;
    char size[65535];//用于存放chunksize
    char size_data[65535*2];//用于存放chunkdata
    int size_q;//记录size数组的长度
    int size_p;//记录size_data数组的长度
    int count;//记录chunk中\r\n的个数
    int length;//用于记录chunkdata的大小
    TreeNode **state_node; //流式匹配状态指针
    int is_monitor;
    // z_stream strm;
}hash_node;

//create hash_list
void init_hashlist(hash_list hash);

//compute hashKey
unsigned int hash_key(struct tuple4 ip_and_port);

//compare tuple4
int tuple_cmp(struct tuple4 a, struct tuple4 b);

//put hash_node and data_node into hash_list
void insert_hash(struct tcp_stream tcp_connecttion, hash_list hashList);

//put data_node into hash_list
//void insert_data(struct tcp_stream tcp_connecttion , hash_node* hashNode, data_node* dataNode ,int k);

//delete a TCP stream in hash_list
void delete_hash_node(hash_list hash , struct tuple4 tupl4);
#endif //IPTEST_HTTP_HASH_H
