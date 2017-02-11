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
// Array List Define
static void* _DS_List_Array_Create(IN const unsigned int nMaxNumofData);
static int _DS_List_Array_Destroy(IN OUT void **ppListCore);
static int _DS_List_Array_IsFull(IN const void *pListCore);
static int _DS_List_Array_IsEmpty(IN const void *pListCore);
static int _DS_List_Array_Insert(IN OUT void *pListCore, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData);
static int _DS_List_Array_Delete(IN OUT void *pListCore, IN const int nData);
static int _DS_List_Array_DeleteFromDir(IN OUT void *pListCore, IN const ListDirection nDir, OUT int *pOutData);
static int _DS_List_Array_PeekFromDir(IN const void *pListCore, IN const ListDirection nDir, OUT int *pOutData);

// Node Single List Define
static void* _DS_List_NodeS_Create(void);
static int _DS_List_NodeS_Destroy(IN OUT void **ppListCore);
static int _DS_List_NodeS_Insert(IN OUT void *pListCore, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData);
static int _DS_List_NodeS_Delete(IN OUT void *pListCore, IN const int nData);
static int _DS_List_NodeS_DeleteFromDir(IN OUT void *pListCore, IN const ListDirection nDir, OUT int *pOutData);
static int _DS_List_NodeS_PeekFromDir(IN const void *pListCore, IN const ListDirection nDir, OUT int *pOutData);

// Node Double List Define
static void* _DS_List_NodeD_Create(void);
static int _DS_List_NodeD_Destroy(IN OUT void **ppListCore);
static int _DS_List_NodeD_Insert(IN OUT void *pListCore, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData);
static int _DS_List_NodeD_Delete(IN OUT void *pListCore, IN const int nData);
static int _DS_List_NodeD_DeleteFromDir(IN OUT void *pListCore, IN const ListDirection nDir, OUT int *pOutData);
static int _DS_List_NodeD_PeekFromDir(IN const void *pListCore, IN const ListDirection nDir, OUT int *pOutData);


static Node * _DS_List_Node_Create(IN const int nData);
static void _DS_List_Node_Destroy(Node **ppNode);
static Node* _DS_List_Node_FindData(IN const NodeList *pListCore, IN const int nData);
int _DS_List_Node_IsEmpty(IN const void *pListCore);
void _DS_List_Array_Show(IN const void *pListCore);
void _DS_List_Node_Show(IN const void *pListCore);


/*----------------------------------------------------------------------------------------
 Static Variable
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Global Variable
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Function Implementation
 ----------------------------------------------------------------------------------------*/
#pragma mark - List
void* DS_List_Create(IN const unsigned int nMaxNumofData, IN const ListType nListType)
{
    List                *pTmpListHndl = NULL;
    
    SAFEALLOC(pTmpListHndl, 1, 32, List);
    pTmpListHndl->pListCore = NULL;
    pTmpListHndl->nListType = nListType;
    
    switch(pTmpListHndl->nListType)
    {
        case LIST_TYPE_SINGLE:
            pTmpListHndl->pListCore = _DS_List_NodeS_Create();
            break;
        case LIST_TYPE_DOUBLE:
            pTmpListHndl->pListCore = _DS_List_NodeD_Create();
            break;
        case LIST_TYPE_ARRAY:
            if(0 >= nMaxNumofData)
                break;
            
            pTmpListHndl->pListCore = _DS_List_Array_Create(nMaxNumofData);
            break;
        default:
            break;
    }
    
    if(NULL == pTmpListHndl->pListCore)
        return NULL;
    
    return (void *)pTmpListHndl;
}


int DS_List_Destroy(IN OUT void **ppListHndl)
{
    List                **ppList = (List **)ppListHndl;
    
    if(NULL == (*ppList))
        return SUCCESS;

    switch((*ppList)->nListType)
    {
        case LIST_TYPE_SINGLE:
            _DS_List_NodeS_Destroy(&((*ppList)->pListCore));
            break;
        case LIST_TYPE_DOUBLE:
            _DS_List_NodeD_Destroy(&((*ppList)->pListCore));
            break;
        case LIST_TYPE_ARRAY:
            _DS_List_Array_Destroy(&((*ppList)->pListCore));
            break;
        default:
            break;
    }
    
    SAFEFREE((*ppList));
    
    return SUCCESS;
}


int DS_List_IsFull(IN const void *pListHndl)
{
    List                *pList = (List *)pListHndl;
    
    switch(pList->nListType)
    {
        case LIST_TYPE_SINGLE:
        case LIST_TYPE_DOUBLE:
            return 0;
        case LIST_TYPE_ARRAY:
            return _DS_List_Array_IsFull(pList->pListCore);
        default:
            return 0;
    }
}


int DS_List_IsEmpty(IN const void *pListHndl)
{
    List                *pList = (List *)pListHndl;

    switch(pList->nListType)
    {
        case LIST_TYPE_SINGLE:
        case LIST_TYPE_DOUBLE:
            return _DS_List_Node_IsEmpty(pList->pListCore);
        case LIST_TYPE_ARRAY:
            return _DS_List_Array_IsEmpty(pList->pListCore);
        default:
            return 0;
    }
}


