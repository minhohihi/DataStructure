//
//  DataStruct_List.c
//  DataStructureCore
//
//  Created by Maverick on 2017. 2. 9..
//  Copyright © 2017년 Minhohihi. All rights reserved.
//


/*----------------------------------------------------------------------------------------
 File Inclusions
 ----------------------------------------------------------------------------------------*/
#include "DataStruct_List.h"


/*----------------------------------------------------------------------------------------
 Constant Definitions
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Macro Definitions
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Type Definitions
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Static Function
 ----------------------------------------------------------------------------------------*/
static Node * _DS_List_Node_Create(IN const int nData);
static void _DS_List_Node_Destroy(Node **ppNode);
static Node* _DS_List_Node_FindData(IN const NodeList *pList, IN const int nData);


/*----------------------------------------------------------------------------------------
 Static Variable
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Global Variable
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Function Implementation
 ----------------------------------------------------------------------------------------*/
#pragma mark - ArrayList
List* DS_List_Create(IN const unsigned int nMaxNumofData, IN const NodeType nNodeType)
{
    List                *pTmpList = NULL;
    
    SAFEALLOC(pTmpList, 1, 32, List);
    pTmpList->pAList = NULL;
    pTmpList->pNList = NULL;
    
    if(-1 == nMaxNumofData)
    {
        pTmpList->nNodeType = nNodeType;
        
        if(LIST_NODE_TYPE_SINGLE == nNodeType)
            pTmpList->pNList = DS_List_NodeS_Create();
        else if(LIST_NODE_TYPE_DOUBLE == nNodeType)
            pTmpList->pNList = DS_List_NodeD_Create();
    }
    else
        pTmpList->pAList = DS_List_Array_Create(nMaxNumofData);
    
    if((NULL == pTmpList->pNList) && (NULL == pTmpList->pAList))
        return NULL;
    
    return pTmpList;
}


int DS_List_Destroy(IN OUT List **ppList)
{
    if(NULL == (*ppList))
        return SUCCESS;

    if(NULL != (*ppList)->pAList)
        DS_List_Array_Destroy(&((*ppList)->pAList));
    else if(NULL != (*ppList)->pNList)
    {
        if(LIST_NODE_TYPE_SINGLE == (*ppList)->nNodeType)
            DS_List_NodeS_Destroy(&((*ppList)->pNList));
        else if(LIST_NODE_TYPE_DOUBLE == (*ppList)->nNodeType)
            DS_List_NodeD_Destroy(&((*ppList)->pNList));
    }
    
    SAFEFREE((*ppList));
    
    return SUCCESS;
}


int DS_List_IsFull(IN const List *pList)
{
    if(NULL != pList->pAList)
        return DS_List_Array_IsFull(pList->pAList);
    else
        return 0;
}


int DS_List_IsEmpty(const List *pList)
{
    if(NULL != pList->pAList)
        return DS_List_Array_IsEmpty(pList->pAList);
    else if(NULL != pList->pNList)
        return DS_List_Node_IsEmpty(pList->pNList);
    else
        return 0;
}


int DS_List_Insert(IN OUT List *pList, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData)
{
    if(NULL != pList->pAList)
        return DS_List_Array_Insert(pList->pAList, nData, nData, CompData);
    else if(NULL != pList->pNList)
    {
        if(LIST_NODE_TYPE_SINGLE == pList->nNodeType)
            return DS_List_NodeS_Insert(pList->pNList, nData, nData, CompData);
        else if(LIST_NODE_TYPE_DOUBLE == pList->nNodeType)
            return DS_List_NodeD_Insert(pList->pNList, nData, nData, CompData);
    }

    return FAIL;
}


int DS_List_Delete(IN OUT List *pList, IN const int nData)
{
    if(NULL != pList->pAList)
        return DS_List_Array_Delete(pList->pAList, nData);
    else if(NULL != pList->pNList)
    {
        if(LIST_NODE_TYPE_SINGLE == pList->nNodeType)
            return DS_List_NodeS_Delete(pList->pNList, nData);
        else if(LIST_NODE_TYPE_DOUBLE == pList->nNodeType)
            return DS_List_NodeD_Delete(pList->pNList, nData);
    }

    return FAIL;
}


