//
// Created by yang on 2019/12/3.
//

//
// Created by yang on 2019/12/2.
//
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libnet.h>
#include <zlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include "data_queue.h"
#include "http_hash.h"
#include "nids.h"
typedef struct
{
    int count;
}HashCount;
HashCount hash_count[65535];
struct hash_list http_hashList[HashMaxSize];
//struct tcp_stream http_connection;
#define OUTBUFFLEN 65535
z_stream strm;
int ret;
char **pattern,**url_pattern;
TreeNode *root,*url_root;
char ip_model[10][16];//ip匹配模型
int ip_num;//record ip num
char * getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);//获取1970-1-1到现在的时间结果保存到tv中
    uint64_t sec=tv.tv_sec;
    uint64_t min=tv.tv_sec/60;
    struct tm cur_tm;//保存转换后的时间结果
    localtime_r((time_t*)&sec,&cur_tm);
    char cur_time[20];
    snprintf(cur_time,20,"%d-%02d-%02d %02d:%02d:%02d",cur_tm.tm_year+1900,cur_tm.tm_mon+1,cur_tm.tm_mday,cur_tm.tm_hour,cur_tm.tm_min,cur_tm.tm_sec);
    //printf("current time is %s\n",cur_time);//打印当前时间
    return cur_time;
}