int DS_List_Insert(IN OUT void *pListHndl, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData)
{
    List                *pList = (List *)pListHndl;

    switch(pList->nListType)
    {
        case LIST_TYPE_SINGLE:
            return _DS_List_NodeS_Insert(pList->pListCore, nData, nDir, CompData);
        case LIST_TYPE_DOUBLE:
            return _DS_List_NodeD_Insert(pList->pListCore, nData, nDir, CompData);
        case LIST_TYPE_ARRAY:
            return _DS_List_Array_Insert(pList->pListCore, nData, nDir, CompData);
        default:
            return FAIL;
    }
}


int DS_List_Delete(IN OUT void *pListHndl, IN const int nData)
{
    List                *pList = (List *)pListHndl;

    switch(pList->nListType)
    {
        case LIST_TYPE_SINGLE:
            return _DS_List_NodeS_Delete(pList->pListCore, nData);
        case LIST_TYPE_DOUBLE:
            return _DS_List_NodeD_Delete(pList->pListCore, nData);
        case LIST_TYPE_ARRAY:
            return _DS_List_Array_Delete(pList->pListCore, nData);
        default:
            return FAIL;
    }
}


int DS_List_DeleteFromDir(IN OUT void *pListHndl, IN const ListDirection nDir, OUT int *pOutData)
{
    List                *pList = (List *)pListHndl;

    switch(pList->nListType)
    {
        case LIST_TYPE_SINGLE:
            return _DS_List_NodeS_DeleteFromDir(pList->pListCore, nDir, pOutData);
        case LIST_TYPE_DOUBLE:
            return _DS_List_NodeD_DeleteFromDir(pList->pListCore, nDir, pOutData);
        case LIST_TYPE_ARRAY:
            return _DS_List_Array_DeleteFromDir(pList->pListCore, nDir, pOutData);
        default:
            return FAIL;
    }
}


int DS_List_PeekFromDir(IN const void *pListHndl, IN const ListDirection nDir, OUT int *pOutData)
{
    List                *pList = (List *)pListHndl;

    switch(pList->nListType)
    {
        case LIST_TYPE_SINGLE:
            return _DS_List_NodeS_PeekFromDir(pList->pListCore, nDir, pOutData);
        case LIST_TYPE_DOUBLE:
            return _DS_List_NodeD_PeekFromDir(pList->pListCore, nDir, pOutData);
        case LIST_TYPE_ARRAY:
            return _DS_List_Array_PeekFromDir(pList->pListCore, nDir, pOutData);
        default:
            return FAIL;
    }
}


void DS_List_ShowData(IN const void *pListHndl)
{
    List                *pList = (List *)pListHndl;
    
    switch(pList->nListType)
    {
        case LIST_TYPE_SINGLE:
        case LIST_TYPE_DOUBLE:
            return _DS_List_Node_Show(pList->pListCore);
        case LIST_TYPE_ARRAY:
            return _DS_List_Array_Show(pList->pListCore);
        default:
            return;
    }
}



#pragma mark - ArrayList
static void* _DS_List_Array_Create(IN const unsigned int nMaxNumofData)
{
    ArrayList           *pTmpList = NULL;

    SAFEALLOC(pTmpList, 1, 32, ArrayList);

    SAFEALLOC(pTmpList->pData, nMaxNumofData, 32, int);
    pTmpList->nCurrNumofData = 0;
    pTmpList->nMaxNumofData = nMaxNumofData;
    pTmpList->nTailIdx = -1;
    
    return (ArrayList *)pTmpList;
}


static int _DS_List_Array_Destroy(IN OUT void **ppListCore)
{
    ArrayList           **ppList = (ArrayList **)ppListCore;
    
    if(NULL == (*ppList))
        return SUCCESS;
    else
    {
        SAFEFREE((*ppList)->pData);
        SAFEFREE((*ppList));
        
        return SUCCESS;
    }
}


static int _DS_List_Array_IsFull(IN const void *pListCore)
{
    const ArrayList     *pList = (ArrayList *)pListCore;
    
    if(pList->nCurrNumofData == pList->nMaxNumofData)
        return 1;
    else
        return 0;
}


static int _DS_List_Array_IsEmpty(const void *pListCore)
{
    const ArrayList     *pList = (ArrayList *)pListCore;
    
    if(0 == pList->nCurrNumofData)
        return 1;
    else
        return 0;
}