int DS_List_DeleteFromDir(IN OUT List *pList, IN const ListDirection nDir, OUT int *pOutData)
{
    if(NULL != pList->pAList)
        return DS_List_Array_DeleteFromDir(pList->pAList, nDir, pOutData);
    else if(NULL != pList->pNList)
    {
        if(LIST_NODE_TYPE_SINGLE == pList->nNodeType)
            return DS_List_NodeS_DeleteFromDir(pList->pNList, nDir, pOutData);
        else if(LIST_NODE_TYPE_DOUBLE == pList->nNodeType)
            return DS_List_NodeD_DeleteFromDir(pList->pNList, nDir, pOutData);
    }
    
    return FAIL;
}


int DS_List_PeekFromDir(IN const List *pList, IN const ListDirection nDir, OUT int *pOutData)
{
    if(NULL != pList->pAList)
        return DS_List_Array_PeekFromDir(pList->pAList, nDir, pOutData);
    else if(NULL != pList->pNList)
    {
        if(LIST_NODE_TYPE_SINGLE == pList->nNodeType)
            return DS_List_NodeS_PeekFromDir(pList->pNList, nDir, pOutData);
        else if(LIST_NODE_TYPE_DOUBLE == pList->nNodeType)
            return DS_List_NodeD_PeekFromDir(pList->pNList, nDir, pOutData);
    }
    
    return FAIL;
}


#pragma mark - ArrayList
ArrayList* DS_List_Array_Create(IN const unsigned int nMaxNumofData)
{
    ArrayList           *pTmpList = NULL;

    SAFEALLOC(pTmpList, 1, 32, ArrayList);

    SAFEALLOC(pTmpList->pData, nMaxNumofData, 32, int);
    pTmpList->nCurrNumofData = 0;
    pTmpList->nMaxNumofData = nMaxNumofData;
    pTmpList->nHeadIdx = 0;
    pTmpList->nTailIdx = -1;
    
    return pTmpList;
}


int DS_List_Array_Destroy(IN OUT ArrayList **ppList)
{
    if(NULL == (*ppList))
        return SUCCESS;
    else
    {
        SAFEFREE((*ppList)->pData);
        SAFEFREE((*ppList));
        
        return SUCCESS;
    }
}


int DS_List_Array_IsFull(IN const ArrayList *pList)
{
    if(pList->nCurrNumofData == pList->nMaxNumofData)
        return 1;
    else
        return 0;
}


int DS_List_Array_IsEmpty(const ArrayList *pList)
{
    if(0 == pList->nCurrNumofData)
        return 1;
    else
        return 0;
}


int DS_List_Array_Insert(IN OUT ArrayList *pList, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData)
{
    if(1 == DS_List_Array_IsFull((const ArrayList *)pList))
        return FAIL;
    
    pList->nTailIdx++;

    if(NULL == CompData)
    {
        if(nDir == LIST_DIR_TAIL)
            pList->pData[pList->nTailIdx] = nData;
        else if(nDir == LIST_DIR_HEAD)
        {
            MEMCPY(&(pList->pData[1]), &(pList->pData[0]), pList->nCurrNumofData * sizeof(int));
            pList->pData[0] = nData;
        }
    }
    else
    {
        unsigned int            i = 0;
        const int               *pData = pList->pData;
        
        for(i=0 ; i<pList->nCurrNumofData ; i++)
            if(0 > CompData(pData[i], nData))
                break;
        
        if((i != pList->nCurrNumofData) && (0 != (pList->nTailIdx - i)))
            MEMCPY(&(pList->pData[i+1]), &(pList->pData[i]), (pList->nTailIdx - i) * sizeof(int));

        pList->pData[i] = nData;
    }
    
    pList->nCurrNumofData++;
    
    return SUCCESS;
}


