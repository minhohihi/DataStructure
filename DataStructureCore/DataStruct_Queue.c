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
#pragma mark - Queue
void* DS_Queue_Create(IN const int nMaxQueueSize)
{
    Queue               *pQueue = NULL;
    const ListType      nListType = (-1 == nMaxQueueSize) ? LIST_TYPE_DOUBLE : LIST_TYPE_ARRAY;
    
    SAFEALLOC(pQueue, 1, 32, Queue);
    if(NULL == pQueue)
        return NULL;
    
    pQueue->pList = DS_List_Create(nMaxQueueSize, nListType);
    if(NULL == pQueue->pList)
        return NULL;
    
    return (void *)pQueue;
}


int DS_Queue_Destroy(IN OUT void **ppQueueHndl)
{
    Queue               **ppQueue = (Queue **)ppQueueHndl;
    
    if(NULL == (*ppQueue))
        return SUCCESS;
    
    DS_List_Destroy((void **)(&((*ppQueue)->pList)));
    SAFEFREE((*ppQueue));
    
    return SUCCESS;
}


int DS_Queue_Push(IN OUT void *pQueueHndl, IN const int nData)
{
    Queue               *pQueue = (Queue *)pQueueHndl;
    
    if(1 == DS_List_IsFull((const List *)(pQueue->pList)))
        return FAIL;
    
    if(FAIL == DS_List_Insert(pQueue->pList, nData, LIST_DIR_TAIL, NULL))
        return FAIL;
    
    return SUCCESS;
}


int DS_Queue_Priority_Push(IN OUT Queue *pQueueHndl, IN const int nData, IN const fpCompData CompData)
{
    Queue               *pQueue = (Queue *)pQueueHndl;
    
    if(1 == DS_List_IsFull((const void *)(pQueue->pList)))
        return FAIL;
    
    if(FAIL == DS_List_Insert(pQueue->pList, nData, LIST_DIR_INVALID, CompData))
        return FAIL;
    
    return SUCCESS;
}


int DS_Queue_Pop(IN OUT void *pQueueHndl, OUT int *pData)
{
    Queue               *pQueue = (Queue *)pQueueHndl;
    
    if(1 == DS_List_IsEmpty((const List *)(pQueue->pList)))
        return FAIL;
    
    if(FAIL == DS_List_DeleteFromDir(pQueue->pList, LIST_DIR_HEAD, pData))
        return FAIL;
    
    return SUCCESS;
}


int DS_Queue_Peek(IN const void *pQueueHndl, OUT int *pData)
{
    Queue               *pQueue = (Queue *)pQueueHndl;
    
    if(1 == DS_List_IsEmpty((const List *)(pQueue->pList)))
        return FAIL;
    
    if(FAIL == DS_List_PeekFromDir(pQueue->pList, LIST_DIR_HEAD, pData))
        return FAIL;
    
    return SUCCESS;
}


void DS_Queue_ShowData(IN const void *pQueueHndl)
{
    Queue               *pQueue = (Queue *)pQueueHndl;
    
    DS_List_ShowData(pQueue->pList);
}



