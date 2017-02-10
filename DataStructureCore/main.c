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

static void _Test_DS_List_Array(IN const int *pInputData);
static void _Test_DS_List_NodeS(IN const int *pInputData);
static void _Test_DS_List_NodeD(IN const int *pInputData);
static void _Test_DS_Stack_Array(IN const int *pInputData);
static void _Test_DS_Stack_Node(IN const int *pInputData);
static void _Test_DS_Queue_Array(IN const int *pInputData);
static void _Test_DS_Queue_Priority_Array(IN const int *pInputData);
static void _Test_DS_Queue_Node(IN const int *pInputData);
static void _Test_DS_Queue_Priority_Node(IN const int *pInputData);

int nInputData[100] = {10, 11, 14, 16, 7, 4, 2, 54, 24, 5, 3, 1, };
fpCompData pCompFunc = CompDataSmallFirst;


int main(int argc, const char * argv[])
{
    _Test_DS_List_Array((const int *)(&nInputData));
    _Test_DS_List_NodeS((const int *)(&nInputData));
    _Test_DS_List_NodeD((const int *)(&nInputData));
    _Test_DS_Stack_Array((const int *)(&nInputData));
    _Test_DS_Stack_Node((const int *)(&nInputData));
    _Test_DS_Queue_Array((const int *)(&nInputData));
    _Test_DS_Queue_Node((const int *)(&nInputData));
    _Test_DS_Queue_Priority_Node((const int *)(&nInputData));

    return 0;
    
}


static void _Test_DS_Queue_Priority_Node(IN const int *pInputData)
{
    int            i = 0;
    NodeQueue      *pRootQueue = NULL;
    int             nOutData = 0;
    
    printf("\n\n\n\n");
    printf(" ******************************************* \n");
    printf("          Priority Queue by Node             \n");
    printf(" ******************************************* \n");
    
    pRootQueue = DS_Queue_Node_Create();
    
    for(i=0 ; i<12 ; i++)
    {
        DS_Queue_Priority_Node_Push(pRootQueue, pInputData[i], pCompFunc);
        DS_Queue_Node_Show((const NodeQueue *)pRootQueue);
    }
    
    for(i=0 ; i<12 ; i++)
    {
        DS_Queue_Node_Pop(pRootQueue, &nOutData);
        printf("nOutData:%05d   Rest: ", nOutData);  DS_Queue_Node_Show((const NodeQueue *)pRootQueue);
    }
    
    DS_Queue_Node_Destroy(&pRootQueue);
    
    return;
}


static void _Test_DS_Queue_Priority_Array(IN const int *pInputData)
{
    int             i = 0;
    ArrayQueue      *pRootQueue = NULL;
    int             nOutData = 0;
    
    printf("\n\n\n\n");
    printf(" ******************************************* \n");
    printf("          Priority Queue by Array            \n");
    printf(" ******************************************* \n");
    
    pRootQueue = DS_Queue_Array_Create(20);
    
    for(i=0 ; i<12 ; i++)
    {
        DS_Queue_Priority_Array_Push(pRootQueue, pInputData[i], pCompFunc);
        DS_Queue_Array_Show((const ArrayQueue *)pRootQueue);
    }
    
    for(i=0 ; i<12 ; i++)
    {
        DS_Queue_Array_Pop(pRootQueue, &nOutData);
        printf("nOutData:%05d   Rest: ", nOutData);  DS_Queue_Array_Show((const ArrayQueue *)pRootQueue);
    }
    
    DS_Queue_Array_Destroy(&pRootQueue);
    
    return;
}


static void _Test_DS_Queue_Node(IN const int *pInputData)
{
    int             i = 0;
    NodeQueue       *pRootQueue = NULL;
    int             nOutData = 0;
 
    printf("\n\n\n\n");
    printf(" ******************************************* \n");
    printf("             Queue by Node                   \n");
    printf(" ******************************************* \n");

    pRootQueue = DS_Queue_Node_Create();
    
    for(i=0 ; i<12 ; i++)
    {
        DS_Queue_Node_Push(pRootQueue, pInputData[i]);
        DS_Queue_Node_Show((const NodeQueue *)pRootQueue);
    }
    
    for(i=0 ; i<12 ; i++)
    {
        DS_Queue_Node_Pop(pRootQueue, &nOutData);
        printf("nOutData:%05d   Rest: ", nOutData);  DS_Queue_Node_Show((const NodeQueue *)pRootQueue);
    }
    
    DS_Queue_Node_Destroy(&pRootQueue);
    
    return;
}


static void _Test_DS_Queue_Array(IN const int *pInputData)
{
    int            i = 0;
    ArrayQueue      *pRootQueue = NULL;
    int             nOutData = 0;
    
    printf("\n\n\n\n");
    printf(" ******************************************* \n");
    printf("             Queue by Array                  \n");
    printf(" ******************************************* \n");
    
    pRootQueue = DS_Queue_Array_Create(20);
    
    for(i=0 ; i<12 ; i++)
    {
        DS_Queue_Array_Push(pRootQueue, pInputData[i]);
        DS_Queue_Array_Show((const ArrayQueue *)pRootQueue);
    }
    
    for(i=0 ; i<12 ; i++)
    {
        DS_Queue_Array_Pop(pRootQueue, &nOutData);
        printf("nOutData:%05d   Rest: ", nOutData);  DS_Queue_Array_Show((const ArrayQueue *)pRootQueue);
    }
    
    DS_Queue_Array_Destroy(&pRootQueue);
    
    return;
}