int DS_List_Array_Delete(IN OUT ArrayList *pList, IN const int nData)
{
    unsigned int            i = 0;
    const int               *pData = pList->pData;

    if(1 == DS_List_Array_IsEmpty((const ArrayList *)pList))
        return SUCCESS;
    
    for(i=0 ; i<pList->nCurrNumofData ; i++)
        if(pData[i] == nData)
            break;
    
    if((i != pList->nCurrNumofData) && (0 != (pList->nTailIdx - i)))
        MEMCPY(&(pList->pData[i]), &(pList->pData[i + 1]), (pList->nTailIdx - i) * sizeof(int));
    
    pList->nTailIdx--;
    pList->nCurrNumofData--;
    
    return SUCCESS;
}


int DS_List_Array_DeleteFromDir(IN OUT ArrayList *pList, IN const ListDirection nDir, OUT int *pOutData)
{
    if(1 == DS_List_Array_IsEmpty((const ArrayList *)pList))
        return FAIL;

    if(LIST_DIR_INVALID <= nDir)
        return FAIL;
    
    pList->nCurrNumofData--;

    if(LIST_DIR_HEAD == nDir)
    {
        *pOutData = pList->pData[0];
        
        if(0 != pList->nCurrNumofData)
            MEMCPY(&(pList->pData[0]), &(pList->pData[1]), pList->nCurrNumofData * sizeof(int));
    }
    else if(LIST_DIR_TAIL == nDir)
        *pOutData = pList->pData[pList->nTailIdx];

    pList->nTailIdx--;

    return SUCCESS;
}


int DS_List_Array_PeekFromDir(IN const ArrayList *pList, IN const ListDirection nDir, OUT int *pOutData)
{
    if(1 == DS_List_Array_IsEmpty((const ArrayList *)pList))
        return FAIL;
    
    if(LIST_DIR_INVALID <= nDir)
        return FAIL;
    
    if(LIST_DIR_HEAD == nDir)
        *pOutData = pList->pData[0];
    else if(LIST_DIR_TAIL == nDir)
        *pOutData = pList->pData[pList->nTailIdx];
    
    return SUCCESS;
}


#pragma mark - Node Single List
NodeList* DS_List_NodeS_Create(void)
{
    NodeList            *pTmpList = NULL;
    
    SAFEALLOC(pTmpList, 1, 32, NodeList);
    if(NULL == pTmpList)
        return NULL;
    
    if(NULL == (pTmpList->pRoot = _DS_List_Node_Create(-1)))
        return NULL;
    
    pTmpList->nTotalNumofData = 0;
    pTmpList->pHead = pTmpList->pRoot;
    pTmpList->pTail = pTmpList->pRoot;
    
    return pTmpList;
}


int DS_List_NodeS_Destroy(IN OUT NodeList **ppList)
{
    Node                    *pCurrNode = NULL;
    NodeList                *pList = *ppList;
    
    pCurrNode = pList->pHead;
    
    // Find Proper Location
    while(NULL != pCurrNode)
    {
        Node                *pTmpNode = pCurrNode;
        
        pCurrNode = pCurrNode->pRNext;
        
        _DS_List_Node_Destroy(&pTmpNode);
    }
    
    SAFEFREE((*ppList));
    
    return SUCCESS;
}


