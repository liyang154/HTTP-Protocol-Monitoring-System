//
// Created by root on 20-4-26.
//
#include"actrie.h"

//初始化队列
queue* InitQueue()
{
    queue* que = (queue*)malloc(sizeof(queue));
    que->front = NULL;
    que->rear = NULL;
    return que;
}

//查看队列是否为空
int EmptyQueue(queue* que)
{
    return que->front == NULL;
}


// 入队操作
void InsertQueue(queue* que, TreeNode* t_node)
{
    node* n = (node*)malloc(sizeof(node));
    if (n == NULL)//内存分配失败
        return;
    n->data = t_node;
    n->next = NULL;//尾插法，插入元素指向空
    if (que->rear == NULL)
    {
        que->front = n;
        que->rear = n;
    }
    else
    {
        que->rear->next = n;//让n成为当前的尾部节点下一节点
        que->rear = n;//尾部指针指向n
    }
}

//出队操作
void DeleteQueue(queue* que)
{
    node* n = que->front;
    if (que->front == NULL)//判断队列是否为空
        return;
    if (que->front == que->rear)
    { //是否只有一个元素
        que->front = NULL;
        que->rear = NULL;
    }
    else
    {
        que->front = que->front->next;
        free(n);
    }
}

//创建AC自动机节点
TreeNode* Create_Node()
{
    TreeNode* pAC_Node = (TreeNode*)malloc(sizeof(TreeNode));
    memset(pAC_Node, 0, sizeof(TreeNode));
    pAC_Node->fail = NULL;
    pAC_Node->par = NULL;
    pAC_Node->EdgeSize = 2;
    pAC_Node->Edge = (struct TreeEdge*) malloc(pAC_Node->EdgeSize * sizeof(struct TreeEdge));
    return pAC_Node;
}

//创建边
void Add_Edge(TreeNode* thiz, TreeNode* next, char alpha)
{
    if (thiz->EdgeNum >= thiz->EdgeSize)
    {
        thiz->EdgeSize += 2;
        thiz->Edge = (struct TreeEdge*)realloc(thiz->Edge, thiz->EdgeSize * sizeof(struct TreeEdge));
    }
    thiz->Edge[thiz->EdgeNum].alpha = alpha;
    thiz->Edge[thiz->EdgeNum++].next = next;
}

//在结点下查找给定字符的下一结点
TreeNode* Find_nextNode(TreeNode* pAc_node, char ch)
{
    int i = 0;
    if (NULL == pAc_node)
    {
        return NULL;
    }
    for (i = 0; i < pAc_node->EdgeNum; i++)
    {
        if (pAc_node->Edge[i].alpha == ch)
            return (pAc_node->Edge[i].next);
    }
    return NULL;
}

//在输入的结点下创建边和下一结点
TreeNode* Create_nextNode(TreeNode* pCur_node, char alpha)
{
    TreeNode* pNext_node = NULL;
    pNext_node = Find_nextNode(pCur_node, alpha);
    if (pNext_node)
    {
        return NULL;
    }
    pNext_node = Create_Node();
    Add_Edge(pCur_node, pNext_node, alpha);
    return pNext_node;
}

