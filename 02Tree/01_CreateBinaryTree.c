#include<stdio.h>
#include<stdlib.h>

typedef struct tree
{
    struct tree *pLeft;
    struct tree *pRight;
    int value;

}BinaryTree;

//创建二叉树
BinaryTree* CreaBinaryTree()
{
    //创建根节点
    BinaryTree *pRoot=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->value=1;

    //根的左
    pRoot->pLeft=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->pLeft->value=2;

    //左的左
    pRoot->pLeft->pLeft=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->pLeft->pLeft->value=4;
    pRoot->pLeft->pLeft->pLeft=NULL;
    pRoot->pLeft->pLeft->pRight=NULL;

    //左的右

    pRoot->pLeft->pRight=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->pLeft->pRight->value=5;
    pRoot->pLeft->pRight->pLeft=NULL;
    pRoot->pLeft->pRight->pRight=NULL;

    //根的右
    pRoot->pRight=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->pRight->value=3;
    pRoot->pRight->pLeft=NULL;
    pRoot->pRight->pRight=NULL;

    return pRoot;
}

//前序遍历
void PreorderTraversal(BinaryTree *pTree)
{
    if(pTree==NULL)return;
    //根
    printf("%d   ",pTree->value);//前序

    //左
    PreorderTraversal(pTree->pLeft);
    //右
    PreorderTraversal(pTree->pRight);

}

//中序遍历
void InorderTraverval(BinaryTree *pTree)
{
    if(pTree == NULL)return;

    //左
    InorderTraverval(pTree->pLeft);
    //根
    printf("%d   ",pTree->value);//中序
    //右
    InorderTraverval(pTree->pRight);

}

//后序遍历
void LastorderTraversal(BinaryTree *pTree)
{
    if(pTree==NULL)return;

    //左
    LastorderTraversal(pTree->pLeft);

    //右
    LastorderTraversal(pTree->pRight);

    //根
    printf("%d   ",pTree->value);//后序

}

//创建树
void CreateBiTree(BinaryTree **pTree)
{
    if(pTree == NULL)return;
    int nNum;
    scanf("%d",&nNum);
    if(nNum == 0)return;

    //根
    *pTree=(BinaryTree*)malloc(sizeof(BinaryTree));
    (*pTree)->value = nNum;
    (*pTree)->pLeft = NULL;
    (*pTree)->pRight = NULL;

    //左子树
    CreateBiTree(&((*pTree)->pLeft));

    //右子树
    CreateBiTree(&((*pTree)->pRight));
}

//数组的方式创建完全二叉树
BinaryTree *ArrtoTree(int arr[],int len)
{
    if(arr == NULL || len <= 0)return NULL;

    //申请结构体数组
    BinaryTree* pTree = NULL;
    pTree = (BinaryTree*)malloc((sizeof(BinaryTree))*len);

    //赋值
    int i;
    for(i=0; i<len ;i++)
    {
        pTree[i].value = arr[i];
        pTree[i].pLeft = NULL;
        pTree[i].pRight = NULL;
    }

    for(i=0;i <= (len/2)-1;i++)
    {
        if(i*2+1 <= len-1)
        {
            pTree[i].pLeft = &pTree[i*2+1];
        }
        if((i*2+2) <= len-1)
        {
            pTree[i].pRight = &pTree[i*2+2];

        }
    }
    return pTree;
}

typedef struct LIST
{
    BinaryTree *value;
    struct LIST*pNext;

}List;

typedef struct STACK
{
    int count;
    List *pTop;

}Stack;

void init(Stack**stack)
{
    *stack=(Stack *)malloc(sizeof(Stack));
    (*stack)->count=0;
    (*stack)->pTop=NULL;

}

void push(Stack*stack,BinaryTree *num)
{
    if(stack==NULL)
    {
        printf("此栈不存在\n");
        exit(1);
    }
    List *pnode=(List *)malloc(sizeof(List));
    pnode->value=num;
    pnode->pNext=stack->pTop;
    stack->pTop=pnode;
    (stack->count)++;

}
BinaryTree *pop(Stack*stack)
{
    if(stack==NULL)
    {
        printf("此栈不存在\n");
        return NULL;
        //return -1;
    }
    if(stack->pTop==NULL)
    {
        printf("此栈为空\n");
        return NULL;
        //return -1;
    }

    List *pDel=stack->pTop;
    BinaryTree *num=pDel->value;
    stack->pTop=stack->pTop->pNext;
    free(pDel);
    pDel=NULL;
    (stack->count)--;

    return num;

}
void clear(Stack *stack)
{
    while(stack->count>0)
    {
        pop(stack);
    }
}
void Destory(Stack**stack)
{
    clear(*stack);
    free(*stack);
    *stack=NULL;
}
void UnRelPreorderTraversal(BinaryTree*tree)
    //非递归前序打印
{
    if(tree==NULL)
    {
        return;
    }
    Stack *stack=NULL;
    init(&stack);

    while(1)
    {
        while(tree)
        {

            printf("%d   ",tree->value);
            push(stack,tree);
            tree=tree->pLeft;

        }

        tree=pop(stack);
        if(tree==NULL)
        {
            break;
        }
        tree=tree->pRight;
    }
    printf("\n");
}

void UnRelInorderTraverval(BinaryTree*tree)

    //非递归中序打印
{
    if(tree==NULL)
    {
        return;
    }
    Stack *stack=NULL;
    init(&stack);

    while(1)
    {
        while(tree)
        {
            push(stack,tree);
            tree=tree->pLeft;
        }

        tree=pop(stack);
        if(tree==NULL)
        {
            break;
        }
        printf("%d   ",tree->value);
        tree=tree->pRight;
    }

    printf("\n");
}
void UnRelLastorderTraversal(BinaryTree*tree)
{
    if(tree==NULL)
    {
        return;
    }
    Stack*stack=NULL;
    init(&stack);
    BinaryTree*pMark=NULL;

    while(1)
    {
        while(tree)
        {
            push(stack,tree);
            tree=tree->pLeft;
        }

        if(stack->count==0)
        {

            return;
        }

        if((stack->pTop)->value->pRight==NULL||pMark==(stack->pTop)->value->pRight)
        {
            pMark=pop(stack);
            printf("%d   ",pMark->value);
        }

        else
        {
            tree=stack->pTop->value->pRight;
        }
    }

    printf("\n");
}

int main()
{
   // BinaryTree *pTree = CreaBinaryTree();

    BinaryTree *pTree = NULL;
    //CreateBiTree(&pTree);
    int arr[]={1,2,3,4,5};
    pTree = ArrtoTree(arr,sizeof(arr)/sizeof(arr[0]));
    PreorderTraversal(pTree);
    printf("\n");

    InorderTraverval(pTree);
    printf("\n");

    LastorderTraversal(pTree);
    printf("\n");

   // UnRelPreorderTraversal(tree);
   // UnRelInorderTraverval(tree);
   // UnRelLastorderTraversal(tree);
    return 0;
}

