#include<stdio.h>
#include<stdlib.h>

typedef struct tree
{
    struct tree *pLift;
    struct tree *pRight;
    int value;

}BinaryTree;

//创建二叉树
BinaryTree* CreateBinaryTree()
{
    //创建根节点
    BinaryTree *pRoot=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->value=1;

    //根的左
    pRoot->pLift=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->pLift->value=2;

    //左的左
    pRoot->pLift->pLift=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->pLift->pLift->value=4;
    pRoot->pLift->pLift->pLift=NULL;
    pRoot->pLift->pLift->pRight=NULL;

    //左的右

    pRoot->pLift->pRight=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->pLift->pRight->value=5;
    pRoot->pLift->pRight->pLift=NULL;
    pRoot->pLift->pRight->pRight=NULL;

    //根的右
    pRoot->pRight=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->pRight->value=3;
    pRoot->pRight->pLift=NULL;
    pRoot->pRight->pRight=NULL;

    return pRoot;
}

typedef struct node
{
    BinaryTree* nValue;
    struct node *pNext;
}MyQueue;

typedef struct queue
{
    int nCount;
    MyQueue *pHead;
    MyQueue *pTail;
}Queue;

void q_Init(Queue **pQueue)
{
    *pQueue = (Queue*)malloc(sizeof(Queue));
    (*pQueue)->nCount = 0;
    (*pQueue)->pHead = NULL;
    (*pQueue)->pTail = NULL;
}

void q_Push(Queue *pQueue,BinaryTree* nNum)
{
    if(pQueue == NULL)
        exit(1);

    MyQueue *pTemp = NULL;
    pTemp = (MyQueue*)malloc(sizeof(MyQueue));
    pTemp->nValue = nNum;
    pTemp->pNext = NULL;

    //尾添加
    if(pQueue->pHead == NULL)
    {
        pQueue->pHead = pTemp;
    }
    else
    {
        pQueue->pTail->pNext = pTemp;
    }
    pQueue->pTail = pTemp;
    pQueue->nCount++;
}

BinaryTree* q_Pop(Queue *pQueue)
{
    if(pQueue == NULL)
    {
        exit(1);
    }

    if(pQueue->nCount == 0)return NULL;

    MyQueue *pDel = pQueue->pHead;
    BinaryTree* nNum = pDel->nValue;

    pQueue->pHead = pQueue->pHead->pNext;
    free(pDel);
    pDel = NULL;
    pQueue->nCount--;

    if(pQueue->nCount == 0)
    {
        pQueue->pTail == NULL;
    }
    return nNum;
}

int q_IsEmpty(Queue *pQueue)
{
    if(pQueue == NULL)
    {
        exit(1);
    }
    return pQueue->nCount == 0?1:0;
}

//层序遍历
void LevelTraversal(BinaryTree* pTree)
{
    if(pTree == NULL)return;

    //辅助队列
    Queue *pQueue = NULL;
    q_Init(&pQueue);
    //根入栈
    q_Push(pQueue,pTree);

    while(!q_IsEmpty(pQueue))
    {
        //弹出
        pTree = q_Pop(pQueue);
        //打印
        printf("%d   ",pTree->value);

        //非空左右入栈
        if(pTree->pLift!=NULL)
        {
           q_Push(pQueue,pTree->pLift);
        }
        if(pTree->pRight!=NULL)
        {
            q_Push(pQueue,pTree->pRight);
        }
    }
    printf("\n");
}

int main()
{
    BinaryTree *pTree = NULL;
    pTree = CreateBinaryTree();
    LevelTraversal(pTree);
    return 0;
}

