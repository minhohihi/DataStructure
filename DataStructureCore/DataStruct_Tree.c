//
//  DataStruct_Tree.c
//  DataStructureCore
//
//  Created by Maverick on 2017. 2. 9..
//  Copyright © 2017년 Minhohihi. All rights reserved.
//


/*----------------------------------------------------------------------------------------
 File Inclusions
 ----------------------------------------------------------------------------------------*/
#include "DataStruct_Tree.h"


/*----------------------------------------------------------------------------------------
 Constant Definitions
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Macro Definitions
 ----------------------------------------------------------------------------------------*/
#define GET_DATA(pBNode)                    (pBNode->nData)
#define SET_DATA(pBNode, nData)             pBNode->nData = nData;
#define SET_LNODE(pPNode, pNewNode)         pPNode->pLNode = pNewNode
#define SET_RNODE(pPNode, pNewNode)         pPNode->pRNode = pNewNode
#define HAVE_WHICH_CHILD(pPNode)            (!(!(pPNode->pLNode))) | ((!(!(pPNode->pRNode))) << 1)


/*----------------------------------------------------------------------------------------
 Type Definitions
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Static Function
 ----------------------------------------------------------------------------------------*/
static BNode* _DS_BTree_CreateBNode(IN const DATA nData);
static int _DS_BTree_DestroyBNode(BNode **ppNode);
static int _DS_BTree_FindData(IN const BTree *pTree, IN const DATA nData, OUT BNode **ppPNode, OUT BNode **ppTNode);
static int _DS_BTree_FindMostBiggest(IN const BNode *pRNode, OUT BNode **ppPNode, OUT BNode **ppTNode);
static int _DS_BTree_FindMostSmallest(IN const BNode *pRNode, OUT BNode **ppPNode, OUT BNode **ppTNode);
static int _DS_BTree_TravelPreCore(IN const BNode *pPNode);
static int _DS_BTree_TravelInCore(IN const BNode *pPNode);
static int _DS_BTree_TravelPostCore(IN const BNode *pPNode);
static int _DS_BTree_Height(IN const BNode *pBNode);
static int _DS_BTree_DiffHeight(IN const BNode *pBNode);
static BNode* _DS_BTree_AVL_LL(IN OUT BNode *pRootNode);
static BNode* _DS_BTree_AVL_RR(IN OUT BNode *pRootNode);
static BNode* _DS_BTree_AVL_LR(IN OUT BNode *pRootNode);
static BNode* _DS_BTree_AVL_RL(IN OUT BNode *pRootNode);


/*----------------------------------------------------------------------------------------
 Static Variable
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Global Variable
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Function Implementation
 ----------------------------------------------------------------------------------------*/
void* DS_BTree_Create(void)
{
    BTree               *pTreeHndl = NULL;
    
    SAFEALLOC(pTreeHndl, 1, 32, BTree);
    if(NULL == pTreeHndl)
        return NULL;
    
    if(NULL == (pTreeHndl->pVRootNode = _DS_BTree_CreateBNode(0)))
        return NULL;
    
    return (void *)pTreeHndl;
}


int DS_BTree_Destroy(IN OUT void **ppTreeHndl)
{
    BTree               *pTree = (BTree *)(*ppTreeHndl);
    
    SAFEFREE(pTree->pVRootNode);
    SAFEFREE(pTree);
    
    return SUCCESS;
}


int DS_BTree_Insert(IN OUT void *pTreeHndl, IN const DATA nData)
{
    BTree               *pTree = (BTree *)pTreeHndl;
    BNode               *pBNode = pTree->pVRootNode->pRNode;
    BNode               *pNewNode = _DS_BTree_CreateBNode(nData);
    
    if(NULL != pBNode)
    {
        BNode           *pPNode = NULL;         // Parent Node
        BNode           *pTNode = NULL;         // Target Node
        
        if(FAIL == _DS_BTree_FindData(pTree, nData, &pPNode, &pTNode))
        {
            // Insert Data at The End of Tree
            if(nData < GET_DATA(pPNode))
                SET_LNODE(pPNode, pNewNode);
            else
                SET_RNODE(pPNode, pNewNode);
        }
        else
        {
            // Ignore Same Data. Just Return Success
            return SUCCESS;
        }
    }
    else
    {
        // If Root Node is Empty
        pTree->pVRootNode->pRNode = pNewNode;
        
        return SUCCESS;
    }
    
    return SUCCESS;
}


