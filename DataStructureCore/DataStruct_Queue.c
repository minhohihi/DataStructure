//
//  DataStruct_Queue.c
//  DataStructureCore
//
//  Created by Maverick on 2017. 2. 9..
//  Copyright © 2017년 Minhohihi. All rights reserved.
//



/*----------------------------------------------------------------------------------------
 File Inclusions
 ----------------------------------------------------------------------------------------*/
#include "DataStruct_Queue.h"


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


/*----------------------------------------------------------------------------------------
 Static Variable
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Global Variable
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Function Implementation
 ----------------------------------------------------------------------------------------*/
#pragma mark - Array List Queue
ArrayQueue* DS_Queue_Array_Create(IN const unsigned int nMaxQueueSize)
{
    ArrayQueue          *pQueue = NULL;
    
    SAFEALLOC(pQueue, 1, 32, ArrayQueue);
    if(NULL == pQueue)
        return NULL;
    
    pQueue->pList = DS_List_Array_Create(nMaxQueueSize);
    if(NULL == pQueue->pList)
        return NULL;
    
    return pQueue;
}


int DS_Queue_Array_Destroy(IN OUT ArrayQueue **ppQueue)
{
    if(NULL == (*ppQueue))
        return SUCCESS;
    
    DS_List_Array_Destroy(&((*ppQueue)->pList));
    SAFEFREE((*ppQueue));
    
    return SUCCESS;
}


int DS_Queue_Array_Push(IN OUT ArrayQueue *pQueue, IN const int nData)
{
    if(1 == DS_List_Array_IsFull((const ArrayList *)(pQueue->pList)))
        return FAIL;
    
    if(FAIL == DS_List_Array_Insert(pQueue->pList, nData, LIST_DIR_TAIL, NULL))
        return FAIL;
    
    return SUCCESS;
}


int DS_Queue_Array_Pop(IN OUT ArrayQueue *pQueue, OUT int *pData)
{
    if(1 == DS_List_Array_IsEmpty((const ArrayList *)(pQueue->pList)))
        return FAIL;
    
    if(FAIL == DS_List_Array_DeleteFromDir(pQueue->pList, LIST_DIR_HEAD, pData))
        return FAIL;
    
    return SUCCESS;
}


int DS_Queue_Array_Peek(IN const ArrayQueue *pQueue, OUT int *pData)
{
    if(1 == DS_List_Array_IsEmpty((const ArrayList *)(pQueue->pList)))
        return FAIL;
    
    if(FAIL == DS_List_Array_PeekFromDir(pQueue->pList, LIST_DIR_HEAD, pData))
        return FAIL;
    
    return SUCCESS;
}


#pragma mark - Node List Priority Queue
int DS_Queue_Priority_Array_Push(IN OUT ArrayQueue *pQueue, IN const int nData, IN const fpCompData CompData)
{
    if(1 == DS_List_Array_IsFull((const ArrayList *)(pQueue->pList)))
        return FAIL;
    
    if(FAIL == DS_List_Array_Insert(pQueue->pList, nData, LIST_DIR_INVALID, CompData))
        return FAIL;
    
    return SUCCESS;
}



#pragma mark - Node List Queue
NodeQueue* DS_Queue_Node_Create(void)
{
    NodeQueue          *pQueue = NULL;
    
    SAFEALLOC(pQueue, 1, 32, NodeQueue);
    if(NULL == pQueue)
        return NULL;
    
    pQueue->pList = DS_List_NodeD_Create();
    if(NULL == pQueue->pList)
        return NULL;
    
    return pQueue;
}


int DS_Queue_Node_Destroy(IN OUT NodeQueue **ppQueue)
{
    if(NULL == (*ppQueue))
        return SUCCESS;
    
    DS_List_NodeD_Destroy(&((*ppQueue)->pList));
    SAFEFREE((*ppQueue));
    
    return SUCCESS;
}


int DS_Queue_Node_Push(IN OUT NodeQueue *pQueue, IN const int nData)
{
    if(FAIL == DS_List_NodeD_Insert(pQueue->pList, nData, LIST_DIR_TAIL, NULL))
        return FAIL;
    
    return SUCCESS;
}


int DS_Queue_Node_Pop(IN OUT NodeQueue *pQueue, OUT int *pData)
{
    if(1 == DS_List_Node_IsEmpty((const NodeList *)(pQueue->pList)))
        return FAIL;
    
    if(FAIL == DS_List_NodeD_DeleteFromDir(pQueue->pList, LIST_DIR_HEAD, pData))
        return FAIL;
    
    return SUCCESS;
}


int DS_Queue_Node_Peek(IN const NodeQueue *pQueue, OUT int *pData)
{
    if(1 == DS_List_Node_IsEmpty((const NodeList *)(pQueue->pList)))
        return FAIL;
    
    if(FAIL == DS_List_NodeD_PeekFromDir(pQueue->pList, LIST_DIR_HEAD, pData))
        return FAIL;
    
    return SUCCESS;
}



#pragma mark - Node List Priority Queue
int DS_Queue_Priority_Node_Push(IN OUT NodeQueue *pQueue, IN const int nData, IN const fpCompData CompData)
{
    if(FAIL == DS_List_NodeD_Insert(pQueue->pList, nData, LIST_DIR_INVALID, CompData))
        return FAIL;
    
    return SUCCESS;
}


#pragma mark - Queue Common
void DS_Queue_Array_Show(IN const ArrayQueue *pQueue)
{
    DS_List_Array_Show(pQueue->pList);
}


void DS_Queue_Node_Show(IN const NodeQueue *pQueue)
{
    DS_List_Node_Show(pQueue->pList);
}
