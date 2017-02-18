//
//  DataStruct_Stack.c
//  DataStructureCore
//
//  Created by Maverick on 2017. 2. 9..
//  Copyright © 2017년 Minhohihi. All rights reserved.
//


/*----------------------------------------------------------------------------------------
 File Inclusions
 ----------------------------------------------------------------------------------------*/
#include "DataStruct_Stack.h"


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
#pragma mark - Stack
void* DS_Stack_Create(IN const int nMaxStackSize)
{
    Stack               *pStackHndl = NULL;
    const ListType      nListType = (-1 == nMaxStackSize) ? LIST_TYPE_DOUBLE : LIST_TYPE_ARRAY;
    
    SAFEALLOC(pStackHndl, 1, 32, Stack);
    if(NULL == pStackHndl)
        return NULL;
    
    pStackHndl->pList = DS_List_Create(nMaxStackSize, nListType);
    if(NULL == pStackHndl->pList)
        return NULL;
    
    return (void *)pStackHndl;
}


int DS_Stack_Destroy(IN OUT void **ppStackHndl)
{
    Stack               **ppStack = (Stack **)ppStackHndl;
    
    if(NULL == (*ppStack))
        return SUCCESS;
    
    DS_List_Destroy((void **)(&((*ppStack)->pList)));
    SAFEFREE((*ppStack));
    
    *ppStackHndl = NULL;
    
    return SUCCESS;
}


int DS_Stack_Push(IN OUT void *pStackHndl, IN const int nData)
{
    Stack               *pStack = (Stack *)pStackHndl;
    
    if(FAIL == DS_List_Insert(pStack->pList, nData, LIST_DIR_TAIL, NULL))
        return FAIL;
    
    return SUCCESS;
}


int DS_Stack_Pop(IN OUT void *pStackHndl, OUT int *pData)
{
    Stack               *pStack = (Stack *)pStackHndl;
    
    if(FAIL == DS_List_DeleteFromDir(pStack->pList, LIST_DIR_TAIL, pData))
        return FAIL;
    
    return SUCCESS;
}


int DS_Stack_Peek(IN const void *pStackHndl, OUT int *pData)
{
    Stack               *pStack = (Stack *)pStackHndl;
    
    if(FAIL == DS_List_PeekFromDir(pStack->pList, LIST_DIR_TAIL, pData))
        return FAIL;
    
    return SUCCESS;
}


void DS_Stack_ShowData(IN const void *pStackHndl)
{
    Stack               *pStack = (Stack *)pStackHndl;
    
    DS_List_ShowData(pStack->pList);
}
