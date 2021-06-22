#include<stdio.h>
#include<stdlib.h>

typedef struct list
{
    int nValue;
    struct list *pNext;
}List;

List *CreateList()
{
    int nCount; //节点个数
    int nNum;//节点的值

    List *pHead = NULL;
    List *pTail = NULL;

    List *pTemp = NULL;

    printf("请输入节点个数:\n");
    scanf("%d",&nCount);

    while(nCount != 0)
    {
        printf("输入数值:\n");
        scanf("%d",&nNum);

        pTemp = (List*)malloc(sizeof(List));
        pTemp->nValue = nNum;
        pTemp->pNext = NULL;

        //尾添加
        if(pHead == NULL)
        {
            pHead = pTemp;
        }
        else
        {
            pTail->pNext = pTemp;
        }
        pTail = pTemp;

        nCount--;
    }

    return pHead;
}

void Print(List *pHead)
{
    if(pHead == NULL)return;

    while(pHead)
    {
        printf("%d ",pHead->nValue);
        pHead = pHead->pNext;
    }

    printf("\n");
}
//倒序打印
void RePrint(List *pHead)
{
    if(pHead == NULL)return;

    //处理下一个
    RePrint(pHead->pNext);

    //打印
    printf("%d ",pHead->nValue);
}

//倒置打印
List *Reverse(List *pHead)
{
    if(pHead == NULL || pHead->pNext == NULL)return pHead;

    List *p1 = NULL;
    List *p2 = pHead;//指向
    List *p3 = pHead->pNext;//断开位置

    while(p3 != NULL)
    {
        //连接
        p2->pNext = p1;
        //指针移动
        p1 = p2;
        p2 = p3;
        p3 = p3->pNext;
    }

    p2->pNext = p1;

    return p2;
}

int main()
{
    List *pHead = CreateList();
    Print(pHead);
    RePrint(pHead);
    printf("\n");
    pHead = Reverse(pHead);
    Print(pHead);
    return 0;

}