int DS_BTree_Delete(IN OUT void *pTreeHndl, IN const DATA nData)
{
    BTree               *pTree = (BTree *)pTreeHndl;
    BNode               *pBNode = pTree->pVRootNode->pRNode;

    if(NULL != pBNode)
    {
        BNode           *pPNode = NULL;         // Parent Node
        BNode           *pTNode = NULL;         // Target Node
        BNode           *pCNode = NULL;         // Child Node

        if(SUCCESS == _DS_BTree_FindData(pTree, nData, &pPNode, &pTNode))
        {
            const int   nChildrenIndicator = HAVE_WHICH_CHILD(pTNode);
            
            switch(nChildrenIndicator)
            {
                case 0:
                    // No Children
                    if(pPNode->pLNode == pTNode)
                        _DS_BTree_DestroyBNode(&(pPNode->pLNode));
                    else
                        _DS_BTree_DestroyBNode(&(pPNode->pRNode));
                    break;
                    
                case 1:
                case 2:
                    // Has Left Child Only or Has Right Child Only
                    pCNode = (1 == nChildrenIndicator) ? pTNode->pLNode : pTNode->pRNode;
                    
                    if(pPNode->pLNode == pTNode)
                        SET_LNODE(pPNode, pCNode);
                    else
                        SET_RNODE(pPNode, pCNode);
                        
                    _DS_BTree_DestroyBNode(&pTNode);
                    break;
                    
                case 3:
                    // Has Both Children
                    {
                        BNode       *pTmpPNode = NULL;
                        BNode       *pTmpTNode = NULL;
                        
                        _DS_BTree_FindMostSmallest(pTNode->pRNode, &pTmpPNode, &pTmpTNode);
                        
                        pTNode->nData = GET_DATA(pTmpTNode);
                        
                        if(pTmpPNode->pLNode == pTmpTNode)
                            SET_LNODE(pTmpPNode, pTmpTNode->pRNode);
                        else
                            SET_RNODE(pTmpPNode, pTmpTNode->pRNode);
                            
                        _DS_BTree_DestroyBNode(&pTmpTNode);
                    }
                    break;
                default:
                    return FAIL;
            }
        }
        else
            return SUCCESS;
    }
    
    return SUCCESS;
}


int DS_BTree_Search(IN const void *pTreeHndl, IN const DATA nData)
{
    const BTree         *pTree = (BTree *)pTreeHndl;
    BNode               *pPNode = NULL;         // Parent Node
    BNode               *pTNode = NULL;         // Target Node
    
    if(SUCCESS == _DS_BTree_FindData(pTree, nData, &pPNode, &pTNode))
        return SUCCESS;
    else
        return FAIL;
}


int DS_BTree_DoBalancing(IN OUT void *pTreeHndl)
{
    BTree               *pTree = (BTree *)pTreeHndl;
    BNode               *pRootNode = pTree->pVRootNode->pRNode;
    const int           nHeightDiff = _DS_BTree_DiffHeight(pRootNode);
    
    if(NULL == pRootNode)
        return SUCCESS;
    
    if(nHeightDiff > 1)
    {
        const int       nSubTreeHeightDiff = _DS_BTree_DiffHeight(pRootNode->pLNode);
        
        if(nSubTreeHeightDiff > 0)
            pTree->pVRootNode->pRNode = _DS_BTree_AVL_LL(pRootNode);
        else
            pTree->pVRootNode->pRNode = _DS_BTree_AVL_LR(pRootNode);
    }
    else if(nHeightDiff < -1)
    {
        const int       nSubTreeHeightDiff = _DS_BTree_DiffHeight(pRootNode->pRNode);
        
        if(nSubTreeHeightDiff < 0)
            pTree->pVRootNode->pRNode = _DS_BTree_AVL_RR(pRootNode);
        else
            pTree->pVRootNode->pRNode = _DS_BTree_AVL_RL(pRootNode);
    }
    
    return SUCCESS;
}


int DS_BTree_TravelPre(IN const void *pTreeHndl)
{
    const BTree         *pTree = (BTree *)pTreeHndl;
    
    _DS_BTree_TravelPreCore((const BNode *)pTree->pVRootNode->pRNode);
    
    return SUCCESS;
}


int DS_BTree_TravelIn(IN const void *pTreeHndl)
{
    const BTree         *pTree = (BTree *)pTreeHndl;
    
    _DS_BTree_TravelInCore((const BNode *)pTree->pVRootNode->pRNode);
    
    return SUCCESS;
}


int DS_BTree_TravelPost(IN const void *pTreeHndl)
{
    const BTree         *pTree = (BTree *)pTreeHndl;
    
    _DS_BTree_TravelPostCore((const BNode *)pTree->pVRootNode->pRNode);
    
    return SUCCESS;
}


static BNode* _DS_BTree_CreateBNode(IN const DATA nData)
{
    BNode               *pBNode = NULL;
    
    SAFEALLOC(pBNode, 1, 32, BNode);
    if(NULL == pBNode)
        return NULL;
    
    pBNode->nData = nData;
    pBNode->pLNode = NULL;
    pBNode->pRNode = NULL;
    
    return pBNode;
}


static int _DS_BTree_DestroyBNode(BNode **ppNode)
{
    BNode               *pBNode = *ppNode;
    
    SAFEFREE(pBNode);
    if(NULL != pBNode)
        return FAIL;
    
    return SUCCESS;
}


