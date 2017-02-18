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
#include "DataStruct_Sort.h"


/*----------------------------------------------------------------------------------------
 Constant Definitions
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Macro Definitions
 ----------------------------------------------------------------------------------------*/
#define SWAP(a, b)\
                {\
                    int     nTemp = a;\
                    a = b;\
                    b = nTemp;\
                }

/*----------------------------------------------------------------------------------------
 Type Definitions
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Static Function
 ----------------------------------------------------------------------------------------*/
static void _DS_Sort_QuickSortCore(IN int *pData, IN const int nLow, IN const int nHigh, IN const fpCompData CompData);


/*----------------------------------------------------------------------------------------
 Static Variable
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Global Variable
 ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 Function Implementation
 ----------------------------------------------------------------------------------------*/
int DS_Sort_BubbleSort(IN int *pData, IN const int nNumofData, IN const fpCompData CompData)
{
    int             i = 0, j = 0;
    
    if(NULL == pData)
        return FAIL;
    
    for(i=0 ; i<nNumofData ; i++)
    {
        for(j=1 ; j<(nNumofData - i) ; j++)
            if(0 > CompData(pData[j-1], pData[j]))
                SWAP(pData[j-1], pData[j]);
    }
    
    return SUCCESS;
}


int DS_Sort_SelectionSort(IN int *pData, IN const int nNumofData, IN const fpCompData CompData)
{
    int             i = 0, j = 0;
    const int       nFlagData = CompData(1, -1) * 0x7FFFFFFF;
    
    if(NULL == pData)
        return FAIL;
    
    for(i=0 ; i<nNumofData ; i++)
    {
        int         nExtIdx = 0;
        int         nLocalExt = nFlagData;
        
        for(j=0 ; j<(nNumofData - i) ; j++)
        {
            if(0 < CompData(nLocalExt, pData[j]))
            {
                nLocalExt = pData[j];
                nExtIdx = j;
            }
        }
        
        SWAP(pData[nExtIdx], pData[j-1]);
    }
    
    return SUCCESS;
}


int DS_Sort_InsertionSort(IN int *pData, IN const int nNumofData, IN const fpCompData CompData)
{
    int             i = 0, j = 0;
    
    if(NULL == pData)
        return FAIL;
    
    for(i=1 ; i<nNumofData ; i++)
    {
        const int   nCurrVal = pData[i];
        
        j = i;
        while((0 <= --j) && (0 < CompData(nCurrVal, pData[j])))
            pData[j+1] = pData[j];
        
        pData[j+1] = nCurrVal;
    }
    
    return SUCCESS;
}


int DS_Sort_QuickSort(IN int *pData, IN const int nNumofData, IN const fpCompData CompData)
{
    if(NULL == pData)
        return FAIL;
    
    _DS_Sort_QuickSortCore(pData, 0, nNumofData - 1, CompData);
    
    return SUCCESS;
}


int DS_Sort_RadixSort(IN int *pData, IN const int nNumofData, IN const int nMaxLen)
{
    if(NULL == pData)
        return FAIL;
    
    {
        int         i = 0, j = 0;
        int         nModScale = 1;
        void        *pQueue[10] = {NULL, };
        
        for(i=0 ; i<10 ; i++)
            pQueue[i] = DS_Queue_Create(-1);
        
        for(i=0 ; i<nMaxLen ; i++)
        {
            int     nIdx = 0;
            
            for(j=0 ; j<nNumofData ; j++)
                DS_Queue_Push(pQueue[(pData[j] / nModScale) % 10], pData[j]);
            
            for(j=0 ; j<10 ; j++)
                while(DS_Queue_Pop(pQueue[j], &(pData[nIdx])))
                    nIdx++;
            
            nModScale *= 10;
        }

        for(i=0 ; i<10 ; i++)
            DS_Queue_Destroy(&(pQueue[i]));
    }
    
    return SUCCESS;
    
}


void DS_Sort_ShowData(IN const int *pData, IN const int nNumofData)
{
    int             i = 0;
    
    for(i=0 ; i<nNumofData ; i++)
    {
        if((0 == (i%10)) && (0 != i))
            printf("\n");
        
        printf("%03d ", pData[i]);
    }
    printf("\n\n");

}


static void _DS_Sort_QuickSortCore(IN int *pData, IN const int nLow, IN const int nHigh, IN const fpCompData CompData)
{
    const int   nPivotIdx = (nLow + nHigh) / 2;
    const int   nPivotVal = pData[nPivotIdx];
    int         i = nLow, j = nHigh;
    
    do
    {
        while((i < nHigh) && (0 < CompData(pData[i], nPivotVal)))
            i++;
        
        while((j > nLow) && (0 < CompData(nPivotVal, pData[j])))
            j--;
        
        if(i <= j)
        {
            SWAP(pData[i], pData[j]);
            i++;
            j--;
        }
    }while(i <= j);
    
    if(nLow < j)
        _DS_Sort_QuickSortCore(pData, nLow, j, CompData);
    
    if(i < nHigh)
        _DS_Sort_QuickSortCore(pData, i, nHigh, CompData);
}






