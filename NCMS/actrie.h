//
// Created by root on 20-4-26.
//

#ifndef IPTEST_ACTRIE_H
#define IPTEST_ACTRIE_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"change.h"

//定义Trie树节点
typedef struct TreeNode
{
    struct TreeNode* par;      		/* 父节点 */
    struct TreeNode* fail;    	/* 失败结点 */
    int patternNo;     		/* 关键字的编号，仅在结束结点中保存编号 */
    int patternTag;         /*是否为可接受态*/
    struct TreeEdge* Edge;		/* 出边数组 */
    unsigned short EdgeNum;  		/* 出边数目 */
    unsigned short EdgeSize;  		/* 最大动态分配的大小 */
} TreeNode;

//定义边
typedef struct TreeEdge
{
    char alpha;
    TreeNode* next;
} TreeEdge;

//定义节点
typedef struct node
{
    TreeNode* data;
    struct node* next;
} node;

//定义队列
typedef struct queue
{
    node* front;//队头指针
    node* rear;//队尾指针
} queue;

//创建ac自动机trie树
TreeNode* Create_acTrie(char** pattern, int patterns_num);

//创建失败指针
int Create_failPoint(TreeNode* root);

//AC自动机匹配  返回值为0匹配失败，不为0时，返回值为关键字标号；
int Search_acTrie(TreeNode* root, TreeNode** state_node, char* text, int text_len, char** pattern);

//释放内存
int Release_acTrie(TreeNode* root);

//在结点下查找给定字符的下一结点
TreeNode* Find_nextNode(TreeNode* pAc_node, char ch);
#endif //IPTEST_ACTRIE_H