//创建ac自动机trie树
TreeNode* Create_acTrie(char** pattern, int patterns_num)
{
    int iPattern_index, iChar_index;
    TreeNode* root = Create_Node();
    TreeNode* pCur_node = NULL, * pNext_node = NULL;
    char alpha;
    for (iPattern_index = 0; iPattern_index < patterns_num; iPattern_index++)
    {

        //gb2312编码
        pCur_node = root;
        char* gb2312_inbuf = (char*)malloc(sizeof(char) * 256);
        strcpy(gb2312_inbuf, pattern[iPattern_index]);
        gb2312_inbuf[strlen(gb2312_inbuf)] = '\0';
        size_t gb2312_inlen = strlen(gb2312_inbuf);
        char* gb2312_outbuf = (char*)malloc(sizeof(char) * 256);//存放转换后的字符串
        size_t gb2312_outlen = 256;
        int n0 = UTF8_to_GB2312(gb2312_inbuf, &gb2312_inlen, gb2312_outbuf, &gb2312_outlen);
        if (n0 == 1)
        {
            for (iChar_index = 0; iChar_index < (256 - gb2312_outlen); iChar_index++)
            {
                alpha = gb2312_outbuf[iChar_index];
                pNext_node = Find_nextNode(pCur_node, alpha);
                if (NULL != pNext_node)
                {
                    pCur_node = pNext_node;
                }
                else
                {
                    pNext_node = Create_nextNode(pCur_node, alpha);
                    if (NULL != pNext_node)
                    {
                        pNext_node->par = pCur_node;
                        pCur_node = pNext_node;
                    }
                }
            }
        }
        pCur_node->patternNo = iPattern_index + 1;
        pCur_node->patternTag = 1;
        free(gb2312_inbuf);
        free(gb2312_outbuf);

        //gbk编码
        pCur_node = root;
        char* gbk_inbuf = (char*)malloc(sizeof(char) * 256);
        strcpy(gbk_inbuf, pattern[iPattern_index]);
        gbk_inbuf[strlen(gbk_inbuf)] = '\0';
        size_t gbk_inlen = strlen(gbk_inbuf);
        char* gbk_outbuf = (char*)malloc(sizeof(char) * 256);//存放转换后的字符串
        size_t gbk_outlen = 256;
        int n1 = UTF8_to_GBK(gbk_inbuf, &gbk_inlen, gbk_outbuf, &gbk_outlen);
        if (n1 == 1)
        {
            for (iChar_index = 0; iChar_index < (256 - gbk_outlen); iChar_index++)
            {
                alpha = gbk_outbuf[iChar_index];
                pNext_node = Find_nextNode(pCur_node, alpha);
                if (NULL != pNext_node)
                {
                    pCur_node = pNext_node;
                }
                else
                {
                    pNext_node = Create_nextNode(pCur_node, alpha);
                    if (NULL != pNext_node)
                    {
                        pNext_node->par = pCur_node;
                        pCur_node = pNext_node;
                    }
                }
            }
        }
        pCur_node->patternNo = iPattern_index + 1;
        pCur_node->patternTag = 1;
        free(gbk_inbuf);
        free(gbk_outbuf);

        //UNICODE编码
        pCur_node = root;
        char* UNICODE_inbuf = (char*)malloc(sizeof(char) * 256);
        strcpy(UNICODE_inbuf, pattern[iPattern_index]);
        UNICODE_inbuf[strlen(UNICODE_inbuf)] = '\0';
        size_t UNICODE_inlen = strlen(UNICODE_inbuf);
        char* UNICODE_outbuf = (char*)malloc(sizeof(char) * 256);//存放转换后的字符串
        size_t UNICODE_outlen = 256;
        int n2 = UTF8_to_UNICODE(UNICODE_inbuf, &UNICODE_inlen, UNICODE_outbuf, &UNICODE_outlen);
        if (n2 == 1)
        {
            for (iChar_index = 0; iChar_index < (256 - UNICODE_outlen); iChar_index++)
            {
                alpha = UNICODE_outbuf[iChar_index];
                pNext_node = Find_nextNode(pCur_node, alpha);
                if(NULL != pNext_node)
                {
                    pCur_node = pNext_node;
                }
                else
                {
                    pNext_node = Create_nextNode(pCur_node, alpha);
                    if(NULL != pNext_node)
                    {
                        pNext_node->par = pCur_node;
                        pCur_node = pNext_node;
                    }
                }
            }
        }
        pCur_node->patternNo = iPattern_index + 1;
        pCur_node->patternTag = 1;
        free(UNICODE_inbuf);
        free(UNICODE_outbuf);

        //URL编码
        pCur_node = root;
        char* URL_inbuf = (char*)malloc(sizeof(char) * 256);
        strcpy(URL_inbuf, pattern[iPattern_index]);
        URL_inbuf[strlen(URL_inbuf)] = '\0';
        UTF8_to_URL(URL_inbuf);
        for (iChar_index = 0; iChar_index < (strlen(URL_inbuf)); iChar_index++)
        {
            alpha = URL_inbuf[iChar_index];
            pNext_node = Find_nextNode(pCur_node, alpha);
            if (NULL != pNext_node)
            {
                pCur_node = pNext_node;
            }
            else
            {
                pNext_node = Create_nextNode(pCur_node, alpha);
                if (NULL != pNext_node)
                {
                    pNext_node->par = pCur_node;
                    pCur_node = pNext_node;
                }
            }
        }
        pCur_node->patternNo = iPattern_index + 1;
        pCur_node->patternTag = 1;
        free(URL_inbuf);

        //utf-8编码
        pCur_node = root;
        for (iChar_index = 0; iChar_index < (strlen(pattern[iPattern_index])); iChar_index++)
        {
            alpha = pattern[iPattern_index][iChar_index];
            pNext_node = Find_nextNode(pCur_node, alpha);
            if (NULL != pNext_node)
            {
                pCur_node = pNext_node;
            }
            else
            {
                pNext_node = Create_nextNode(pCur_node, alpha);
                if (NULL != pNext_node)
                {
                    pNext_node->par = pCur_node;
                    pCur_node = pNext_node;
                }
            }
        }
        pCur_node->patternNo = iPattern_index + 1;
        pCur_node->patternTag = 1;
    }
    return root;
}

