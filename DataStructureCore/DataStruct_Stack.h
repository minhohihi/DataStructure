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

typedef struct _Stack
{
    List                *pList;
}Stack;


#pragma mark - Stack
void* DS_Stack_Create(IN const int nMaxStackSize);
int DS_Stack_Destroy(IN OUT void **ppStackHndl);
int DS_Stack_Push(IN OUT void *pStackHndl, IN const int nData);
int DS_Stack_Pop(IN OUT void *pStackHndl, OUT int *pData);
void DS_Stack_ShowData(IN const void *pStack);


#endif /* Stack_h */