int DS_List_NodeS_Insert(IN OUT NodeList *pList, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData)
{
    Node                    *pNewNode = NULL;
    
    // Alloc New Node
    if(NULL == (pNewNode = _DS_List_Node_Create(nData)))
        return FAIL;
    
    if(NULL == CompData)
    {
        if(nDir == LIST_DIR_TAIL)
        {
            // Attach New Node At The End of List & Update Tail Ptr
            pList->pTail->pRNext = pNewNode;
            pList->pTail = pNewNode;
        }
        else if(nDir == LIST_DIR_HEAD)
        {
            // Attach New Node At The Front of List
            pNewNode->pRNext = pList->pHead->pRNext;
            pList->pHead->pRNext = pNewNode;
        }
        else
            _DS_List_Node_Destroy(&pNewNode);
    }
    else
    {
        Node                    *pCurrNode = NULL;
        Node                    *pPrevNode = NULL;
        
        pPrevNode = pList->pHead;
        pCurrNode = pList->pHead->pRNext;
        
        // Find Proper Location
        while(NULL != pCurrNode)
        {
            if(0 > CompData(pCurrNode->nData, nData))
                break;
            
            pPrevNode = pCurrNode;
            pCurrNode = pCurrNode->pRNext;
        }
        
        pNewNode->pRNext = pCurrNode;
        pPrevNode->pRNext = pNewNode;
        
        // Update Tail If Needed
        if(NULL == pCurrNode)
            pList->pTail = pNewNode;
    }

    // Increase Total Number of Nodes
    pList->nTotalNumofData++;

    return SUCCESS;
}


int DS_List_NodeS_Delete(IN OUT NodeList *pList, IN const int nData)
{
    Node                    *pLocalNode = NULL;
    Node                    *pTmpNode = NULL;
    
    // Return If List is Empty
    if(1 == DS_List_Node_IsEmpty((const NodeList *)pList))
        return SUCCESS;
    
    // Find Target Node
    pLocalNode = _DS_List_Node_FindData((const NodeList *)(pList), nData);
    if(NULL == pLocalNode)
        return SUCCESS;
    
    // Update Tail Node If Found Node is the Last Node
    if(pLocalNode->pRNext == pList->pTail)
        pList->pTail = pLocalNode;
    
    // Update Link
    pTmpNode = pLocalNode->pRNext->pRNext;
    
    // De-Alloc Memory
    SAFEFREE(pLocalNode->pRNext);
    
    pLocalNode->pRNext = pTmpNode;
    
    // Decrease Total Number of Nodes
    pList->nTotalNumofData--;
    
    return SUCCESS;
}


int DS_List_NodeS_DeleteFromDir(IN OUT NodeList *pList, IN const ListDirection nDir, OUT int *pOutData)
{
    Node                *pNode = NULL;
    
    if(LIST_DIR_INVALID <= nDir)
        return FAIL;

    if(1 == DS_List_Node_IsEmpty((const NodeList *)pList))
        return FAIL;
    
    pList->nTotalNumofData--;
    
    if(LIST_DIR_HEAD == nDir)
    {
        pNode = pList->pHead->pRNext;
        
        *pOutData = pNode->nData;
        
        pList->pHead->pRNext = pNode->pRNext;
        
        if(NULL == pList->pHead->pRNext)
            pList->pTail = pList->pHead;
        
        // De-Alloc Memory
        SAFEFREE(pNode);
    }
    else if(LIST_DIR_TAIL == nDir)
    {
        // Find Previous Node Of Tail
        pNode = pList->pHead;
        while(pNode->pRNext != pList->pTail)
            pNode = pNode->pRNext;

        *pOutData = pList->pTail->nData;
        
        // De-Alloc Memory
        SAFEFREE(pList->pTail);

        pList->pTail = pNode;
        pList->pTail->pRNext = NULL;
    }
    
    return SUCCESS;
}


int DS_List_NodeS_PeekFromDir(IN const NodeList *pList, IN const ListDirection nDir, OUT int *pOutData)
{
    if(LIST_DIR_INVALID <= nDir)
        return FAIL;
    
    if(1 == DS_List_Node_IsEmpty((const NodeList *)pList))
        return FAIL;
    
    if(LIST_DIR_HEAD == nDir)
        *pOutData = pList->pHead->pRNext->nData;
    else if(LIST_DIR_TAIL == nDir)
        *pOutData = pList->pTail->nData;
    
    return SUCCESS;
}


