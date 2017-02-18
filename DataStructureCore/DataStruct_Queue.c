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
    Queue               *pQueueHndl = NULL;
    const ListType      nListType = (-1 == nMaxQueueSize) ? LIST_TYPE_DOUBLE : LIST_TYPE_ARRAY;
    
    SAFEALLOC(pQueueHndl, 1, 32, Queue);
    if(NULL == pQueueHndl)
        return NULL;
    
    pQueueHndl->pList = DS_List_Create(nMaxQueueSize, nListType);
    if(NULL == pQueueHndl->pList)
        return NULL;
    
    return (void *)pQueueHndl;
}


int DS_Queue_Destroy(IN OUT void **ppQueueHndl)
{
    Queue               **ppQueue = (Queue **)ppQueueHndl;
    
    if(NULL == (*ppQueue))
        return SUCCESS;
    
    DS_List_Destroy((void **)(&((*ppQueue)->pList)));
    SAFEFREE((*ppQueue));
    
    *ppQueueHndl = NULL;
    
    return SUCCESS;
}


int DS_Queue_Push(IN OUT void *pQueueHndl, IN const int nData)
{
    Queue               *pQueue = (Queue *)pQueueHndl;
    
    if(FAIL == DS_List_Insert(pQueue->pList, nData, LIST_DIR_TAIL, NULL))
        return FAIL;
    
    return SUCCESS;
}


int DS_Queue_Priority_Push(IN OUT Queue *pQueueHndl, IN const int nData, IN const fpCompData CompData)
{
    Queue               *pQueue = (Queue *)pQueueHndl;
    
    if(FAIL == DS_List_Insert(pQueue->pList, nData, LIST_DIR_INVALID, CompData))
        return FAIL;
    
    return SUCCESS;
}


int DS_Queue_Pop(IN OUT void *pQueueHndl, OUT int *pData)
{
    Queue               *pQueue = (Queue *)pQueueHndl;
    
    if(FAIL == DS_List_DeleteFromDir(pQueue->pList, LIST_DIR_HEAD, pData))
        return FAIL;
    
    return SUCCESS;
}


int DS_Queue_Peek(IN const void *pQueueHndl, OUT int *pData)
{
    Queue               *pQueue = (Queue *)pQueueHndl;
    
    if(FAIL == DS_List_PeekFromDir(pQueue->pList, LIST_DIR_HEAD, pData))
        return FAIL;
    
    return SUCCESS;
}


void DS_Queue_ShowData(IN const void *pQueueHndl)
{
    Queue               *pQueue = (Queue *)pQueueHndl;
    
    DS_List_ShowData(pQueue->pList);
}



