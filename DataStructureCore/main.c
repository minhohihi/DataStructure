//
//  main.c
//  DataStructureCore
//
//  Created by Maverick on 2017. 2. 9..
//  Copyright © 2017년 Minhohihi. All rights reserved.
//

#include <stdio.h>
#include "DataStructCore.h"

int CompDataBigFirst(const int nSrcData0, const int nSrcData1);
int CompDataSmallFirst(const int nSrcData0, const int nSrcData1);

static void _Test_DS_List(IN const int *pInputData);
static void _Test_DS_Stack(IN const int *pInputData);
static void _Test_DS_Queue(IN const int *pInputData);
static void _Test_DS_Heap(IN const int *pInputData);
static void _Test_DS_Sort(IN const int *pInputData);
static void _Test_DS_BTree(IN const int *pInputData);

#define NUM_OF_DATA             (1000)

int nInputData[NUM_OF_DATA] = {10, 11, 14, 16, 7, 4, 2, 54, 24, 5, 3, 1, -1, -4, -5, 203, 102, 5, 45, 124, -45, -2345, -2312, };
fpCompData pCompFunc = CompDataBigFirst;


int main(int argc, const char * argv[])
{
    _Test_DS_List((const int *)(&nInputData));
    
    _Test_DS_Stack((const int *)(&nInputData));
    
    _Test_DS_Queue((const int *)(&nInputData));
    
    _Test_DS_Heap((const int *)(&nInputData));
    
    _Test_DS_Sort((const int *)(&nInputData));

    _Test_DS_BTree((const int *)(&nInputData));

    return 0;
    
}


static void _Test_DS_BTree(IN const int *pInputData)
{
    void                *pRootBTree = NULL;
    int                 nData[NUM_OF_DATA] = {0, };
    int                 i = 0;
    
    pRootBTree = DS_BTree_Create();
    
    memcpy(&(nData[0]), pInputData, NUM_OF_DATA * sizeof(int));
    for(i=0 ; i<NUM_OF_DATA ; i++)
        DS_BTree_Insert(pRootBTree, nData[i]);

    DS_BTree_DoBalancing(pRootBTree);
    
    for(i=0 ; i<NUM_OF_DATA ; i++)
        DS_BTree_Delete(pRootBTree, nData[i]);

    DS_BTree_Destroy(&pRootBTree);
}


static void _Test_DS_Sort(IN const int *pInputData)
{
    int                 nData[NUM_OF_DATA] = {0, };
    
    printf("\n\n\n\n");
    printf(" ******************************************* \n");
    printf("                 Bubble Sort                 \n");
    printf(" ******************************************* \n");
    memcpy(&(nData[0]), pInputData, NUM_OF_DATA * sizeof(int));
    DS_Sort_BubbleSort(&(nData[0]), NUM_OF_DATA, pCompFunc);
    DS_Sort_ShowData(&(nData[NUM_OF_DATA-100]), 100);


    printf("\n\n\n\n");
    printf(" ******************************************* \n");
    printf("              Selection Sort                 \n");
    printf(" ******************************************* \n");
    memcpy(&(nData[0]), pInputData, NUM_OF_DATA * sizeof(int));
    DS_Sort_SelectionSort(&(nData[0]), NUM_OF_DATA, pCompFunc);
    DS_Sort_ShowData(&(nData[NUM_OF_DATA-100]), 100);


    printf("\n\n\n\n");
    printf(" ******************************************* \n");
    printf("              Insertion Sort                 \n");
    printf(" ******************************************* \n");
    memcpy(&(nData[0]), pInputData, NUM_OF_DATA * sizeof(int));
    DS_Sort_InsertionSort(&(nData[0]), NUM_OF_DATA, pCompFunc);
    DS_Sort_ShowData(&(nData[NUM_OF_DATA-100]), 100);
    

    printf("\n\n\n\n");
    printf(" ******************************************* \n");
    printf("                  Quick Sort                 \n");
    printf(" ******************************************* \n");
    memcpy(&(nData[0]), pInputData, NUM_OF_DATA * sizeof(int));
    DS_Sort_QuickSort(&(nData[0]), NUM_OF_DATA, pCompFunc);
    DS_Sort_ShowData(&(nData[NUM_OF_DATA-100]), 100);
    
    
    //printf("\n\n\n\n");
    //printf(" ******************************************* \n");
    //printf("                  Radix Sort                 \n");
    //printf(" ******************************************* \n");
    //memcpy(&(nData[0]), pInputData, NUM_OF_DATA * sizeof(int));
    //DS_Sort_RadixSort(&(nData[0]), NUM_OF_DATA, 3);
    //DS_Sort_ShowData(&(nData[0]), NUM_OF_DATA);
}


