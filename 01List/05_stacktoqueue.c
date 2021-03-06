#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int nValue;
    struct node *pNext;
}MyStack;

typedef struct stack
{
    int nCount;
    MyStack *pTop;
}Stack;

//初始化函数
void s_Init(Stack **pStack)
{
    *pStack = (Stack*)malloc(sizeof(Stack));
    (*pStack)->nCount = 0;   
    (*pStack)->pTop = NULL;
}

//插入   
void s_Push(Stack *pStack,int nNum)
{
    if(pStack == NULL)
    {
        printf("栈不存在\n");
        exit(1);
    }

    MyStack *pTemp = NULL;
    pTemp = (MyStack*)malloc(sizeof(MyStack));
    pTemp->nValue = nNum;
    pTemp->pNext = pStack->pTop;
    pStack->pTop = pTemp;

    pStack->nCount++;
}

//弹出
int s_Pop(Stack *pStack)
{
    if(pStack == NULL)
    {
        printf("栈不存在\n");
        exit(1);
    }
    
    if(pStack->pTop == NULL)return-1;

    MyStack *pDel = pStack->pTop;
    int nNum = pDel->nValue;

    pStack->pTop = pStack->pTop->pNext;
    free(pDel);
    pDel = NULL;

    pStack->nCount--;
    return nNum;
}

//清空
void s_Clear(Stack *pStack)
{
    if(pStack == NULL)
    {
        printf("栈不存在\n");
        exit(1);
    }
    
    while(pStack->nCount != 0)
    {
        s_Pop(pStack);
    }
}

//销毁
void s_Destroy(Stack **pStack)
{
    s_Clear(*pStack);
    free(*pStack);
    *pStack = NULL;

}

//获取栈元素个数
int s_GetCount(Stack *pStack)
{
    if(pStack == NULL)
    {
        printf("栈不存在\n");
        exit(1);
    }
    return pStack->nCount;
}

//获得栈顶
MyStack *s_GetTop(Stack *pStack)
{
    if(pStack == NULL)
    {
        printf("栈不存在\n");
        exit(1);
    }

    return pStack->pTop;
}

//判断是否为空
int s_IsEmpty(Stack *pStack)
{
    if(pStack == NULL)
    {
        printf("栈不存在\n");
        exit(1);
    }

    return pStack->nCount = 0?1:0;
}

typedef struct queue
{
    int nCount;
    Stack *pStack1;
    Stack *pStack2;
}Queue;

void q_Init(Queue **pQueue)
{
    *pQueue = (Queue*)malloc(sizeof(Queue));
    (*pQueue)->nCount = 0;

    s_Init(&((*pQueue)->pStack1));
    s_Init(&((*pQueue)->pStack2));
}

void q_Push(Queue *pQueue,int nNum)
{
    if(pQueue == NULL || pQueue->pStack1 == NULL || pQueue->pStack2 == NULL )exit(1);

    //栈1入栈
    //栈2非空，将元素放回栈1
    while(pQueue->pStack2->nCount != 0)
    {
        s_Push(pQueue->pStack1,s_Pop(pQueue->pStack2));
    }

    //新元素入栈
    s_Push(pQueue->pStack1,nNum);
    pQueue->nCount++;
}

int q_Pop(Queue *pQueue)
{
    if(pQueue == NULL || pQueue->pStack1 == NULL || pQueue->pStack2 == NULL )exit(1);

    //栈2出队
    //栈1非空，将元素放回栈2
    while(pQueue->pStack1->nCount != 0)
    {
        s_Push(pQueue->pStack2,s_Pop(pQueue->pStack1));
    }

    //新元素入栈
    int nNum = s_Pop(pQueue->pStack2);
    pQueue->nCount--;
    return nNum;
}


int main()
{
   Queue *pQueue = NULL;
   q_Init(&pQueue);
   q_Push(pQueue,1); 
   q_Push(pQueue,2); 
   q_Push(pQueue,3); 
   q_Push(pQueue,4);
   
   printf("%d\n",q_Pop(pQueue));
   printf("%d\n",q_Pop(pQueue));
   printf("%d\n",q_Pop(pQueue));
   printf("%d\n",q_Pop(pQueue));
   return 0;
}