static void _Test_DS_Stack_Node(IN const int *pInputData)
{
    int            i = 0;
    NodeStack      *pRootStack = NULL;
    int             nOutData = 0;
    
    printf("\n\n\n\n");
    printf(" ******************************************* \n");
    printf("             Stack by Node                   \n");
    printf(" ******************************************* \n");

    pRootStack = DS_Stack_Node_Create();
    
    for(i=0 ; i<12 ; i++)
    {
        DS_Stack_Node_Push(pRootStack, pInputData[i]);
        DS_Stack_Node_Show((const NodeStack *)pRootStack);
    }
    
    for(i=0 ; i<12 ; i++)
    {
        DS_Stack_Node_Pop(pRootStack, &nOutData);
        printf("nOutData:%05d   Rest: ", nOutData);  DS_Stack_Node_Show((const NodeStack *)pRootStack);
    }
    
    
    DS_Stack_Node_Destroy(&pRootStack);
    
    return;
}


static void _Test_DS_Stack_Array(IN const int *pInputData)
{
    int            i = 0;
    ArrayStack      *pRootStack = NULL;
    int             nOutData = 0;
   
    printf("\n\n\n\n");
    printf(" ******************************************* \n");
    printf("             Stack by Array                  \n");
    printf(" ******************************************* \n");
    
    pRootStack = DS_Stack_Array_Create(20);
    
    for(i=0 ; i<12 ; i++)
    {
        DS_Stack_Array_Push(pRootStack, pInputData[i]);
        DS_Stack_Array_Show((const ArrayStack *)pRootStack);
    }
    
    for(i=0 ; i<12 ; i++)
    {
        DS_Stack_Array_Pop(pRootStack, &nOutData);
        printf("nOutData:%05d   Rest: ", nOutData);  DS_Stack_Array_Show((const ArrayStack *)pRootStack);
    }
    
    DS_Stack_Array_Destroy(&pRootStack);
    
    return;
}


static void _Test_DS_List_NodeD(IN const int *pInputData)
{
    int            i = 0;
    NodeList       *pRootList = NULL;
    int             nOutData = 0;
    
    printf("\n\n\n\n");
    printf(" ******************************************* \n");
    printf("       Double Linked List by Node            \n");
    printf(" ******************************************* \n");
    
    pRootList = DS_List_NodeS_Create();
    
    for(i=0 ; i<12 ; i++)
    {
        DS_List_NodeD_Insert(pRootList, pInputData[i], LIST_DIR_INVALID, pCompFunc);
        DS_List_Node_Show((const NodeList *)pRootList);
    }

    for(i=0 ; i<12 ; i++)
    {
        DS_List_NodeD_DeleteFromDir(pRootList, LIST_DIR_HEAD, &nOutData);
        DS_List_Node_Show((const NodeList *)pRootList);
    }
    
    DS_List_NodeD_Destroy(&pRootList);
    
    return;
}


static void _Test_DS_List_NodeS(IN const int *pInputData)
{
    int            i = 0;
    NodeList        *pRootList = NULL;
    
    printf("\n\n\n\n");
    printf(" ******************************************* \n");
    printf("       Single Linked List by Node            \n");
    printf(" ******************************************* \n");

    pRootList = DS_List_NodeS_Create();
    
    for(i=0 ; i<12 ; i++)
    {
        DS_List_NodeS_Insert(pRootList, pInputData[i], LIST_DIR_INVALID, pCompFunc);
        DS_List_Node_Show((const NodeList *)pRootList);
    }
    
    for(i=0 ; i<12 ; i++)
    {
        DS_List_NodeS_Delete(pRootList, pInputData[i]);
        DS_List_Node_Show((const NodeList *)pRootList);
    }
    
    DS_List_NodeS_Destroy(&pRootList);
    
    return;
}


static void _Test_DS_List_Array(IN const int *pInputData)
{
    int            i = 0;
    ArrayList       *pRootList = NULL;
    
    printf("\n\n\n\n");
    printf(" ******************************************* \n");
    printf("       Single Linked List by Array           \n");
    printf(" ******************************************* \n");

    pRootList = DS_List_Array_Create(20);
    
    for(i=0 ; i<12 ; i++)
    {
        DS_List_Array_Insert(pRootList, pInputData[i], LIST_DIR_INVALID, pCompFunc);
        DS_List_Array_Show((const ArrayList *)pRootList);
    }
    
    for(i=0 ; i<12 ; i++)
    {
        DS_List_Array_Delete(pRootList, pInputData[i]);
        DS_List_Array_Show((const ArrayList *)pRootList);
    }

    DS_List_Array_Destroy(&pRootList);
    
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
    else if(nSrcData0 > nSrcData1)
        return -1;
    else
        return 1;
}
