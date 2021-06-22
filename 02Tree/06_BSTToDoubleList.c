#include<stdio.h>
#include<stdlib.h>

typedef struct tree
{
    struct tree *pLeft;
    struct tree *pRight;
    int value;
}BST;

void AddNode(BST **pTree,int nNum)
{
    //节点
    BST *pTemp = NULL;
    pTemp = (BST*)malloc(sizeof(BST));
    pTemp->pLeft = NULL;
    pTemp->pRight = NULL;
    pTemp->value = nNum;

    //空树
    if(*pTree == NULL)
    {
        *pTree = pTemp;
        return;
    }
    //非空树
    BST *pNode = *pTree;
    while(pNode)
    {
        if(pNode->value > nNum)
        {
            //左侧
            if(pNode->pLeft == NULL)
            {
                pNode->pLeft = pTemp;
                return;
            }
            pNode = pNode->pLeft;
        }
        else if(pNode->value < nNum)
        {
            //右侧
            if(pNode->pRight == NULL)
            {
                pNode->pRight = pTemp;
                return;
            }
            pNode = pNode->pRight;
        }
        else
        {
            printf("data error!\n");
            free(pTemp);
            pTemp = NULL;
            return;
        }
    }
}

BST* CreateTree(int arr[],int len)
{
    if(arr == NULL || len <=0)return NULL;
    BST *pTree=NULL;
    int i;

    for(i=0;i<len;i++)
    {
        AddNode(&pTree,arr[i]);
    }
    return pTree;
}

//中序遍历
void InorderTraversal(BST *pTree)
{
    if(pTree == NULL)return;

    //左
    InorderTraversal(pTree->pLeft);
    //根
    printf("%d   ",pTree->value);//中序
    //右
    InorderTraversal(pTree->pRight);
}

void BSTToDoubleList(BST *pTree,BST **pHead,BST **pTail)
{
    if(pTree == NULL)return;
    //左
    BSTToDoubleList(pTree->pLeft,pHead,pTail);
    //根，节点添加
    if(*pHead == NULL)
    {
        *pHead = pTree;
    }
    else
    {
        (*pTail)->pRight = pTree;
        pTree->pLeft = *pTail;
    }
    *pTail = pTree;
    //右
    BSTToDoubleList(pTree->pRight,pHead,pTail);
}

void PrintList(BST *pHead)
{

    if(pHead==NULL)return;
    while(pHead!=NULL)
    {
        printf("%d   ",pHead->value);
        pHead=pHead->pRight;
    }
    printf("\n");
}

int main()
{
    BST* pTree=NULL;
    int arr[]={19,2,188,4,17,8,34,5,129};

    pTree = CreateTree(arr,sizeof(arr)/sizeof(arr[0]));
    InorderTraversal(pTree);
    printf("\n");

    BST *pHead = NULL;
    BST *pTail = NULL;
    BSTToDoubleList(pTree,&pHead,&pTail);
    PrintList(pHead);
    return 0;
}
