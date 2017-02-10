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
#pragma mark - Array List Stack
ArrayStack* DS_Stack_Array_Create(IN const unsigned int nMaxStackSize)
{
    ArrayStack          *pStack = NULL;
    
    SAFEALLOC(pStack, 1, 32, ArrayStack);
    if(NULL == pStack)
        return NULL;
    
    pStack->pList = DS_List_Array_Create(nMaxStackSize);
    if(NULL == pStack->pList)
        return NULL;
    
    return pStack;
}


int DS_Stack_Array_Destroy(IN OUT ArrayStack **ppStack)
{
    if(NULL == (*ppStack))
        return SUCCESS;
    
    DS_List_Array_Destroy(&((*ppStack)->pList));
    SAFEFREE((*ppStack));
    
    return SUCCESS;
}


int DS_Stack_Array_Push(IN OUT ArrayStack *pStack, IN const int nData)
{
    if(1 == DS_List_Array_IsFull((const ArrayList *)(pStack->pList)))
        return FAIL;
    
    if(FAIL == DS_List_Array_Insert(pStack->pList, nData, LIST_DIR_TAIL, NULL))
        return FAIL;
    
    return SUCCESS;
}


int DS_Stack_Array_Pop(IN OUT ArrayStack *pStack, OUT int *pData)
{
    if(1 == DS_List_Array_IsEmpty((const ArrayList *)(pStack->pList)))
        return FAIL;

    if(FAIL == DS_List_Array_DeleteFromDir(pStack->pList, LIST_DIR_TAIL, pData))
        return FAIL;
    
    return SUCCESS;
}


int DS_Stack_Array_Peek(IN const ArrayStack *pStack, OUT int *pData)
{
    if(1 == DS_List_Array_IsEmpty((const ArrayList *)(pStack->pList)))
        return FAIL;

    if(FAIL == DS_List_Array_PeekFromDir(pStack->pList, LIST_DIR_TAIL, pData))
        return FAIL;
    
    return SUCCESS;
}



#pragma mark - Node List Stack
NodeStack* DS_Stack_Node_Create(void)
{
    NodeStack          *pStack = NULL;
    
    SAFEALLOC(pStack, 1, 32, NodeStack);
    if(NULL == pStack)
        return NULL;
    
    pStack->pList = DS_List_NodeD_Create();
    if(NULL == pStack->pList)
        return NULL;
    
    return pStack;
}


int DS_Stack_Node_Destroy(IN OUT NodeStack **ppStack)
{
    if(NULL == (*ppStack))
        return SUCCESS;
    
    DS_List_NodeD_Destroy(&((*ppStack)->pList));
    SAFEFREE((*ppStack));
    
    return SUCCESS;
}


int DS_Stack_Node_Push(IN OUT NodeStack *pStack, IN const int nData)
{
    if(FAIL == DS_List_NodeD_Insert(pStack->pList, nData, LIST_DIR_TAIL, NULL))
        return FAIL;
    
    return SUCCESS;
}


int DS_Stack_Node_Pop(IN OUT NodeStack *pStack, OUT int *pData)
{
    if(1 == DS_List_Node_IsEmpty((const NodeList *)(pStack->pList)))
        return FAIL;
    
    if(FAIL == DS_List_NodeD_DeleteFromDir(pStack->pList, LIST_DIR_TAIL, pData))
        return FAIL;
    
    return SUCCESS;
}


int DS_Stack_Node_Peek(IN const NodeStack *pStack, OUT int *pData)
{
    if(1 == DS_List_Node_IsEmpty((const NodeList *)(pStack->pList)))
        return FAIL;

    if(FAIL == DS_List_NodeD_PeekFromDir(pStack->pList, LIST_DIR_TAIL, pData))
        return FAIL;
    
    return SUCCESS;
}



#pragma mark - Stack Common
void DS_Stack_Array_Show(IN const ArrayStack *pStack)
{
    DS_List_Array_Show(pStack->pList);
}


void DS_Stack_Node_Show(IN const NodeStack *pStack)
{
    DS_List_Node_Show(pStack->pList);
}
