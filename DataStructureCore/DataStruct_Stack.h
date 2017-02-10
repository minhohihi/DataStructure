//
//  DataStruct_Stack.h
//  DataStructureCore
//
//  Created by Maverick on 2017. 2. 9..
//  Copyright © 2017년 Minhohihi. All rights reserved.
//

#ifndef __DATASTRUCT_STACK_H__
#define __DATASTRUCT_STACK_H__

#include    "DataStruct_Misc.h"
#include    "DataStruct_Node.h"
#include    "DataStruct_List.h"

typedef struct _ArrayStack
{
    ArrayList           *pList;
}ArrayStack;


typedef struct _NodeStack
{
    NodeList            *pList;
}NodeStack;


#pragma mark - Array List Stack
ArrayStack* DS_Stack_Array_Create(IN const unsigned int nMaxStackSize);
int DS_Stack_Array_Destroy(IN OUT ArrayStack **ppStack);
int DS_Stack_Array_Push(IN OUT ArrayStack *pStack, IN const int nData);
int DS_Stack_Array_Pop(IN OUT ArrayStack *pStack, OUT int *pData);


#pragma mark - Node List Stack
NodeStack* DS_Stack_Node_Create(void);
int DS_Stack_Node_Destroy(IN OUT NodeStack **ppStack);
int DS_Stack_Node_Push(IN OUT NodeStack *pStack, IN const int nData);
int DS_Stack_Node_Pop(IN OUT NodeStack *pStack, OUT int *pData);
int DS_Stack_Node_Peek(IN const NodeStack *pStack, OUT int *pData);


#pragma mark - Stack Common
void DS_Stack_Array_Show(IN const ArrayStack *pStack);
void DS_Stack_Node_Show(IN const NodeStack *pStack);


#endif /* Stack_h */
