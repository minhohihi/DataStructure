//
//  DataStruct_Heap.h
//  DataStructureCore
//
//  Created by Maverick on 2017. 2. 18..
//  Copyright © 2017년 Minhohihi. All rights reserved.
//

#ifndef __DATASTRUCT_HEAP_H__
#define __DATASTRUCT_HEAP_H__

#include    "DataStruct_Misc.h"
#include    "DataStruct_Node.h"
#include    "DataStruct_List.h"

typedef struct _Heap
{
    int             *pHeapData;
    int             nMaxNumofData;
    int             nTotalNumofData;
    fpCompData      CompData;
}Heap;


void* DS_Heap_Create(IN const int nMaxHeapSize, IN const fpCompData CompData);
int DS_Heap_Destroy(IN OUT void **ppHeapHndl);
int DS_Heap_Push(IN void *pHeapHndl, IN const int nData);
int DS_Heap_Pop(IN void *pHeapHndl, OUT int *pData);
void DS_Heap_ShowData(IN const void *pHeapHndl);

#endif /* DataStruct_Heap_h */