static int _DS_BTree_FindData(IN const BTree *pTree, IN const DATA nTagetData, OUT BNode **ppPNode, OUT BNode **ppTNode)
{
    *ppPNode = pTree->pVRootNode;
    *ppTNode = (*ppPNode)->pRNode;
    
    while(NULL != *ppTNode)
    {
        const DATA      nData = GET_DATA((*ppTNode));
        
        if(nTagetData == nData)
            return SUCCESS;
            
        *ppPNode = *ppTNode;
        
        if(nTagetData < nData)
            *ppTNode = (*ppTNode)->pLNode;
        else
            *ppTNode = (*ppTNode)->pRNode;
    }
    
    if(NULL == (*ppTNode))
        return FAIL;
    else
        return SUCCESS;
}


static int _DS_BTree_FindMostBiggest(IN const BNode *pRNode, OUT BNode **ppPNode, OUT BNode **ppTNode)
{
    *ppPNode = (BNode *)pRNode;
    *ppTNode = (*ppPNode)->pRNode;
    
    while(NULL != *ppTNode)
    {
        *ppPNode = *ppTNode;
        
        *ppTNode = (*ppTNode)->pRNode;
    }
    
    if(NULL == (*ppTNode))
        return FAIL;
    else
        return SUCCESS;
}


static int _DS_BTree_FindMostSmallest(IN const BNode *pRNode, OUT BNode **ppPNode, OUT BNode **ppTNode)
{
    *ppPNode = (BNode *)pRNode;
    *ppTNode = (*ppPNode)->pLNode;
    
    while(NULL != *ppTNode)
    {
        *ppPNode = *ppTNode;
        
        *ppTNode = (*ppTNode)->pLNode;
    }
    
    if(NULL == (*ppTNode))
        return FAIL;
    else
        return SUCCESS;
}


static int _DS_BTree_TravelPreCore(IN const BNode *pPNode)
{
    if(NULL == pPNode)
        return SUCCESS;
    
    _DS_BTree_TravelPreCore(pPNode->pLNode);
    _DS_BTree_TravelPreCore(pPNode->pRNode);
    
    return SUCCESS;
}


static int _DS_BTree_TravelInCore(IN const BNode *pPNode)
{
    if(NULL == pPNode)
        return SUCCESS;
    
    
    _DS_BTree_TravelInCore(pPNode->pLNode);
    _DS_BTree_TravelInCore(pPNode->pRNode);
    
    return SUCCESS;
}


static int _DS_BTree_TravelPostCore(IN const BNode *pPNode)
{
    if(NULL == pPNode)
        return SUCCESS;
    
    
    _DS_BTree_TravelPostCore(pPNode->pLNode);
    _DS_BTree_TravelPostCore(pPNode->pRNode);
    
    return SUCCESS;
}


static int _DS_BTree_Height(IN const BNode *pBNode)
{
    int             nLeftHeight = 0;
    int             nRightHeight = 0;
    
    if(NULL == pBNode)
        return 0;
    
    nLeftHeight = _DS_BTree_Height(pBNode->pLNode);
    nRightHeight = _DS_BTree_Height(pBNode->pRNode);
    
    return GET_MAX(nLeftHeight, nRightHeight) + 1;
}


static int _DS_BTree_DiffHeight(IN const BNode *pBNode)
{
    int             nLeftHeight = 0;
    int             nRightHeight = 0;
    
    if(NULL == pBNode)
        return 0;
    
    nLeftHeight = _DS_BTree_Height(pBNode->pLNode);
    nRightHeight = _DS_BTree_Height(pBNode->pRNode);

    return nLeftHeight - nRightHeight;
}


static BNode* _DS_BTree_AVL_LL(IN OUT BNode *pRootNode)
{
    if(NULL != pRootNode)
    {
        BNode           *pChildNode = pRootNode->pLNode;
        
        SET_LNODE(pRootNode, pChildNode->pRNode);
        SET_RNODE(pChildNode, pRootNode);
        
        return pChildNode;
    }
    else
        return NULL;
}


static BNode* _DS_BTree_AVL_RR(IN OUT BNode *pRootNode)
{
    if(NULL != pRootNode)
    {
        BNode           *pChildNode = pRootNode->pRNode;
        
        SET_RNODE(pRootNode, pChildNode->pLNode);
        SET_LNODE(pChildNode, pRootNode);
        
        return pChildNode;
    }
    else
        return NULL;
}


static BNode* _DS_BTree_AVL_LR(IN OUT BNode *pRootNode)
{
    if(NULL != pRootNode)
    {
        BNode           *pChildNode = pRootNode->pLNode;
        
        SET_LNODE(pRootNode, _DS_BTree_AVL_RR(pChildNode));
        
        return _DS_BTree_AVL_LL(pRootNode);
    }
    else
        return NULL;
}


static BNode* _DS_BTree_AVL_RL(IN OUT BNode *pRootNode)
{
    if(NULL != pRootNode)
    {
        BNode           *pChildNode = pRootNode->pRNode;
        
        SET_RNODE(pRootNode, _DS_BTree_AVL_LL(pChildNode->pRNode));
        
        return _DS_BTree_AVL_RR(pRootNode);
    }
    else
        return NULL;
}











