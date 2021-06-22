#include<stdio.h>
#include<stdlib.h>

typedef struct tree
{
    struct tree *pLeft;
    struct tree *pRight;
    struct tree *pFather;
    int value;

}BinaryTree;

//创建二叉树
BinaryTree* CreateBinaryTree()
{
    //创建根节点
    BinaryTree *pRoot=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->value=1;
    pRoot->pFather = NULL;

    //根的左
    pRoot->pLeft=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->pLeft->value=2;
    pRoot->pLeft->pFather = pRoot;

    //左的左
    pRoot->pLeft->pLeft=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->pLeft->pLeft->value=4;
    pRoot->pLeft->pLeft->pFather = pRoot->pLeft;
    pRoot->pLeft->pLeft->pLeft=NULL;
    pRoot->pLeft->pLeft->pRight=NULL;

    //左的右
    pRoot->pLeft->pRight=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->pLeft->pRight->value=5;
    pRoot->pLeft->pRight->pFather = pRoot->pLeft;
    pRoot->pLeft->pRight->pLeft=NULL;
    pRoot->pLeft->pRight->pRight=NULL;

    //根的右
    pRoot->pRight=(BinaryTree*)malloc(sizeof(BinaryTree));
    pRoot->pRight->value=3;
    pRoot->pRight->pFather = pRoot;
    pRoot->pRight->pLeft=NULL;
    pRoot->pRight->pRight=NULL;

    return pRoot;
}

void PreorderTraversal(BinaryTree *pTree)
{
    if(pTree == NULL)return;
    //根
    printf("%d   ",pTree->value);
    //左
    PreorderTraversal(pTree->pLeft);
    //右
    PreorderTraversal(pTree->pRight);
}

//右旋
void RightRotate(BinaryTree **pTree)
{
    if(*pTree == NULL || (*pTree)->pLeft == NULL)return;
    BinaryTree *pNodeA = *pTree;//A
    BinaryTree *pNodeB = (*pTree)->pLeft;//B

    //三个孩子关系
    //children relation
    pNodeA->pLeft = pNodeB->pRight;//E是A的左
    pNodeB->pRight = pNodeA;//A是B的右
    //检测根是不是为空，B是X的孩子
    if(pNodeA->pFather == NULL)
    {
        *pTree = pNodeB;
    }
    else
    {
        if(pNodeA == pNodeA->pFather->pLeft)
        {
            pNodeA->pFather->pLeft = pNodeB;
        }
        else
        {
            pNodeA->pFather->pRight = pNodeB;
        }
    }
    //三个父亲关系
    if(pNodeA->pLeft != NULL)
    {
        pNodeA->pLeft->pFather = pNodeA;//E的父亲是A
    }
    pNodeB->pFather = pNodeA->pFather;//B的父亲是X
    pNodeA->pFather = pNodeB;//A的父亲是B
}

//左旋
void LeftRotate(BinaryTree **pTree)
{
    if(*pTree == NULL || (*pTree)->pRight == NULL)return;
    BinaryTree *pNodeA = *pTree;//A
    BinaryTree *pNodeB = (*pTree)->pRight;//B

    //三个孩子关系
    pNodeA->pRight = pNodeB->pLeft;//E是A的右
    pNodeB->pLeft = pNodeA;//A是B的左
    //检测根是不是为空，B是X的孩子
    if(pNodeA->pFather == NULL)
    {
        *pTree = pNodeB;
    }
    else
    {
        if(pNodeA == pNodeA->pFather->pLeft)
        {
            pNodeA->pFather->pLeft = pNodeB;
        }
        else
        {
            pNodeA->pFather->pRight = pNodeB;
        }
    }
    //三个父亲关系
    if(pNodeA->pRight != NULL)
    {
        pNodeA->pRight->pFather = pNodeA;//E的父亲是A
    }
    pNodeB->pFather = pNodeA->pFather;//B的父亲是X
    pNodeA->pFather = pNodeB;//A的父亲是B

}
int main()
{
    BinaryTree *pTree=NULL;
    pTree = CreateBinaryTree();
    PreorderTraversal(pTree);
    printf("\n");
    RightRotate(&pTree);
    PreorderTraversal(pTree);
    printf("\n");
    LeftRotate(&pTree);
    PreorderTraversal(pTree);
    printf("\n");
    return 0;
}
