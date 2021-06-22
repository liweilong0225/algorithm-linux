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
void s_Push(Stack *pStack,BinaryTree* nNum)
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
BinaryTree* s_Pop(Stack *pStack)
{
    if(pStack == NULL)
    {
        printf("栈不存在\n");
        exit(1);
    }

    if(pStack->pTop == NULL)return NULL;

    MyStack *pDel = pStack->pTop;
    BinaryTree* nNum = pDel->nValue;

    pStack->pTop = pStack->pTop->pNext;
    free(pDel);
    pDel = NULL;

    pStack->nCount--;
    return nNum;
}

//非递归前序打印
void UnRelPreorderTraversal(BinaryTree* pTree)
{
    if(pTree == NULL)return;
    //栈
    Stack *pStack = NULL;
    s_Init(&pStack);

    while(1)
    {
        while(pTree)
        {
            //打印
            printf("%d   ",pTree->value);
            //保存
            s_Push(pStack,pTree);
            //向左走
            pTree = pTree->pLift;

        }
        //弹出
        pTree = s_Pop(pStack);
        if(pTree==NULL) break;
        //右侧
        pTree = pTree->pRight;
    }
    printf("\n");
}

//非递归中序打印
void UnRelInorderTraversal(BinaryTree *pTree)
{
    if(pTree==NULL)return;
    //栈
    Stack *pStack=NULL;
    s_Init(&pStack);

    while(1)
    {
        while(pTree)
        {
            //保存
            s_Push(pStack,pTree);
            //向左走
            pTree=pTree->pLift;
        }
        //弹出
        pTree = s_Pop(pStack);
        //空栈
        if(pTree == NULL)break; 
        //打印
        printf("%d   ",pTree->value);
        //右侧
        pTree=pTree->pRight;
    }
    printf("\n");
}

//非递归后序打印
void UnRelLastorderTraversal(BinaryTree* pTree)
{
    if(pTree == NULL) return;
    Stack* pStack = NULL;
    s_Init(&pStack);
    BinaryTree* pMark = NULL;
    while(1)
    {
        while(pTree)
        {
            //保存
            s_Push(pStack,pTree);
            //向左走
            pTree = pTree->pLift;
        }
        //栈空则结束
        if(pStack->nCount == 0)break;
        
        //栈顶元素的右
        if(pStack->pTop->nValue->pRight == NULL || pMark == pStack->pTop->nValue->pRight)
        {
            //弹出，标记，打印
            pMark = s_Pop(pStack);
            printf("%d   ",pMark->value);
        }
        else
        {
            //右
            pTree = pStack->pTop->nValue->pRight;
        }
    }
    printf("\n");
}

int main()
{
    BinaryTree *pTree = CreateBinaryTree();
    UnRelPreorderTraversal(pTree);
    UnRelInorderTraversal(pTree);
    UnRelLastorderTraversal(pTree);

    return 0;
}