//查找失败指针
void Search_failPoint(TreeNode* pCur_node, TreeNode* parent, TreeNode* root, char edge_ch)
{
    TreeNode* pNext_node;
    int i = 0;
    for (i = 0; i < parent->EdgeNum; i++)
    {
        if (edge_ch == parent->Edge[i].alpha)
            break;
    }
    if (i < parent->EdgeNum)
    {
        pCur_node->fail = parent->Edge[i].next;
        return;
    }
    //在父节点的失败结点中查找字母，否则递归遍历父节点
    pNext_node = Find_nextNode(parent->fail, edge_ch);
    if (NULL == pNext_node)
    {
        if (parent->fail == root)
        {
            pCur_node->fail = root;
        }
        else
        {
            parent = parent->fail;
            Search_failPoint(pCur_node, parent, root, edge_ch);
        }
    }
    else
    {
        pCur_node->fail = pNext_node;
    }
    return;
}

//把结点的所有子节点入队
int  Node_toQueue(TreeNode* parent, queue* que)
{
    int i;
    for (i = 0; i < parent->EdgeNum; i++)
    {
        InsertQueue(que, parent->Edge[i].next);
    }
    return 0;
}

//找失败指针
int Create_failPoint(TreeNode* root)
{
    int i = 0;
    queue* q = InitQueue();
    char edge_ch = '\0';
    TreeNode* pCur_node = NULL, * parent = NULL, * pNext_node = NULL;
    for (i = 0; i < root->EdgeNum; i++)
    {
        root->Edge[i].next->fail = root;
    }
    root->fail = root;
    Node_toQueue(root, q);
    while (!EmptyQueue(q))
    {
        parent = q->front->data;
        DeleteQueue(q);
        Node_toQueue(parent, q);
        for (i = 0; i < parent->EdgeNum; i++)
        {
            edge_ch = parent->Edge[i].alpha;
            pCur_node = parent->Edge[i].next;
            //在父节点的失败结点下的边中查找字母
            pNext_node = Find_nextNode(parent->fail, edge_ch);
            if (NULL == pNext_node)
            {
                if (parent->fail == root)
                {
                    pCur_node->fail = root;
                }
                else
                {
                    //递归不断找含字母的边
                    Search_failPoint(pCur_node, parent->fail, root, edge_ch);
                }
            }
            else
            {
                pCur_node->fail = pNext_node;
            }
            if (pCur_node->fail->patternNo != 0)
            {
                pCur_node->patternNo = pCur_node->fail->patternNo;
            }
        }
    }
    free(q);
    return 0;
}