int char2int(char s[])
{
    char str[80];
    int k=0,m=0;
    int flag=1,mark;
    int num=0;
    for(int i=0;s[i]!='\0';i++)
        if((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='f')||(s[i]>='A'&&s[i]<='F'))
        {  //找出第一个十六进制字符所在的位置
            mark=i;
            break;
        }
    for(int i=0;i<mark;i++)//看看第一个十六进制字符前面有没有负号
        if(s[i]=='-')
        {
            flag=0;
            break;
        }
    for(int i=0;s[i]!='\0';i++)  //提取所有十六进制字符
        if((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='f')||(s[i]>='A'&&s[i]<='F'))
        {
            str[m]=s[i];
            m++;
        }
    str[m]='\0';
    for(int i=0;str[i]!='\0';i++)//将十六进制字符转换成十进制数
    {
        if(str[i]>='0'&&str[i]<='9')
            num=num*16+str[i]-'0';
        else if(str[i]>='a'&&str[i]<='f')
            num=num*16+str[i]-'a'+10;
        else if(str[i]>='A'&&str[i]<='F')
            num=num*16+str[i]-'A'+10;
    }
    if(flag==0)
        num=-num;
    //printf("%d",num);

    return num;
}
char *UnCompress(char *src, int len, char **unz_data, long int *unz_len, unsigned short is_compress)
{

    char *dest = NULL;
    unsigned have;
    unsigned char out[OUTBUFFLEN];
    int totalsize = 0;
    //allocate inflate state
    strm.avail_in = len;
    strm.next_in = (Byte*)src;
    //ret = inflateInit2(&strm, 47);
    //run inflate() on input until output buffer not full
    do
    {
        strm.avail_out = OUTBUFFLEN;
        strm.next_out = out;
        ret = inflate(&strm, Z_NO_FLUSH);
        if(ret!=Z_OK)
        {
            printf("Z_OK ERROR\n");
        }
        if(ret!=Z_STREAM_END)
        {
            printf("Z_STREAM_END ERROR\n");
        }
        if (ret != Z_OK && ret != Z_STREAM_END)
        {
            printf("\ninflate ret = %d\n", ret);
            //return NULL;
        }
        have = OUTBUFFLEN - strm.avail_out;
        printf("解压后的数据：\n");
        for(int i=0;i<have;i++)
        {
            printf("%c",out[i]);
        }
        printf("\n");
        totalsize += have;
        dest = (char*)realloc(dest,totalsize);
        if(dest == NULL)
        {
            perror("realloc");
            return NULL;
        }
        memcpy(dest + totalsize - have,out,have);
        dest[totalsize-1]='\0';
    } while (strm.avail_out == 0);
    //(void)inflateEnd(&strm);
    *unz_data = dest;
    *unz_len = totalsize;
    return dest;
}
void parse_client_data(struct tcp_stream *tcp_http_connection)
{
    int len1,len2;//记录chunksize和chunkdata的数组的长度
    char content[65535];
    char temp[1024];
    int ii;//游标，用于将数组清空
    int i,j;
    int k=0;
    int m=0;
    char *aftergzip=NULL;
    long int unlength=0;
    char entity_content[1024];
    int number;
    char address_content[65535];
    struct tuple4 ip_and_port=tcp_http_connection->addr;
    strcpy(address_content,inet_ntoa(*((
            struct in_addr *) &(ip_and_port.saddr))));
    sprintf(address_content+strlen(address_content),":%i",ip_and_port.source);
    strcat(address_content,"1-----------------------1");
    strcat(address_content,inet_ntoa(*((
            struct in_addr *) & (ip_and_port.daddr))));
    sprintf(address_content+strlen(address_content),":%i",ip_and_port.dest);
    strcat(address_content,"\n");
    printf("address_content=\n%s\n",address_content);
    unsigned hash=hash_key(tcp_http_connection->addr);
    hash_node *p=http_hashList[hash].first;
    if(p==NULL)
    {
        printf("p为空\n");
    } else{
        while(p)
        {
            if(tuple_cmp(tcp_http_connection->addr,p->tupl4))
            {
                printf("开始解析\n");
                printf("count_new=%d\n",tcp_http_connection->client.count_new);
                memcpy(content,tcp_http_connection->client.data,tcp_http_connection->client.count_new);
                number=tcp_http_connection->client.count_new;
                if(content[0]!='H'&&content[1]!='T'&&content[2]!='T'&&content[3]!='P'&&p->is_text!=0) {
                    if(p->is_monitor)//已经监测到关键字
                    {
                        return;
                    }
                    printf("实体内容为（1 续）:\n");
                    if(p->is_chunked)
                    {
                        printf("chunk(xu)\n");
                        for(m=0;m<number;m++)
                        {
                            if(p->count==0)//记录长度
                            {
                                if(content[m+1]=='\r'&&content[m+2]=='\n'&&content[m+3]=='\r'&&content[m+4]=='\n')//结尾
                                {
                                    printf("最后一个包\n");
                                    break;
                                }
                                else if (content[m] != '\r' && content[m + 1] != '\n') {
                                    p->size[p->size_q] = content[m];
                                    p->size_q++;
                                    //printf("aaa%s\n", p->size);
                                }
                                else
                                {
                                    //printf("bbb%s\n", p->size);
                                    p->count++;
                                    m++;
                                    continue;
                                }
                            }
                            else//记录数据
                            {
                                p->length=char2int(p->size);
                                if(p->size_p<p->length)
                                {
                                    p->size_data[p->size_p++]=content[m];
                                } else
                                {
                                    p->size_data[p->size_p] = '\0';
                                    m++;
                                    p->count=0;
                                    printf("size(xu)=%s\n",p->size);
                                    printf("q(xu)=%d\n",p->size_q);
                                    printf("p(xu)=%d\n", p->size_p);
                                    p->size_q=0;
                                    p->size_data[p->size_p]='\0';
                                    printf("----------1111111---------\n");
                                    UnCompress(p->size_data,p->size_p,&aftergzip,&unlength,1);
                                    p->is_monitor=Search_acTrie(root,p->state_node,aftergzip,strlen(aftergzip),pattern);
                                    len1=strlen(p->size);
                                    len2=strlen(p->size_data);
                                    for(ii=0;ii<len1;ii++)
                                    {
                                        p->size[ii]='\0';
                                    }
                                    for(ii=0;ii<len2;ii++)
                                    {
                                        p->size_data[ii]='\0';
                                    }
                                    p->size_p=0;
                                    p->length=0;
                                    if(p->is_monitor)//如果命中,写日志
                                    {
                                        printf("我命中了\n");
                                        FILE *file=fopen("/log/content_log.txt","a");
                                        if(file==NULL)
                                        {
                                            printf("open error\n");
                                            break;
                                        }
                                        char ip_match[16];
                                        char keyword[256];
                                        strcpy(ip_match,inet_ntoa(*((struct in_addr *) &(ip_and_port.daddr))));
                                        char local_ip[16];
                                        strcpy(local_ip,inet_ntoa(*((struct in_addr *) &(ip_and_port.saddr))));
                                        fputs("本地ip:",file);
                                        fputs(local_ip,file);
                                        fputs("\t本地端口:",file);
                                        fprintf(file,"%d",p->tupl4.source);
                                        fputs("\t\t访问服务器ip:",file);
                                        fputs(ip_match,file);
                                        fputs("\t\t访问服务器端口:",file);
                                        fprintf(file,"%d",p->tupl4.dest);
                                        //fputc(p->tupl4.dest,file);
                                        fputs("\ttime:",file);
                                        fputs(getCurrentTime(),file);
                                        memcpy(keyword,pattern[p->is_monitor-1],strlen(pattern[p->is_monitor-1]));
                                        keyword[strlen(pattern[p->is_monitor-1])]='\0';
                                        fputs("\t监测关键字:",file);
                                        fputs(keyword,file);
                                        fputs("\n",file);
                                        fclose(file);
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        printf("不是chunk2\n");
                        if(p->is_compresss)
                        {
                            printf("16进制\n");
                            char *sll=content;
                            for(int ii=0;ii<strlen(content);ii++)
                            {
                                printf("%2x",(unsigned char)*(sll+ii));
                            }
                            if(p->is_monitor)
                            {
                                return;
                            }
                            /*if(p->is_monitor)//命中
                            {
                                printf("匹配成功\n");
                                break;
                            }else{*/
                            UnCompress(content,number,&aftergzip,&unlength,p->is_compresss);
                            p->is_monitor=Search_acTrie(root,p->state_node,aftergzip,(int)strlen(aftergzip),pattern);
                            if(p->is_monitor)//如果命中,写日志
                            {
                                printf("我命中了\n");
                                FILE *file=fopen("/log/content_log.txt","a");
                                if(file==NULL)
                                {
                                    printf("open error\n");
                                    break;
                                }
                                char ip_match[16];
                                char keyword[256];
                                strcpy(ip_match,inet_ntoa(*((struct in_addr *) &(ip_and_port.daddr))));
                                char local_ip[16];
                                strcpy(local_ip,inet_ntoa(*((struct in_addr *) &(ip_and_port.saddr))));
                                fputs("本地ip:",file);
                                fputs(local_ip,file);
                                fputs("\t本地端口:",file);
                                fprintf(file,"%d",p->tupl4.source);
                                fputs("\t\t访问服务器ip:",file);
                                fputs(ip_match,file);
                                fputs("\t\t访问服务器端口:",file);
                                fprintf(file,"%d",p->tupl4.dest);
                                fputs("\ttime:",file);
                                fputs(getCurrentTime(),file);
                                memcpy(keyword,pattern[p->is_monitor-1],strlen(pattern[p->is_monitor-1]));
                                keyword[strlen(pattern[p->is_monitor-1])]='\0';
                                fputs("\t监测关键字:",file);
                                fputs(keyword,file);
                                fputs("\n",file);
                                fclose(file);
                            }
                            /* printf("----------22222222---------\n");
                             if(*(p->state_node)==NULL)
                             {
                                 printf("我是空的1\n");
                             }
                             p->is_monitor=Search_acTrie(root,p->state_node,aftergzip,(int)strlen(aftergzip),pattern);
                             if(*(p->state_node)==NULL)
                             {
                                 printf("我是空的2\n");
                             }
                             if(p->is_monitor)//如果命中,写日志
                             {*//*
                                    http_log *httpLog=(http_log *)malloc(sizeof(http_log));
                                    memcpy(httpLog->saddr, inet_ntoa(*((struct in_addr *) &(p->tupl4.saddr))), strlen(inet_ntoa(*((struct in_addr *) &(p->tupl4.saddr)))));
                                    printf("addr=%s\n",httpLog->saddr);
                                    free(httpLog);*//*
                                    printf("我命中了\n");
                                }*/
                            // }

                        } else
                        {
                            printf("%s\n",content);
                            printf("----------333333333---------\n");
                            Search_acTrie(root,p->state_node,content,number,pattern);
                        }
                    }
                    //UnCompress(content,number,&aftergzip,&unlength,1);

                }
                else {
                    for(int ii=0;ii<65535;ii++)//数组清空
                    {
                        p->size[ii]='\0';
                        p->size_data[ii]='\0';
                    }
                    p->size_p=0;
                    p->size_q=0;
                    p->count=0;
                    p->length=0;
                    p->is_monitor=0;
                    strm.zalloc = Z_NULL;
                    strm.zfree = Z_NULL;
                    strm.opaque = Z_NULL;
                    strm.avail_in = 0;
                    strm.next_in = Z_NULL;
                    ret = inflateInit2(&strm, 47);
                    if (ret != Z_OK) {
                        printf("初始化失败\n");
                        return;
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
                            printf("%s\n", temp);
                        }
                        if (strstr(temp, "Server")) {
                            printf("服务器(Server)：%s\n", temp + strlen("Server"));
                            printf("%s\n", temp);
                        }
                        if (strstr(temp, "Cache-Control")) {
                            printf("缓存机制为(Cache-Control):%s\n", temp + strlen("Cache-Control:"));
                        }
                        if (strstr(temp, "Content-Length")) {
                            printf("内容长度为(Content-Length):%s\n", temp + strlen("Content-Length:"));
                        }
                        if (strstr(temp, "Content-Type")) {
                            printf("内容类型(Content-Type):%s\n", temp + strlen("Content-Type"));
                        }
                        if (strstr(temp, "Content-Encoding")) {
                            printf("内容类型(Content-Encoding):%s\n", temp + strlen("Content-Encoding"));
                        }
                        /*获取实体内容*/
                        if ((content[i] == '\n') && (content[i + 1] == '\r')) {
                            if (i + 3 == strlen(content)) {
                                printf("无实体内容\n");
                                break;
                            }
                            for (j = 0; j < number - i - 3; j++)
                                entity_content[j] = content[i + 3 + j];
                            entity_content[j]='\0';
                            printf("实体内容为:\n");
                            if(p->is_text)
                            {
                                if(p->is_chunked)
                                {
                                    printf("chunk\n");
                                    for(m=0;m<j;m++)
                                    {
                                        if(p->count==0)//记录长度
                                        {
                                            if (entity_content[m] != '\r' && entity_content[m + 1] != '\n') {
                                                p->size[p->size_q++] = entity_content[m];
                                            }
                                            else
                                            {
                                                p->count++;
                                                m++;
                                                continue;
                                            }
                                        }
                                        else//记录数据
                                        {
                                            p->length=char2int(p->size);
                                            if(p->size_p<p->length)
                                            {
                                                p->size_data[p->size_p++]=entity_content[m];
                                            }
                                            else
                                            {
                                                p->size_data[p->size_p] = '\0';
                                                m++;
                                                p->count=0;
                                                printf("size=%s\n",p->size);
                                                printf("q=%d\n",p->size_q);
                                                printf("p=%d\n", p->size_p);
                                                p->size_q=0;
                                                if(p->is_monitor)
                                                {
                                                    return;
                                                }
                                                UnCompress(p->size_data,p->size_p,&aftergzip,&unlength,1);
                                                printf("----------44444444---------\n");
                                                p->is_monitor=Search_acTrie(root,p->state_node,aftergzip,strlen(aftergzip),pattern);
                                                len1=strlen(p->size);
                                                len2=strlen(p->size_data);
                                                for(ii=0;ii<len1;ii++)
                                                {
                                                    p->size[ii]='\0';
                                                }
                                                for(ii=0;ii<len2;ii++)
                                                {
                                                    p->size_data[ii]='\0';
                                                }
                                                p->length=0;
                                                p->size_p=0;
                                                if(p->is_monitor)
                                                {
                                                    printf("我命中了\n");
                                                    FILE *file=fopen("/log/content_log.txt","a");
                                                    if(file==NULL)
                                                    {
                                                        printf("open error\n");
                                                        break;
                                                    }
                                                    char ip_match[16];
                                                    char keyword[256];
                                                    strcpy(ip_match,inet_ntoa(*((struct in_addr *) &(ip_and_port.daddr))));
                                                    char local_ip[16];
                                                    strcpy(local_ip,inet_ntoa(*((struct in_addr *) &(ip_and_port.saddr))));
                                                    fputs("本地ip:",file);
                                                    fputs(local_ip,file);
                                                    fputs("\t本地端口:",file);
                                                    fprintf(file,"%d",p->tupl4.source);
                                                    fputs("\t\t访问服务器ip:",file);
                                                    fputs(ip_match,file);
                                                    fputs("\t\t访问服务器端口:",file);
                                                    fprintf(file,"%d",p->tupl4.dest);
                                                    fputs("\ttime:",file);
                                                    fputs(getCurrentTime(),file);
                                                    memcpy(keyword,pattern[p->is_monitor-1],strlen(pattern[p->is_monitor-1]));
                                                    keyword[strlen(pattern[p->is_monitor-1])]='\0';
                                                    fputs("\t监测关键字:",file);
                                                    fputs(keyword,file);
                                                    fputs("\n",file);
                                                    fclose(file);
                                                }
                                            }
                                        }
                                    }
                                } else
                                {
                                    printf("不是chunk\n");
                                    if(p->is_compresss)
                                    {
                                        if(p->is_monitor)
                                        {
                                            return;
                                        }
                                        /*if(p->is_monitor)//如果已经匹配命中，则直接返回
                                        {
                                            printf("关键字命中");
                                            break;
                                        }

                                        else{*/
                                        UnCompress(entity_content,j,&aftergzip,&unlength,p->is_compresss);
                                        p->is_monitor=Search_acTrie(root,p->state_node,aftergzip,strlen(aftergzip),pattern);
                                        if(p->is_monitor)
                                        {
                                            printf("我命中了\n");
                                            FILE *file=fopen("/log/content_log.txt","a");
                                            if(file==NULL)
                                            {
                                                printf("open error\n");
                                                break;
                                            }
                                            char ip_match[16];
                                            char keyword[256];
                                            strcpy(ip_match,inet_ntoa(*((struct in_addr *) &(ip_and_port.daddr))));
                                            char local_ip[16];
                                            strcpy(local_ip,inet_ntoa(*((struct in_addr *) &(ip_and_port.saddr))));
                                            fputs("本地ip:",file);
                                            fputs(local_ip,file);
                                            fputs("\t本地端口:",file);
                                            fprintf(file,"%d",p->tupl4.source);
                                            fputs("\t\t访问服务器ip:",file);
                                            fputs(ip_match,file);
                                            fputs("\t\t访问服务器端口:",file);
                                            fprintf(file,"%d",p->tupl4.dest);
                                            fputs("\ttime:",file);
                                            fputs(getCurrentTime(),file);
                                            memcpy(keyword,pattern[p->is_monitor-1],strlen(pattern[p->is_monitor-1]));
                                            keyword[strlen(pattern[p->is_monitor-1])]='\0';
                                            fputs("\t监测关键字:",file);
                                            fputs(keyword,file);
                                            fputs("\n",file);
                                            fclose(file);
                                        }
                                        /* printf("----------5555555---------\n");

                                         if(p->is_monitor)//如果命中,写日志
                                         {
                                             *//*http_log *httpLog=(http_log *)malloc(sizeof(http_log));
                                                memcpy(httpLog->saddr, inet_ntoa(*((struct in_addr *) &(p->tupl4.saddr))), strlen(inet_ntoa(*((struct in_addr *) &(p->tupl4.saddr)))));
                                                printf("addr=%s\n",httpLog->saddr);
                                                free(httpLog);*//*
                                                printf("我命中l\n");
                                            }*/
                                        // }
                                    } else
                                    {
                                        printf("%s\n",entity_content);
                                        printf("----------66666666---------\n");
                                        // Search_acTrie(root,p->state_node,aftergzip,strlen(aftergzip),pattern);
                                    }

                                }
                            } else{
                                printf("不是html\n");
                                return;
                            }
                            break;
                        }
                        k = 0;
                    }
                }


                return;
            } else
                p=p->next;
        }
    }
}
void parse_server_data(char content[],int number,struct tcp_stream *tcp_http_connection)
{
/*    hash_node *p=http_hashList[hash].first;
    while(p)
    {
        if (tuple_cmp(p->tupl4, tcp_http_connection->addr))
            break;
        else
            p = p->next;
    }
    if(p==NULL)
    {
        printf("p1为空\n");
        return;
    }*/
    TreeNode **state_node=(TreeNode **) malloc(sizeof(TreeNode)); //流式匹配状态指针
    *state_node=NULL;
    char url[2048]={'\0'};
    char temp[1024];
    char str1[512];
    char str2[512];
    char str3[512];
    int i=0,j=0,k=0;
    //char entity_content[1024];
    for(i=0;i<(int)strlen(content);i++)
    {
        if(content[i]!='\n')
        {
            k++;
            continue;
        }
        for(j=0;j<k;j++)
        {
            temp[j]=content[j+i-k];
        }
        temp[j]='\0';
        if(strstr(temp,"GET"))
        {
            printf("请求行为：");
            printf("%s\n",temp);
            sscanf(temp,"%s %s %s",str1,str2,str3);
            printf("使用的命令为：%s\n",str1);
            printf("获得的资源为：%s\n",str2);
            printf("HTTP协议类型为：%s\n",str3);
        }
        if(strstr(temp,"Referer"))
        {
            printf("转移地址为(Referer):%s\n",temp+strlen("Referer:"));
        }
        if(strstr(temp,"Accept-Language"))
            printf("使用的语言为（Accept-language）:%s\n",temp+strlen("Accept-Language:"));
        if(strstr(temp,"Accept-Encoding"))
            printf("接收的编码为(Accept-Encoding):%s\n",temp+strlen("Accept-Encoding:"));
        if(strstr(temp,"Host"))
        {
            printf("访问的主机为（Host）:%s\n",temp+strlen("Host: "));
            int ii;
            for(ii=0;temp[ii]!='\r';ii++)
            {
                url[ii]=temp[(int)strlen("Host: ")+ii];
            }
            /* printf("url1%s\n",url);
             printf("urlen1=%d\n",(int)strlen(url));*/
            int len=(int)strlen(url)-1;
            for(ii=0;ii<strlen(str2);ii++)
            {
                url[len+ii]=str2[ii];
            }
            /*  printf("str2=%d\n",(int)strlen(str2));
              printf("urlen2=%d\n",(int)strlen(url));*/
            printf("url:%s\n",url);
            int n=Search_acTrie(url_root,state_node,url,strlen(url),url_pattern);
            ///////////////url封堵
            if(n)
            {
                nids_killtcp(tcp_http_connection);
                FILE *file = fopen("/log/url_log.txt", "a");
                if(file==NULL)
                {
                    printf("open error\n");
                    break;
                }
                char local_ip[16];
                char server_ip[16];
                char match_url[2048];//some resources' url are too long
                memcpy(match_url,url_pattern[n-1],strlen(url_pattern[n-1]));
                match_url[strlen(pattern[n-1])]='\0';
                strcpy(local_ip,inet_ntoa(*((struct in_addr *) &(tcp_http_connection->addr.saddr))));
                strcpy(server_ip,inet_ntoa(*((struct in_addr *) &(tcp_http_connection->addr.daddr))));
                fputs("本地ip:",file);
                fputs(local_ip,file);
                fputs("\t本地端口:",file);
                fprintf(file,"%d",tcp_http_connection->addr.source);
                fputs("\t\t访问服务器ip:",file);
                fputs(server_ip,file);
                fputs("\t\t访问服务器端口:",file);
                fprintf(file,"%d",tcp_http_connection->addr.dest);
                fputs("\ttime:",file);
                fputs(getCurrentTime(),file);
                fputs("\t访问网站url:",file);
                fputs(url,file);
                fputs("\t命中url字符串:",file);
                fputs(match_url,file);
                fputs("\n",file);
                fclose(file);
                return;
            }
            printf("url封堵n=%d\n", n);
            return;
        }
        k=0;
    }
}
void http_protocol_callback(struct tcp_stream* tcp_http_connection,void **param)
{
    char ip_input[16];
    unsigned int hash;
    char address_content[1024];
    char content[65535];
    struct tuple4 ip_and_port=tcp_http_connection->addr;
    strcpy(ip_input,inet_ntoa(*((struct in_addr *) &(ip_and_port.daddr))));
    printf("访问网页服务器ip=%s\n",ip_input);
    for(int i=0;i<ip_num;i++)
    {
        if(strcmp(ip_model[i],ip_input)==0)
        {
            nids_killtcp(tcp_http_connection);
            printf("ip shot位置：%d\n",i+1);
            FILE *file = fopen("/log/ip_log.txt", "a");
            if(file==NULL)
            {
                printf("open error\n");
                break;
            }
            char local_ip[16];
            strcpy(local_ip,inet_ntoa(*((struct in_addr *) &(ip_and_port.saddr))));
            fputs("本地ip:",file);
            fputs(local_ip,file);
            fputs("\t本地端口:",file);
            fprintf(file,"%d",ip_and_port.source);
            fputs("\t\t访问服务器ip:",file);
            fputs(ip_input,file);
            fputs("\t\t访问服务器端口:",file);
            fprintf(file,"%d",ip_and_port.dest);
            fputs("\ttime:",file);
            fputs(getCurrentTime(),file);
            fputs("\n",file);
            fclose(file);
            return;
        }
    }
    strcpy(address_content,inet_ntoa(*((
            struct in_addr *) &(ip_and_port.saddr))));
    sprintf(address_content+strlen(address_content),":%i",ip_and_port.source);
    strcat(address_content,"<---->");
    strcat(address_content,inet_ntoa(*((
            struct in_addr *) & (ip_and_port.daddr))));
    sprintf(address_content+strlen(address_content),":%i",ip_and_port.dest);
    strcat(address_content,"\n");
    if(tcp_http_connection->nids_state==NIDS_JUST_EST)
    {
        //nids_killtcp(tcp_http_connection);
        if(tcp_http_connection->addr.dest!=80)//只捕获HTTP协议数据包
        {
            return;
        }
        tcp_http_connection->client.collect++;//浏览器接受数据
        tcp_http_connection->server.collect++;//web服务器接收数据
        printf("\n\n===============\n\n");
        printf("%s建立连接\n",address_content);
        return;
    }
    if(tcp_http_connection->nids_state==NIDS_CLOSE)
    {
        //printf("分析http响应数据包\n");
        /* hash=hash_key(tcp_http_connection->addr);
         printf("hash=%d\n",hash);*/
        /* hash_node *p=http_hashList[hash].first;//p用来遍历hash_node
         if(p==NULL)
             printf("p为空");*/
        printf("--------------\n");
        printf("%s连接正常关闭\n",address_content);
        delete_hash_node(http_hashList,tcp_http_connection->addr);
        return;
    }
    if(tcp_http_connection->nids_state==NIDS_RESET)
    {
        printf("--------------\n");
        printf("%s连接被reset关闭\n",address_content);
        return;
    }
    if(tcp_http_connection->nids_state==NIDS_DATA)
    {
        struct half_stream *hlf;
        if(tcp_http_connection->client.count_new)//浏览器接收数据
        {

            // printf("封堵\n");
            printf("浏览器接收数据\n");
            en_queue(dq,tcp_http_connection);//数据进队列
            ////1-2到时候需要写到analysis线程中
            ////1
            de_queue(dq,tcp_http_connection);
            hash=hash_key(tcp_http_connection->addr);
            printf("hash1=%d\n",hash);
            hash_count[hash].count++;
            if(hash_count[hash].count==1)
            {
                insert_hash(*tcp_http_connection,http_hashList);
            }
            parse_client_data(tcp_http_connection);//分析web服务器接收的数据/////////////////////////改
            ////2
        }
        else{
            hash=hash_key(tcp_http_connection->addr);
            hlf=&(tcp_http_connection->server);//hlf表示服务端的连接端
            strcpy(address_content,inet_ntoa(*((
                    struct in_addr *) &(ip_and_port.saddr))));
            sprintf(address_content+strlen(address_content),":%i",ip_and_port.source);
            strcat(address_content,"---->");
            strcat(address_content,inet_ntoa(*((
                    struct in_addr *) & (ip_and_port.daddr))));
            sprintf(address_content+strlen(address_content),":%i",ip_and_port.dest);
            strcat(address_content,"\n");
            printf("\n");
            printf("%s",address_content);
            printf("服务端接收数据...\n");
            printf("\n");
            memcpy(content,hlf->data,hlf->count_new);
            content[hlf->count_new]='\0';
            parse_server_data(content,hlf->count_new,tcp_http_connection);//分析web服务器接收的数据
        }
    }
    return;
}
int main()
{
    printf("input ip num:");
    scanf("%d",&ip_num);
    //printf("%d\n",n);
    printf("input ip model:");
    for(int i=0;i<ip_num;i++)
    {
        scanf("%s",ip_model[i]);
    }
    for(int i=0;i<ip_num;i++)
    {
        printf("%s\n",ip_model[i]);
    }
    int i;
    int p;
    int url_num;
    printf("网络内容关键字模式串个数：");
    scanf("%d",&p);
    pattern=(char **)malloc(sizeof(char)*256);
    printf("输入%d个网络内容关键字模式串\n",p);
    for(i=0;i<p;i++)
    {
        pattern[i]=(char *)malloc(sizeof(char)*256);
        scanf("%s",pattern[i]);
    }
    //creat ac tree
    root=Create_acTrie(pattern,p);
    //creat failed pointer
    Create_failPoint(root);
    printf("url模式串个数：");
    scanf("%d",&url_num);
    url_pattern=(char **)malloc(sizeof(char)*256);
    printf("输入%d个url模式串\n",url_num);
    for(i=0;i<url_num;i++)
    {
        url_pattern[i]=(char *)malloc(sizeof(char)*256);
        scanf("%s",url_pattern[i]);
    }
    url_root=Create_acTrie(url_pattern,url_num);
    Create_failPoint(url_root);
    init_hashlist(http_hashList);//初始化哈希表
    dq=(data_queue *)malloc(sizeof(data_queue));
    init_queue(dq); //初始化http队列
    struct nids_chksum_ctl temp;
    temp.netaddr = 0;
    temp.mask = 0;
    temp.action = 1;
    nids_register_chksum_ctl(&temp,1);
    if(!nids_init())        //libnids初始化
    {
        printf("出现错误：%s\n",nids_errbuf);
        exit(1);
    }
    nids_register_tcp(http_protocol_callback);      //注册回调函数
    nids_run();
    Release_acTrie(root);
    return 0;
}

