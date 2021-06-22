#include<stdio.h>
#include<stdlib.h>

enum COLOR{RED,BLACK};

typedef struct rbt
{
    int nValue;
    int nColor;
    struct rbt *pLeft;
    struct rbt *pRight;
    struct rbt *pFather;
}RBT;

RBT *pRBT = NULL;

//右旋
void RightRotate(RBT **pTree)
{
    if(*pTree == NULL || (*pTree)->pLeft == NULL)return;
    RBT *pNodeA = *pTree;//A
    RBT *pNodeB = (*pTree)->pLeft;//B

    //三个孩子关系
    //children relation
    pNodeA->pLeft = pNodeB->pRight;//E是A的左
    pNodeB->pRight = pNodeA;//A是B的右
    //检测根是不是为空，B是X的孩子
    if(pNodeA->pFather == NULL)
    {
        pRBT = pNodeB;
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
void LeftRotate(RBT **pTree)
{
    if(*pTree == NULL || (*pTree)->pRight == NULL)return;
    RBT *pNodeA = *pTree;//A
    RBT *pNodeB = (*pTree)->pRight;//B

    //三个孩子关系
    pNodeA->pRight = pNodeB->pLeft;//E是A的右
    pNodeB->pLeft = pNodeA;//A是B的左
    //检测根是不是为空，B是X的孩子
    if(pNodeA->pFather == NULL)
    {
        pRBT = pNodeB;
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

//查找
RBT *Search(RBT *pTree,int nNum)
{
    if(pTree == NULL) return NULL;

    while(pTree)
    {
        if(pTree->nValue > nNum)
        {
            //左侧
            if(pTree->pLeft == NULL)
            {
                return pTree;
            }
            pTree = pTree->pLeft;
        }
        else if(pTree->nValue < nNum)
        {
            //右侧
            if(pTree->pRight == NULL)
            {
                return pTree;
            }
            pTree = pTree->pRight;
        }
        else
        {
            //数值相同，错误
            printf("Date is mistake\n");
            exit(1);
        }
    }
}

//得到叔叔节点
RBT *GetUncle(RBT *pNode)
{
    if(pNode == pNode->pFather->pLeft)
    {
        return pNode->pFather->pRight;
    }
    else
    {
        return pNode->pFather->pLeft;
    }
}

//添加节点
void AddNode(RBT *pTree,int nNum)
{
    //查找
    RBT *pNode = NULL;//父亲
    pNode = Search(pTree,nNum);

    //申请空间
    RBT *pTemp=(RBT*)malloc(sizeof(RBT));
    pTemp->nValue=nNum;
    pTemp->nColor=RED;
    pTemp->pFather=pNode;
    pTemp->pLeft=NULL;
    pTemp->pRight=NULL;

    //1.根
    if(pNode==NULL)
    {
        pRBT = pTemp;
        pTemp->nColor = BLACK;
        return;
    }
    //非根
    //节点放入树中
    if(pNode->nValue > nNum)
    {
        pNode->pLeft = pTemp;
        pTemp->pFather = pNode;
    }
    else
    {
        pNode->pRight = pTemp;
        pTemp->pFather = pNode;
    }
    //2.父亲是黑的
    if(pNode->nColor == BLACK)
    {
        return;
    }
    //3.父亲是红的
    RBT *pGrandFather = NULL;
    RBT *pUncle = NULL;

    while(pNode->nColor == RED)
    {
        RBT *pGrandFather =pNode->pFather;
        RBT *pUncle = GetUncle(pNode);

        //3.1叔叔是红的
        if(pUncle != NULL && pUncle->nColor == RED)
        {
            pNode->nColor = BLACK;
            pUncle->nColor = BLACK;
            pGrandFather->nColor = RED;
            pTemp = pGrandFather;
            pNode = pTemp->pFather;
            //原爷爷是不是根
            if(pTemp->pFather==NULL)
            {
                pTemp->nColor = BLACK;
                return;
            }
            else
                continue;
        }
        //3.2叔叔是黑的
        if(pUncle == NULL || pUncle->nColor == BLACK)
        {
            //3.2.1父亲是爷爷的左
            if(pNode == pGrandFather->pLeft)
            {
                //3.2.1.1当前节点是父亲的右
                if(pTemp == pNode->pRight)
                {
                    pTemp = pNode;
                    LeftRotate(&pTemp);
                    pNode = pTemp->pFather;
                    continue;
                }
                //3.2.1.2当前节点是父亲的左
                if(pTemp == pNode->pLeft)
                {
                    pNode->nColor = BLACK;
                    pGrandFather->nColor = RED;
                    RightRotate(&pGrandFather);
                    break;;
                }
            }
            //3.2.2父亲是爷爷的右
            if(pGrandFather->pRight == pNode)
            {
                //3.2.2.1当前节点是父亲的左
                if(pNode->pLeft == pTemp)
                {
                    pTemp = pNode;
                    RightRotate(&pTemp);
                    pNode = pTemp->pFather;
                    continue;
                }
                //3.2.2.2当前节点是父亲的右
                if(pNode->pRight == pTemp)
                {
                    pNode->nColor = BLACK;
                    pGrandFather->nColor = RED;
                    LeftRotate(&pGrandFather);
                    break;
                }
            }
        }
    }
}

//创建红黑树
void CreateRBT(int arr[],int nLength)
{
    if(arr == NULL|| nLength <= 0)return;
    int i;
    for(i=0;i<nLength;i++)
    {
        AddNode(pRBT,arr[i]);
    }
}

void Traversal(RBT *pTree)
{
    if(pTree == NULL)return;
    printf("value == %d\t col == %d\n",pTree->nValue,pTree->nColor);
    Traversal(pTree->pLeft);
    Traversal(pTree->pRight);
}

//删除节点的查找
RBT *Del_Search(RBT *pTree,int nNum)
{
    if(pTree == NULL)exit(1);

    while(pTree)
    {
        if(pTree->nValue == nNum)
        {
            return pTree;
        }
        else if(pTree->nValue > nNum)
        {
            pTree = pTree->pLeft;
        }
        else
        {
            pTree = pTree->pRight;
        }
    }
    return NULL;
}

//删除红黑树节点
void DeleteNode(RBT*pTree,int nNum)
{
    if(pTree == NULL)return;
    //查找
    RBT *pDel = NULL;
    pDel = Del_Search(pTree,nNum);
    if(pDel == NULL)return;
    //孩子情况
    RBT *pMark = NULL;
    if(pDel->pLeft != NULL && pDel->pRight != NULL)
    {
        pMark = pDel;
        //左的最右
        pDel = pDel->pLeft;
        while(pDel->pRight != NULL)
        {
            pDel = pDel->pRight;
        }
        //值覆盖
        pMark->nValue=pDel->nValue;
    }
    //颜色情况
    RBT *pNode = pDel->pFather;
    //1.根，且没孩子
    if(pNode == NULL && pDel->pLeft == NULL && pDel->pRight==NULL)
    {
        free(pDel);
        pDel = NULL;
        pRBT = NULL;
        return;
    }
    //2.根，且有一个红孩子
    if(pNode == NULL && (pDel->pLeft != NULL || pDel->pRight != NULL))
    {
        pRBT = pDel->pLeft ? pDel->pLeft : pDel->pRight;
        pRBT->nColor = BLACK;
        pRBT->pFather = NULL;
        free(pDel);
        pDel = NULL;
        return;
    }
    //3.非根，红叶子
    if(pDel->nColor == RED)
    {
        if(pDel == pNode->pLeft)
        {
            pNode->pLeft = NULL;
        }
        else
        {
            pNode->pRight = NULL;
        }
        free(pDel);
        pDel = NULL;
        return;
    }
    //4.非根，黑色，且有一个红孩子
    if(pNode != NULL && pDel->nColor == BLACK && (pDel->pLeft != NULL || pDel->pRight != NULL))
    {
        if(pNode->pLeft == pDel)
        {
            pNode->pLeft = pDel->pLeft?pDel->pLeft:pDel->pRight;
            pNode->pLeft->pFather = pNode;
            pNode->pLeft->nColor = BLACK;
        }
        else
        {
            pNode->pRight = pDel->pLeft?pDel->pLeft:pDel->pRight;
            pNode->pRight->pFather = pNode;
            pNode->pRight->nColor = BLACK;
        }
        free(pDel);
        pDel = NULL;
        return;
    }
    //5.非根，黑色，无孩子
    RBT *pBrother = NULL; 
    pBrother = GetUncle(pDel);
    //假删除
    if(pNode->pLeft == pDel)
    {
        pNode->pLeft = NULL;
    }
    else
    {
        pNode->pRight = NULL;
    }
    pMark = pDel;

    while(1)
    {
        //5.1兄弟是红的
        if(pBrother->nColor == RED)
        {
            pNode->nColor = RED;
            pBrother->nColor = BLACK;
            //5.1.1兄弟是父亲的右
            if(pBrother == pNode->pRight)
            {
                LeftRotate(&pNode);
                pBrother=pNode->pRight;
                continue;
            }
            //5.1.2兄弟是父亲的左
            if(pBrother == pNode->pLeft)
            {
                RightRotate(&pNode);
                pBrother=pNode->pLeft;
                continue;
            }
        }
        //5.2兄弟是黑色
        if(pBrother->nColor == BLACK)
        {
            //5.2.1两个侄子全黑
            if(  (pBrother->pLeft == NULL && pBrother->pRight == NULL)||
                    ((pBrother->pLeft != NULL && pBrother->pLeft->nColor == BLACK)
                     &&(pBrother->pRight != NULL && pBrother->pRight->nColor == BLACK))    )
            {
                //5.2.1.1父亲是红的
                if(pNode->nColor == RED)
                {
                    pNode->nColor = BLACK;
                    pBrother->nColor = RED;
                    return;
                }
                //5.2.1.2父亲是黑的
                if(pNode->nColor == BLACK)
                {
                    pBrother->nColor = RED;
                    pDel = pNode;
                    pNode = pDel->pFather;
                    if(pNode == NULL)
                        //是根则退出
                        break;
                    pBrother = GetUncle(pDel);
                    continue;
                }
            }
            //5.2.2左侄子红，右侄子黑
            if((pBrother->pLeft != NULL && pBrother->pLeft->nColor == RED) && 
                    (pBrother->pRight == NULL || pBrother->pRight->nColor == BLACK))
            {
                //5.2.2.1兄弟是父亲的右
                if(pBrother==pNode->pRight)
                {
                    pBrother->nColor = RED;
                    pBrother->pLeft->nColor = BLACK;
                    RightRotate(&pBrother);
                    pBrother = pNode->pRight;
                    continue;
                }
                //5.2.2.2兄弟是父亲的左
                if(pBrother == pNode->pLeft)
                {
                    pBrother->nColor = pNode->nColor;
                    pNode->nColor = BLACK;
                    pBrother->pLeft->nColor = BLACK;
                    RightRotate(&pNode);
                    break;
                }
            }
            //5.2.3右侄子红
            if(pBrother->pRight != NULL && pBrother->pRight->nColor == RED)
            {
                //5.2.3.1兄弟是父亲的左
                if(pBrother==pNode->pLeft)
                {
                    pBrother->nColor = RED;
                    pBrother->pRight->nColor = BLACK;
                    LeftRotate(&pBrother);
                    pBrother = pNode->pLeft;
                    continue;
                }
                //5.2.3.2兄弟是父亲的右
                if(pBrother == pNode->pRight)
                {
                    pBrother->nColor = pNode->nColor;
                    pNode->nColor = BLACK;
                    pBrother->pRight->nColor = BLACK;
                    LeftRotate(&pNode);
                    return;
                }
            }
        }
    }
    //释放
    free(pDel);
    pDel = NULL;
}

int main()
{
    int arr[] = {11,2,14,1,7,15,5,8};
    CreateRBT(arr,sizeof(arr)/sizeof(arr[0]));
    Traversal(pRBT);
    printf("-------------------------------------\n");
    //AddNode(pRBT,4);
    DeleteNode(pRBT,1);
    Traversal(pRBT);
    printf("-------------------------------------\n");
    /*DeleteNode(pRBT,7);
    Traversal(pRBT);
    printf("-------------------------------------\n");
    DeleteNode(pRBT,8);
    Traversal(pRBT);
    printf("-------------------------------------\n");
    DeleteNode(pRBT,14);
    Traversal(pRBT);*/

    DeleteNode(pRBT,8);
    Traversal(pRBT);
    printf("-------------------------------------\n");
    return 0;
}