//AC自动机匹配
int Search_acTrie(TreeNode* root, TreeNode** state_node, char* text, int text_len, char** pattern)
{
    TreeNode* pCur_node = root;
    if ((*state_node) != NULL)
    {
        pCur_node = *state_node;
    }
    TreeNode* pNext_node = NULL;
    int position = 0;
    while (position < text_len)
    {
        pNext_node = Find_nextNode(pCur_node, text[position]);
        if (NULL == pNext_node)
        {
            if (pCur_node == root)
            {
                position++;
            }
            else
            {
                pCur_node = pCur_node->fail;
                if (pCur_node->patternTag == 1)
                {
                    printf("匹配成功：\t\t模式串序号为：%d\t\t模式串内容：%s\n", pCur_node->patternNo, pattern[pCur_node->patternNo - 1]);
                    return pCur_node->patternNo;
                }
            }
        }
        else
        {
            pCur_node = pNext_node;
            if (pCur_node->patternTag == 1)
            {
                printf("匹配成功：\t\t模式串序号为：%d\t\t模式串内容：%s\n", pCur_node->patternNo, pattern[pCur_node->patternNo - 1]);
                return pCur_node->patternNo;
            }
            position++;
        }
    }
    *state_node = pCur_node;
    while (pCur_node != root)
    {
        pCur_node = pCur_node->fail;
        if (pCur_node->patternTag == 1)
        {
            printf("匹配成功：\t\t模式串序号为：%d\t\t模式串内容：%s\n", pCur_node->patternNo, pattern[pCur_node->patternNo - 1]);
            return pCur_node->patternNo;
        }
    }
    return 0;
}

//释放内存
int Release_acTrie(TreeNode* root)
{
    if (root == NULL)
    {
        return 0;
    }
    int i;
    queue* q;
    TreeNode* pCur_node = NULL;
    q = InitQueue();
    InsertQueue(q, root);
    root = NULL;
    while (!EmptyQueue(q))
    {
        pCur_node = q->front->data;
        DeleteQueue(q);
        for (i = 0; i < pCur_node->EdgeNum; i++)
        {
            InsertQueue(q, pCur_node->Edge[i].next);
        }
        free(pCur_node->Edge);
        free(pCur_node);
    }
    free(q);
    return 0;
}

/*
int main()
{
	int i, p, q;
	//int* p = (int*)malloc(sizeof(int));
	char** pattern = (char**)malloc(sizeof(char) * 256);
	char** text = (char**)malloc(sizeof(char) * 256);
	TreeNode** state_node = (TreeNode**)malloc(sizeof(TreeNode));
	*state_node = NULL;
	printf("模式串个数:\n");
	scanf("%d", &p);
	printf("待匹配字符串个数:\n");
	scanf("%d", &q);
	//printf("%d", q);
	//char text[10][101];
	printf("待匹配字符串:\n");
	for (i = 0; i < q; i++)
	{
		text[i] = (char*)malloc(sizeof(char) * 256);
		scanf("%s", text[i]);
	}
	printf("\n模式串:\n");
	for (i = 0; i < p; i++)
	{
		pattern[i] = (char*)malloc(sizeof(char) * 256);
		scanf("%s", pattern[i]);
	}
	TreeNode* root = Create_acTrie(pattern, p);   ///建立Trie树
	Create_failPoint(root); ///添加失败转移
	printf("匹配结果如下：\n 位置\t编号\t模式\n");
	for (i = 0; i < q; i++)
	{
		Search_acTried(root, state_node, text[i], strlen(text[i]), pattern);
	}
	Release_acTrie(root);  ///释放动态申请内存
	return 0;
}
*/
