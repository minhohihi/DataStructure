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

typedef struct _ArrayQueue
{
    ArrayList           *pList;
}ArrayQueue;


typedef struct _NodeQueue
{
    NodeList            *pList;
}NodeQueue;


#pragma mark - Array List Queue
ArrayQueue* DS_Queue_Array_Create(IN const unsigned int nMaxQueueSize);
int DS_Queue_Array_Destroy(IN OUT ArrayQueue **ppQueue);
int DS_Queue_Array_Push(IN OUT ArrayQueue *pQueue, IN const int nData);
int DS_Queue_Array_Pop(IN OUT ArrayQueue *pQueue, OUT int *pData);


#pragma mark - Node List Priority Queue
int DS_Queue_Priority_Array_Push(IN OUT ArrayQueue *pQueue, IN const int nData, IN const fpCompData CompData);


#pragma mark - Node List Queue
NodeQueue* DS_Queue_Node_Create(void);
int DS_Queue_Node_Destroy(IN OUT NodeQueue **ppQueue);
int DS_Queue_Node_Push(IN OUT NodeQueue *pQueue, IN const int nData);
int DS_Queue_Node_Pop(IN OUT NodeQueue *pQueue, OUT int *pData);
int DS_Queue_Node_Peek(IN const NodeQueue *pQueue, OUT int *pData);


#pragma mark - Node List Priority Queue
int DS_Queue_Priority_Node_Push(IN OUT NodeQueue *pQueue, IN const int nData, IN const fpCompData CompData);


#pragma mark - Queue Common
void DS_Queue_Array_Show(IN const ArrayQueue *pQueue);
void DS_Queue_Node_Show(IN const NodeQueue *pQueue);

#endif /* Queue_h */