#pragma mark - Node Double List
NodeList* DS_List_NodeD_Create(void)
{
    NodeList            *pTmpList = NULL;
    
    SAFEALLOC(pTmpList, 1, 32, NodeList);
    if(NULL == pTmpList)
        return NULL;
    
    if(NULL == (pTmpList->pRoot = _DS_List_Node_Create(-1)))
        return NULL;
    
    pTmpList->nTotalNumofData = 0;
    pTmpList->pHead = pTmpList->pRoot;
    pTmpList->pTail = pTmpList->pRoot;
    
    return pTmpList;
}


int DS_List_NodeD_Destroy(IN OUT NodeList **ppList)
{
    Node                    *pCurrNode = NULL;
    NodeList                *pList = *ppList;
    
    pCurrNode = pList->pHead;
    
    // Find Proper Location
    while(NULL != pCurrNode)
    {
        Node                *pTmpNode = pCurrNode;
        
        pCurrNode = pCurrNode->pRNext;
        
        _DS_List_Node_Destroy(&pTmpNode);
    }
    
    SAFEFREE((*ppList));
    
    return SUCCESS;
}


int DS_List_NodeD_Insert(IN OUT NodeList *pList, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData)
{
    Node                    *pNewNode = NULL;
    
    // Alloc New Node
    if(NULL == (pNewNode = _DS_List_Node_Create(nData)))
        return FAIL;
    
    if(NULL == CompData)
    {
        if(nDir == LIST_DIR_TAIL)
        {
            // Attach New Node At The End of List & Update Tail Ptr
            pList->pTail->pRNext = pNewNode;
            pNewNode->pLPrev = pList->pTail;
            pList->pTail = pNewNode;
        }
        else if(nDir == LIST_DIR_HEAD)
        {
            // Attach New Node At The Front of List
            pNewNode->pRNext = pList->pHead->pRNext;
            pNewNode->pLPrev = pList->pHead;
            if(NULL != pList->pHead->pRNext)
                pList->pHead->pRNext->pLPrev = pNewNode;
            pList->pHead->pRNext = pNewNode;
        }
        else
            _DS_List_Node_Destroy(&pNewNode);
    }
    else
    {
        Node                    *pCurrNode = NULL;
        Node                    *pPrevNode = NULL;
        
        pPrevNode = pList->pHead;
        pCurrNode = pList->pHead->pRNext;
        
        // Find Proper Location
        while(NULL != pCurrNode)
        {
            if(0 > CompData(pCurrNode->nData, nData))
                break;
            
            pPrevNode = pCurrNode;
            pCurrNode = pCurrNode->pRNext;
        }
        
        pNewNode->pLPrev = pPrevNode;
        pNewNode->pRNext = pCurrNode;
        pPrevNode->pRNext = pNewNode;
        if(NULL != pCurrNode)
            pCurrNode->pLPrev = pNewNode;
        
        // Update Tail If Needed
        if(NULL == pCurrNode)
            pList->pTail = pNewNode;
    }
    
    // Increase Total Number of Nodes
    pList->nTotalNumofData++;
    
    return SUCCESS;
}


int DS_List_NodeD_Delete(IN OUT NodeList *pList, IN const int nData)
{
    Node                    *pLocalNode = NULL;
    Node                    *pTmpNode = NULL;
    
    // Return If List is Empty
    if(1 == DS_List_Node_IsEmpty((const NodeList *)pList))
        return SUCCESS;
    
    // Find Target Node
    pLocalNode = _DS_List_Node_FindData((const NodeList *)(pList), nData);
    if(NULL == pLocalNode)
        return SUCCESS;
    
    // Update Tail Node If Found Node is the Last Node
    if(pLocalNode->pRNext == pList->pTail)
        pList->pTail = pLocalNode;
    
    // Update Link
    pTmpNode = pLocalNode->pRNext->pRNext;
    
    // De-Alloc Memory
    SAFEFREE(pLocalNode->pRNext);
    
    pLocalNode->pRNext = pTmpNode;
    
    // Decrease Total Number of Nodes
    pList->nTotalNumofData--;
    
    return SUCCESS;
}


