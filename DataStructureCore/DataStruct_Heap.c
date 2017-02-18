//
//  DataStruct_Heap.c
//  DataStructureCore
//
//  Created by Maverick on 2017. 2. 18..
//  Copyright © 2017년 Minhohihi. All rights reserved.
//


/*----------------------------------------------------------------------------------------
 File Inclusions
 ----------------------------------------------------------------------------------------*/
#include "DataStruct_Heap.h"


/*----------------------------------------------------------------------------------------
 Constant Definitions
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Macro Definitions
 ----------------------------------------------------------------------------------------*/
#define GET_PARENT_IDX(nChildIdx)           (nChildIdx >> 1)
#define GET_LEFT_IDX(nParentIdx)            (nParentIdx << 1)
#define GET_RIGHT_IDX(nParentIdx)           ((nParentIdx << 1) + 1)

/*----------------------------------------------------------------------------------------
 Type Definitions
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Static Function
 ----------------------------------------------------------------------------------------*/
static int _DS_Heap_IsEmpty(IN const Heap *pHeap);
static int _DS_Heap_IsFull(IN const Heap *pHeap);
static int _DS_Heap_GetLocalExtremeIdx(IN const Heap *pHeap, IN const int nIdx);


/*----------------------------------------------------------------------------------------
 Static Variable
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Global Variable
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Function Implementation
 ----------------------------------------------------------------------------------------*/
void* DS_Heap_Create(IN const int nMaxHeapSize, IN const fpCompData CompData)
{
    Heap            *pHeap = NULL;
    
    SAFEALLOC(pHeap, 1, 32, Heap);
    if(NULL == pHeap)
        return NULL;
    
    SAFEALLOC(pHeap->pHeapData, nMaxHeapSize, 32, int);
    
    pHeap->nMaxNumofData = nMaxHeapSize;
    pHeap->nTotalNumofData = 0;
    pHeap->CompData = CompData;
    
    return (void *)pHeap;
}


int DS_Heap_Destroy(IN OUT void **ppHeapHndl)
{
    Heap                **ppHeap = (Heap **)ppHeapHndl;
    
    if(NULL == (*ppHeap))
        return SUCCESS;
    
    SAFEFREE((*ppHeap)->pHeapData);
    SAFEFREE((*ppHeap));
    
    return SUCCESS;
}


int DS_Heap_Push(IN void *pHeapHndl, IN const int nData)
{
    Heap                *pHeap = (Heap *)pHeapHndl;
    
    if((NULL == pHeap) || (1 == _DS_Heap_IsFull(pHeap)))
        return FAIL;

    {
        int             *pHeapData = pHeap->pHeapData;
        int             nIdx = pHeap->nTotalNumofData + 1;
        
        while(1 != nIdx)
        {
            const int   nParantIdx = GET_PARENT_IDX(nIdx);
            
            if(0 < pHeap->CompData(nData, pHeapData[nParantIdx]))
            {
                pHeapData[nIdx] = pHeapData[nParantIdx];
                nIdx = nParantIdx;
            }
            else
                break;
        }
        
        pHeapData[nIdx] = nData;
        pHeap->nTotalNumofData++;
    }

    return SUCCESS;
}


int DS_Heap_Pop(IN void *pHeapHndl, OUT int *pData)
{
    Heap                *pHeap = (Heap *)pHeapHndl;
    
    if((NULL == pHeap) || (1 == _DS_Heap_IsEmpty(pHeap)))
        return FAIL;
    
    *pData = pHeap->pHeapData[1];
    
    {
        int             *pHeapData = pHeap->pHeapData;
        const int       nLastData = pHeapData[pHeap->nTotalNumofData];
        int             nParentIdx = 1;
        int             nChildIdx = 0;
        
        nChildIdx = _DS_Heap_GetLocalExtremeIdx(pHeap, nParentIdx);
        while(nChildIdx)
        {
            if(0 < pHeap->CompData(nLastData, pHeapData[nChildIdx]))
                break;
            
            pHeapData[nParentIdx] = pHeapData[nChildIdx];
            nParentIdx = nChildIdx;
            nChildIdx = _DS_Heap_GetLocalExtremeIdx(pHeap, nParentIdx);
        }
        
        pHeapData[nParentIdx] = nLastData;
        pHeap->nTotalNumofData--;
    }
    
    return SUCCESS;
}


void DS_Heap_ShowData(IN const void *pHeapHndl)
{
    int                 i = 0;
    Heap                *pHeap = (Heap *)pHeapHndl;
    
    if(1 == _DS_Heap_IsEmpty(pHeap))
    {
        printf("List is Empty\n");
        return;
    }
    
    for(i=1 ; i<=pHeap->nTotalNumofData ; i++)
        printf("%d ", pHeap->pHeapData[i]);
    
    printf("\n");
}


static int _DS_Heap_IsEmpty(IN const Heap *pHeap)
{
    if(0 == pHeap->nTotalNumofData)
        return 1;
    else
        return 0;
}


static int _DS_Heap_IsFull(IN const Heap *pHeap)
{
    if(pHeap->nMaxNumofData == pHeap->nTotalNumofData)
        return 1;
    else
        return 0;
}


static int _DS_Heap_GetLocalExtremeIdx(IN const Heap *pHeap, IN const int nIdx)
{
    const int           nLeftChildIdx = GET_LEFT_IDX(nIdx);
    const int           nRightChildIdx = GET_RIGHT_IDX(nIdx);
    
    if(nLeftChildIdx > pHeap->nTotalNumofData)
        return 0;
    else if(nLeftChildIdx == pHeap->nTotalNumofData)
        return nLeftChildIdx;
    else
    {
        const int       *pHeapData = pHeap->pHeapData;
        
        if(0 < pHeap->CompData(pHeapData[nLeftChildIdx], pHeapData[nRightChildIdx]))
            return nLeftChildIdx;
        else
            return nRightChildIdx;
    }
}