static void _Test_DS_Heap(IN const int *pInputData)
{
    {
        int             i = 0;
        void            *pRootHeap = NULL;
        int             nOutData = 0;
        
        printf("\n\n\n\n");
        printf(" ******************************************* \n");
        printf("                  Max Heap                   \n");
        printf(" ******************************************* \n");
        
        pRootHeap = DS_Heap_Create(20, pCompFunc);
        
        for(i=0 ; i<20 ; i++)
        {
            DS_Heap_Push(pRootHeap, pInputData[i]);
            DS_Heap_ShowData((const void *)pRootHeap);
        }
        
        for(i=0 ; i<20 ; i++)
        {
            DS_Heap_Pop(pRootHeap, &nOutData);
            printf("nOutData:%05d   Remain: ", nOutData);  DS_Heap_ShowData((const void *)pRootHeap);
        }
        
        DS_Heap_Destroy(&pRootHeap);
    }
    
    return;
}


static void _Test_DS_Queue(IN const int *pInputData)
{
    {
        int             i = 0;
        void            *pRootQueue = NULL;
        int             nOutData = 0;
        
        printf("\n\n\n\n");
        printf(" ******************************************* \n");
        printf("          Priority Queue by Array            \n");
        printf(" ******************************************* \n");
        
        pRootQueue = DS_Queue_Create(20);
        
        for(i=0 ; i<20 ; i++)
        {
            DS_Queue_Priority_Push(pRootQueue, pInputData[i], pCompFunc);
            DS_Queue_ShowData((const void *)pRootQueue);
        }
        
        for(i=0 ; i<20 ; i++)
        {
            DS_Queue_Pop(pRootQueue, &nOutData);
            printf("nOutData:%05d   Remain: ", nOutData);  DS_Queue_ShowData((const void *)pRootQueue);
        }
        
        DS_Queue_Destroy(&pRootQueue);
    }

    {
        int             i = 0;
        void            *pRootQueue = NULL;
        int             nOutData = 0;
     
        printf("\n\n\n\n");
        printf(" ******************************************* \n");
        printf("             Queue by Node                   \n");
        printf(" ******************************************* \n");

        pRootQueue = DS_Queue_Create(-1);
        
        for(i=0 ; i<20 ; i++)
        {
            DS_Queue_Push(pRootQueue, pInputData[i]);
            DS_Queue_ShowData((const void *)pRootQueue);
        }
        
        for(i=0 ; i<20 ; i++)
        {
            DS_Queue_Pop(pRootQueue, &nOutData);
            printf("nOutData:%05d   Remain: ", nOutData);  DS_Queue_ShowData((const void *)pRootQueue);
        }
        
        DS_Queue_Destroy(&pRootQueue);
    }

    {
        int             i = 0;
        void            *pRootQueue = NULL;
        int             nOutData = 0;
        
        printf("\n\n\n\n");
        printf(" ******************************************* \n");
        printf("             Queue by Array                  \n");
        printf(" ******************************************* \n");
        
        pRootQueue = DS_Queue_Create(20);
        
        for(i=0 ; i<20 ; i++)
        {
            DS_Queue_Push(pRootQueue, pInputData[i]);
            DS_Queue_ShowData((const void *)pRootQueue);
        }
        
        for(i=0 ; i<20 ; i++)
        {
            DS_Queue_Pop(pRootQueue, &nOutData);
            printf("nOutData:%05d   Remain: ", nOutData);  DS_Queue_ShowData((const void *)pRootQueue);
        }
        
        DS_Queue_Destroy(&pRootQueue);
    }
    
    return;
}


