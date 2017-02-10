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

typedef enum _NodeType
{
    LIST_NODE_TYPE_SINGLE            = 0,
    LIST_NODE_TYPE_DOUBLE,
    LIST_NODE_TYPE_INVALIDE,
}NodeType;


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


typedef struct _List
{
    NodeList            *pNList;
    ArrayList           *pAList;
    NodeType            nNodeType;
}List;


#pragma mark - Array List
ArrayList* DS_List_Array_Create(IN const unsigned int nMaxNumofData);
int DS_List_Array_Destroy(IN OUT ArrayList **ppList);
int DS_List_Array_IsFull(IN const ArrayList *pList);
int DS_List_Array_IsEmpty(IN const ArrayList *pList);
int DS_List_Array_Insert(IN OUT ArrayList *pList, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData);
int DS_List_Array_Delete(IN OUT ArrayList *pList, IN const int nData);
int DS_List_Array_DeleteFromDir(IN OUT ArrayList *pList, IN const ListDirection nDir, OUT int *pOutData);
int DS_List_Array_PeekFromDir(IN const ArrayList *pList, IN const ListDirection nDir, OUT int *pOutData);


#pragma mark - Node Single List
NodeList* DS_List_NodeS_Create(void);
int DS_List_NodeS_Destroy(IN OUT NodeList **ppList);
int DS_List_NodeS_Insert(IN OUT NodeList *pList, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData);
int DS_List_NodeS_Delete(IN OUT NodeList *pList, IN const int nData);
int DS_List_NodeS_DeleteFromDir(IN OUT NodeList *pList, IN const ListDirection nDir, OUT int *pOutData);
int DS_List_NodeS_PeekFromDir(IN const NodeList *pList, IN const ListDirection nDir, OUT int *pOutData);


#pragma mark - Node Double List
NodeList* DS_List_NodeD_Create(void);
int DS_List_NodeD_Destroy(IN OUT NodeList **ppList);
int DS_List_NodeD_Insert(IN OUT NodeList *pList, IN const int nData, IN const ListDirection nDir, IN const fpCompData CompData);
int DS_List_NodeD_Delete(IN OUT NodeList *pList, IN const int nData);
int DS_List_NodeD_DeleteFromDir(IN OUT NodeList *pList, IN const ListDirection nDir, OUT int *pOutData);
int DS_List_NodeD_PeekFromDir(IN const NodeList *pList, IN const ListDirection nDir, OUT int *pOutData);


#pragma mark - List Common
int DS_List_Node_IsEmpty(IN const NodeList *pList);
void DS_List_Array_Show(IN const ArrayList *pList);
void DS_List_Node_Show(IN const NodeList *pList);


#endif /* List_h */
