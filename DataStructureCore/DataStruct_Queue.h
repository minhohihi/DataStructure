//
//  DataStruct_Queue.h
//  DataStructureCore
//
//  Created by Maverick on 2017. 2. 9..
//  Copyright © 2017년 Minhohihi. All rights reserved.
//

#ifndef __DATASTRUCT_QUEUE_H__
#define __DATASTRUCT_QUEUE_H__

#include    "DataStruct_Misc.h"
#include    "DataStruct_Node.h"
#include    "DataStruct_List.h"

typedef struct _Queue
{
    List                *pList;
}Queue;


void* DS_Queue_Create(IN const int nMaxQueueSize);
int DS_Queue_Destroy(IN OUT void **ppQueueHndl);
int DS_Queue_Push(IN OUT void *pQueueHndl, IN const int nData);
int DS_Queue_Priority_Push(IN OUT Queue *pQueueHndl, IN const int nData, IN const fpCompData CompData);
int DS_Queue_Pop(IN OUT void *pQueueHndl, OUT int *pData);
void DS_Queue_ShowData(IN const void *pQueue);

#endif /* Queue_h */
