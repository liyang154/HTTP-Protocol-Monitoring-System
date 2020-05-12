//
// Created by root on 20-4-26.
//

//
// Created by wmd on 19-11-28.
//
#include <stdio.h>
#include <libnet.h>
#include "nids.h"
#include "http_hash.h"
#define HashMaxSize 65535

char ascii_string[1000000000];

char *char_to_ascii(char ch)
{
    char*string;
    ascii_string[0]=0;
    string=ascii_string;
    if(isgraph(ch))
    {
        *string++=ch;
    }
    else if(ch==' ')
    {
        *string++=ch;
    }
    else if(ch=='\n'||ch=='\r')
    {
        *string++=ch;
    }
    else{
        *string++='.';
    }
    *string=0;
    return ascii_string;
}
//create hash_list
void init_hashlist(hash_list hash)
{   int i = 0;
    for(i ; i < HashMaxSize ; i++){
        hash[i].first = NULL;
    }
    printf("%s\n","<--------------initialize hash_list succeed------------->");
}

//compute hashKey
unsigned int hash_key(struct tuple4 ip_and_port)
{
    unsigned int bsip,asip,bdip,adip,sport,dport,hash,hash1;
    bsip = ip_and_port.saddr >> 16;
    bsip = bsip&0x0000FFFF;
    asip = ip_and_port.saddr&0x0000FFFF;
    sport = ip_and_port.source;

    bdip = ip_and_port.daddr >> 16;
    bdip = bdip&0x0000FFFF;
    adip = ip_and_port.daddr&0x0000FFFF;
    dport = ip_and_port.dest;

    hash1=asip<<3|asip>>(16-3); hash1=hash1^adip; hash=hash1;
    hash1=bsip<<3|bsip>>(16-3); hash1=hash1^sport; hash^=hash1;
    hash1=bdip<<3|bdip>>(16-3); hash1=hash1^dport; hash^=hash1;
    hash = hash&0x0000FFFF;
    return hash;
}

//compare tuple4
int tuple_cmp(struct tuple4 a, struct tuple4 b)
{
    if(a.saddr == b.saddr && a.source == b.source && a.daddr ==b.daddr && a.dest == b.dest)
        return 1;
    else
        return 0;
}
void http_data(hash_node *hashNode,struct tcp_stream tcp_connecttion)
{
    printf("--------------向hashnode插入数据----------\n");
    char temp[1024];
    int i,j;
    int k=0;
    char content[65535];
    struct half_stream hlf;
    hlf=tcp_connecttion.client;
    memcpy(content,hlf.data,hlf.count_new);
    if(strstr(content,"Transfer-Encoding: chunked"))
    {
        hashNode->is_chunked=1;
    }
    else
    {
        hashNode->is_chunked=0;
    }
    for (i = 0; i < strlen(content); i++) {
        if (content[i] != '\n') {
            k++;
            continue;
        }
        for (j = 0; j < k; j++) {
            temp[j] = content[j + i - k];
        }
        temp[j] = '\0';
        if (strstr(temp, "Date")) {
            printf("当前的时间为(Date):%s\n", temp + strlen("Date"));
        }
        if (strstr(temp, "Server")) {
            printf("服务器(Server)：%s\n", temp + strlen("Server"));
        }
        if (strstr(temp, "Cache-Control")) {
            printf("缓存机制为(Cache-Control):%s\n", temp + strlen("Cache-Control:"));
        }
        if (strstr(temp, "Content-Length")) {
            printf("内容长度为(Content-Length):%s\n", temp + strlen("Content-Length:"));
        }
        if (strstr(temp, "Content-Type")) {
            printf("内容类型(Content-Type):%s\n", temp + strlen("Content-Type"));
            if(!strstr(temp,"text/html"))
            {
                hashNode->is_text=0;
            }
            else
                hashNode->is_text=1;
        }
        if (strstr(temp, "Content-Encoding")) {
            printf("内容类型(Content-Encoding):%s\n", temp + strlen("Content-Encoding"));
            if(strstr(temp,"gzip"))
                hashNode->is_compresss=1;
            else if(strstr(temp,"deflate"))
                hashNode->is_compresss=2;
            else
                hashNode->is_compresss=0;
            printf("%d\n",hashNode->is_compresss);
        }
        k = 0;
    }
}
//put hash_node and data_node into hash_list
void insert_hash(struct tcp_stream tcp_connecttion, hash_list hashList)
{

    unsigned int hashKey = hash_key(tcp_connecttion.addr); //computer hashKey
    printf("hashKey = %d\n",hashKey);
    hash_node* hashNode;
    hash_node* hashNodePre;
    if(hashList[hashKey].first == NULL){ //insert one hash_node and one data_node
        hashNode = (hash_node *) malloc(sizeof(hash_node));
        hashNode->state_node = (TreeNode **) malloc(sizeof(TreeNode));
        *hashNode->state_node = NULL;
        hashList[hashKey].first = hashNode;
        hashNode->tupl4 = tcp_connecttion.addr;
        hashNode->next = NULL;
        http_data(hashNode,tcp_connecttion);
        printf("<--------------insert first hash_node-------------->\n");
        return;
    }else//insert another hash_node
    {
        hashNodePre=hashList[hashKey].first;//find hash_node
        hashNode=hashNodePre->next;
        while(hashNode)//conflict,find the final hashNode
        {
            hashNodePre=hashNodePre->next;
            hashNode = hashNode->next;
        }
        hashNode=(hash_node *)malloc(sizeof(hash_node));
        hashNodePre->next=hashNode;
        hashNode->next=NULL;
        hashNode->tupl4=tcp_connecttion.addr;
        hashNode->state_node = (TreeNode **) malloc(sizeof(TreeNode));
        *hashNode->state_node = NULL;
        http_data(hashNode,tcp_connecttion);
        printf("<--------------insert confict hash_node-------------->\n");
    }
}


//delete a TCP stream in hash_list

void delete_hash_node(hash_list hashList , struct tuple4 tupl4)
{
    unsigned hashKey;
    hashKey = hash_key(tupl4);
    hash_node* hashNode;
    hash_node* hashNodePre;
    hashNodePre = hashList[hashKey].first;//first hashNode
    if(hashNodePre!=NULL)
    {
        hashNode = hashList[hashKey].first->next;//second hashNode
    }
    else
        return;
    if(tuple_cmp(hashNodePre->tupl4, tupl4))//match first hashNode
    {
        printf("<--------------delete hashKey = %d-------------->\n\n\n", hash_key(tupl4));
        hashList[hashKey].first = hashNode;
        free(hashNodePre);
        printf("%s\n\n\n", "<--------------delete first hash_node-------------->");
        return;
    }
    while(hashNode)
    {
        if(tuple_cmp(hashNode->tupl4, tupl4))
        {
            printf("<--------------delete hashKey = %d-------------->\n\n\n", hash_key(tupl4));
            hashNodePre->next = hashNode->next;
            free(hashNode);
            printf("%s\n\n\n", "<--------------delete a hash_node-------------->");
            return;
        }
        hashNodePre=hashNodePre->next;
        hashNode = hashNode->next;
    }
    printf("%s\n\n\n", "<--------------hash_node doesn't exist-------------->");
}