int DS_List_NodeD_DeleteFromDir(IN OUT NodeList *pList, IN const ListDirection nDir, OUT int *pOutData)
{
    Node                *pNode = NULL;
    
    if(LIST_DIR_INVALID <= nDir)
        return FAIL;
    
    if(1 == DS_List_Node_IsEmpty((const NodeList *)pList))
        return FAIL;
    
    pList->nTotalNumofData--;
    
    if(LIST_DIR_HEAD == nDir)
    {
        pNode = pList->pHead->pRNext;
        
        *pOutData = pNode->nData;
        
        pList->pHead->pRNext = pNode->pRNext;
        
        if(NULL == pList->pHead->pRNext)
            pList->pTail = pList->pHead;
        else
            pList->pHead->pRNext->pLPrev = pList->pHead;
    }
    else if(LIST_DIR_TAIL == nDir)
    {
        pNode = pList->pTail;
        
        *pOutData = pNode->nData;
    
        pList->pTail = pNode->pLPrev;
        pList->pTail->pRNext = NULL;
    }
    
    // De-Alloc Memory
    SAFEFREE(pNode);
    
    return SUCCESS;
}


int DS_List_NodeD_PeekFromDir(IN const NodeList *pList, IN const ListDirection nDir, OUT int *pOutData)
{
    if(LIST_DIR_INVALID <= nDir)
        return FAIL;
    
    if(1 == DS_List_Node_IsEmpty((const NodeList *)pList))
        return FAIL;

    if(LIST_DIR_HEAD == nDir)
        *pOutData = pList->pHead->pRNext->nData;
    else if(LIST_DIR_TAIL == nDir)
        *pOutData = pList->pTail->nData;
    
    return SUCCESS;
}



#pragma mark - List Common
int DS_List_Node_IsEmpty(IN const NodeList *pList)
{
    if(0 == pList->nTotalNumofData)
        return 1;
    else
        return 0;
}


void DS_List_Array_Show(IN const ArrayList *pList)
{
    int                     i = 0;
    
    if(1 == DS_List_Array_IsEmpty(pList))
    {
        printf("List is Empty\n");
        return;
    }
    
    for(i=0 ; i<pList->nCurrNumofData ; i++)
        printf("%d ", pList->pData[i]);
    
    printf("\n");
}


void DS_List_Node_Show(IN const NodeList *pList)
{
    const Node              *pCurrNode = pList->pHead->pRNext;
    
    if(0 == pList->nTotalNumofData)
    {
        printf("List is Empty\n");
        return;
    }
    
    while(NULL != pCurrNode)
    {
        printf("%d ", pCurrNode->nData);
        
        pCurrNode = pCurrNode->pRNext;
    }
    
    printf("\n");
}



#pragma mark - Static Function
static Node * _DS_List_Node_Create(IN const int nData)
{
    Node                    *pNewNode = NULL;
    
    SAFEALLOC(pNewNode, 1, 32, Node);
    if(NULL == pNewNode)
        return NULL;
    
    pNewNode->nData = nData;
    pNewNode->pLPrev = NULL;
    pNewNode->pRNext = NULL;
    pNewNode->pDirAddr = NULL;
    
    return pNewNode;
}


static void _DS_List_Node_Destroy(Node **ppNode)
{
    SAFEFREE((*ppNode));
}


static Node* _DS_List_Node_FindData(IN const NodeList *pList, IN const int nData)
{
    Node                    *pCurrNode = NULL;
    Node                    *pPrevNode = NULL;
    
    // Return If List is Empty
    if(1 == DS_List_Node_IsEmpty((const NodeList *)pList))
        return NULL;
    
    pPrevNode = pList->pHead;
    pCurrNode = pList->pHead->pRNext;
    
    while(NULL != pCurrNode)
    {
        if(pCurrNode->nData == nData)
            return pPrevNode;
        
        pPrevNode = pCurrNode;
        pCurrNode = pCurrNode->pRNext;
    }
    
    return NULL;
}
















