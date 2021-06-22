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


int main()
{
   Stack *pStack = NULL;
   s_Init(&pStack);
   s_Push(pStack,1); 
   s_Push(pStack,2); 
   s_Push(pStack,3); 
   s_Push(pStack,4);
   
   printf("%d\n",s_Pop(pStack));
   printf("%d\n",s_Pop(pStack));
   printf("%d\n",s_Pop(pStack));
   printf("%d\n",s_Pop(pStack));

   s_Destroy(&pStack);

   s_Push(pStack,2);

   return 0;
}
