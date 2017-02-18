//
//  DataStruct_List.h
//  DataStructureCore
//
//  Created by Maverick on 2017. 2. 9..
//  Copyright © 2017년 Minhohihi. All rights reserved.
//

#ifndef __DATASTRUCT_LIST_H__
#define __DATASTRUCT_LIST_H__

#include    "DataStruct_Misc.h"
#include    "DataStruct_Node.h"

typedef int (*fpCompData)(const int nSrcData0, const int nSrcData1);

typedef enum _ListType
{
    LIST_TYPE_SINGLE            = 0,
    LIST_TYPE_DOUBLE,
    LIST_TYPE_ARRAY,
    LIST_TYPE_INVALIDE,
}ListType;


typedef enum _ListDirection
{
    LIST_DIR_HEAD           = 0,
    LIST_DIR_TAIL,
    LIST_DIR_INVALID,
}ListDirection;


typedef struct _ArrayList
{
    int                 *pData;
    int                 nCurrNumofData;
    int                 nMaxNumofData;
    int                 nHeadIdx;
    int                 nTailIdx;
}ArrayList;


typedef struct _NodeList
{
    Node                *pRoot;
    Node                *pHead;
    Node                *pTail;
    int                 nTotalNumofData;
}NodeList;


typedef union _ListCore
{
    // For Node Based List
    NodeList            pNList;

    // For Array Based List
    ArrayList           pAList;
}ListCore;


typedef struct _List
{
    void                *pListCore;
    ListType            nListType;
}List;


#pragma mark - List
void* DS_List_Create(IN const unsigned int nMaxNumofData, IN const ListType nListType);
int DS_List_Destroy(IN OUT void **ppListHndl);
int DS_List_IsFull(IN const void *pListHndl);
int DS_List_IsEmpty(const void *pListHndl);
int DS_List_Insert(IN OUT void *pListHndl, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData);
int DS_List_Delete(IN OUT void *pListHndl, IN const int nData);
int DS_List_DeleteFromDir(IN OUT void *pListHndl, IN const ListDirection nDir, OUT int *pOutData);
int DS_List_PeekFromDir(IN const void *pListHndl, IN const ListDirection nDir, OUT int *pOutData);
void DS_List_ShowData(IN const void *pListHndl);

#endif /* List_h */