static int _DS_List_Array_Insert(IN OUT void *pListCore, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData)
{
    ArrayList           *pList = (ArrayList *)pListCore;
    
    if(1 == _DS_List_Array_IsFull((const ArrayList *)pList))
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


static int _DS_List_Array_Delete(IN OUT void *pListCore, IN const int nData)
{
    ArrayList               *pList = (ArrayList *)pListCore;
    unsigned int            i = 0;
    const int               *pData = pList->pData;

    if(1 == _DS_List_Array_IsEmpty((const ArrayList *)pList))
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


static int _DS_List_Array_DeleteFromDir(IN OUT void *pListCore, IN const ListDirection nDir, OUT int *pOutData)
{
    ArrayList               *pList = (ArrayList *)pListCore;
    
    if(1 == _DS_List_Array_IsEmpty((const ArrayList *)pList))
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


static int _DS_List_Array_PeekFromDir(IN const void *pListCore, IN const ListDirection nDir, OUT int *pOutData)
{
    const ArrayList         *pList = (ArrayList *)pListCore;

    if(1 == _DS_List_Array_IsEmpty(pList))
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
static void* _DS_List_NodeS_Create(void)
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


static int _DS_List_NodeS_Destroy(IN OUT void **ppListCore)
{
    Node                    *pCurrNode = NULL;
    NodeList                **ppList = (NodeList **)ppListCore;
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


static int _DS_List_NodeS_Insert(IN OUT void *pListCore, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData)
{
    Node                    *pNewNode = NULL;
    NodeList                *pList = (NodeList *)pListCore;
    
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


static int _DS_List_NodeS_Delete(IN OUT void *pListCore, IN const int nData)
{
    Node                    *pLocalNode = NULL;
    Node                    *pTmpNode = NULL;
    NodeList                *pList = (NodeList *)pListCore;
    
    // Return If List is Empty
    if(1 == _DS_List_Node_IsEmpty((const NodeList *)pList))
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


static int _DS_List_NodeS_DeleteFromDir(IN OUT void *pListCore, IN const ListDirection nDir, OUT int *pOutData)
{
    Node                    *pNode = NULL;
    NodeList                *pList = (NodeList *)pListCore;
    
    if(LIST_DIR_INVALID <= nDir)
        return FAIL;

    if(1 == _DS_List_Node_IsEmpty((const NodeList *)pList))
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


static int _DS_List_NodeS_PeekFromDir(IN const void *pListCore, IN const ListDirection nDir, OUT int *pOutData)
{
    NodeList                *pList = (NodeList *)pListCore;
    
    if(LIST_DIR_INVALID <= nDir)
        return FAIL;
    
    if(1 == _DS_List_Node_IsEmpty((const NodeList *)pList))
        return FAIL;
    
    if(LIST_DIR_HEAD == nDir)
        *pOutData = pList->pHead->pRNext->nData;
    else if(LIST_DIR_TAIL == nDir)
        *pOutData = pList->pTail->nData;
    
    return SUCCESS;
}


#pragma mark - Node Double List
static void* _DS_List_NodeD_Create(void)
{
    NodeList                *pTmpList = NULL;
    
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


static int _DS_List_NodeD_Destroy(IN OUT void **ppListCore)
{
    Node                    *pCurrNode = NULL;
    NodeList                **ppList = (NodeList **)ppListCore;
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


static int _DS_List_NodeD_Insert(IN OUT void *pListCore, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData)
{
    Node                    *pNewNode = NULL;
    NodeList                *pList = (NodeList *)pListCore;
    
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


static int _DS_List_NodeD_Delete(IN OUT void *pListCore, IN const int nData)
{
    Node                    *pLocalNode = NULL;
    Node                    *pTmpNode = NULL;
    NodeList                *pList = (NodeList *)pListCore;
    
    // Return If List is Empty
    if(1 == _DS_List_Node_IsEmpty((const NodeList *)pList))
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


static int _DS_List_NodeD_DeleteFromDir(IN OUT void *pListCore, IN const ListDirection nDir, OUT int *pOutData)
{
    Node                *pNode = NULL;
    NodeList                *pList = (NodeList *)pListCore;
    
    if(LIST_DIR_INVALID <= nDir)
        return FAIL;
    
    if(1 == _DS_List_Node_IsEmpty((const NodeList *)pList))
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


static int _DS_List_NodeD_PeekFromDir(IN const void *pListCore, IN const ListDirection nDir, OUT int *pOutData)
{
    NodeList                *pList = (NodeList *)pListCore;
    
    if(LIST_DIR_INVALID <= nDir)
        return FAIL;
    
    if(1 == _DS_List_Node_IsEmpty((const NodeList *)pList))
        return FAIL;

    if(LIST_DIR_HEAD == nDir)
        *pOutData = pList->pHead->pRNext->nData;
    else if(LIST_DIR_TAIL == nDir)
        *pOutData = pList->pTail->nData;
    
    return SUCCESS;
}


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
    if(1 == _DS_List_Node_IsEmpty((const NodeList *)pList))
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


int _DS_List_Node_IsEmpty(IN const void *pListCore)
{
    NodeList                *pList = (NodeList *)pListCore;
    
    if(0 == pList->nTotalNumofData)
        return 1;
    else
        return 0;
}


void _DS_List_Array_Show(IN const void *pListCore)
{
    int                     i = 0;
    ArrayList               *pList = (ArrayList *)pListCore;
    
    if(1 == _DS_List_Array_IsEmpty(pList))
    {
        printf("List is Empty\n");
        return;
    }
    
    for(i=0 ; i<pList->nCurrNumofData ; i++)
        printf("%d ", pList->pData[i]);
    
    printf("\n");
}


void _DS_List_Node_Show(IN const void *pListCore)
{
    NodeList                *pList = (NodeList *)pListCore;
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














