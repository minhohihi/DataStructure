//
//  DataStruct_Tree.h
//  DataStructureCore
//
//  Created by Maverick on 2017. 2. 9..
//  Copyright © 2017년 Minhohihi. All rights reserved.
//

#ifndef __DATASTRUCT_TREE_H__
#define __DATASTRUCT_TREE_H__

#include    <stdio.h>
#include    "DataStruct_Misc.h"
#include    "DataStruct_Node.h"
#include    "DataStruct_List.h"

#define DATA        int

typedef struct _BNode BNode;
typedef struct _BNode
{
    BNode           *pLNode;
    BNode           *pRNode;
    DATA            nData;
}BNode;


typedef struct _BTree
{
    BNode           *pVRootNode;
}BTree;


void* DS_BTree_Create(void);
int DS_BTree_Destroy(IN OUT void **ppTreeHndl);
int DS_BTree_Insert(IN OUT void *pTreeHndl, IN const DATA nData);
int DS_BTree_Delete(IN OUT void *pTreeHndl, IN const DATA nData);
int DS_BTree_Search(IN const void *pTreeHndl, IN const DATA nData);
int DS_BTree_DoBalancing(IN OUT void *pTreeHndl);

int DS_BTree_TravelPre(IN const void *pTreeHndl);
int DS_BTree_TravelIn(IN const void *pTreeHndl);
int DS_BTree_TravelPost(IN const void *pTreeHndl);


#endif /* Tree_h */