static void _Test_DS_Stack(IN const int *pInputData)
{
    {
        int             i = 0;
        void            *pRootStack = NULL;
        int             nOutData = 0;
        
        printf("\n\n\n\n");
        printf(" ******************************************* \n");
        printf("             Stack by Node                   \n");
        printf(" ******************************************* \n");

        pRootStack = DS_Stack_Create(-1);
        
        for(i=0 ; i<20 ; i++)
        {
            DS_Stack_Push(pRootStack, pInputData[i]);
            DS_Stack_ShowData((const void *)pRootStack);
        }
        
        for(i=0 ; i<20 ; i++)
        {
            DS_Stack_Pop(pRootStack, &nOutData);
            printf("nOutData:%05d   Remain: ", nOutData);  DS_Stack_ShowData((const void *)pRootStack);
        }
        
        
        DS_Stack_Destroy(&pRootStack);
    }

    {
        int             i = 0;
        void            *pRootStack = NULL;
        int             nOutData = 0;
       
        printf("\n\n\n\n");
        printf(" ******************************************* \n");
        printf("             Stack by Array                  \n");
        printf(" ******************************************* \n");
        
        pRootStack = DS_Stack_Create(20);
        
        for(i=0 ; i<20 ; i++)
        {
            DS_Stack_Push(pRootStack, pInputData[i]);
            DS_Stack_ShowData((const void *)pRootStack);
        }
        
        for(i=0 ; i<20 ; i++)
        {
            DS_Stack_Pop(pRootStack, &nOutData);
            printf("nOutData:%05d   Remain: ", nOutData);  DS_Stack_ShowData((const void *)pRootStack);
        }
        
        DS_Stack_Destroy(&pRootStack);
    }
    
    return;
}


static void _Test_DS_List(IN const int *pInputData)
{
    {
        int             i = 0;
        void            *pRootList = NULL;
        int             nOutData = 0;
        
        printf("\n\n\n\n");
        printf(" ******************************************* \n");
        printf("       Double Linked List by Node            \n");
        printf(" ******************************************* \n");
        
        pRootList = DS_List_Create(-1, LIST_TYPE_DOUBLE);
        
        for(i=0 ; i<20 ; i++)
        {
            DS_List_Insert(pRootList, pInputData[i], LIST_DIR_INVALID, pCompFunc);
            DS_List_ShowData((const void *)pRootList);
        }

        for(i=0 ; i<20 ; i++)
        {
            DS_List_DeleteFromDir(pRootList, LIST_DIR_HEAD, &nOutData);
            DS_List_ShowData((const void *)pRootList);
        }
        
        DS_List_Destroy(&pRootList);
    }

    {
        int            i = 0;
        void           *pRootList = NULL;
        
        printf("\n\n\n\n");
        printf(" ******************************************* \n");
        printf("       Single Linked List by Node            \n");
        printf(" ******************************************* \n");

        pRootList = DS_List_Create(-1, LIST_TYPE_SINGLE);
        
        for(i=0 ; i<20 ; i++)
        {
            DS_List_Insert(pRootList, pInputData[i], LIST_DIR_INVALID, pCompFunc);
            DS_List_ShowData((const void *)pRootList);
        }
        
        for(i=0 ; i<20 ; i++)
        {
            //DS_List_DeleteFromDir(pRootList, LIST_DIR_HEAD, &nOutData);
            DS_List_Delete(pRootList, pInputData[i]);
            DS_List_ShowData((const void *)pRootList);
        }
        
        DS_List_Destroy(&pRootList);
    }

    {
        int            i = 0;
        void           *pRootList = NULL;
        
        printf("\n\n\n\n");
        printf(" ******************************************* \n");
        printf("                List by Array                \n");
        printf(" ******************************************* \n");

        pRootList = DS_List_Create(20, LIST_TYPE_ARRAY);
        
        for(i=0 ; i<20 ; i++)
        {
            DS_List_Insert(pRootList, pInputData[i], LIST_DIR_INVALID, pCompFunc);
            DS_List_ShowData((const void *)pRootList);
        }
        
        for(i=0 ; i<20 ; i++)
        {
            //DS_List_DeleteFromDir(pRootList, LIST_DIR_HEAD, &nOutData);
            DS_List_Delete(pRootList, pInputData[i]);
            DS_List_ShowData((const void *)pRootList);
        }

        DS_List_Destroy(&pRootList);
    }
    
    return;
}


int CompDataBigFirst(const int nSrcData0, const int nSrcData1)
{
    if(nSrcData0 == nSrcData1)
        return 0;
    else if(nSrcData0 > nSrcData1)
        return 1;
    else
        return -1;
}


int CompDataSmallFirst(const int nSrcData0, const int nSrcData1)
{
    if(nSrcData0 == nSrcData1)
        return 0;
    else if(nSrcData0 < nSrcData1)
        return 1;
    else
        return -1;
}
