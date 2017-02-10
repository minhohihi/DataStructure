//
//  DataStruct_Node.h
//  DataStructureCore
//
//  Created by Maverick on 2017. 2. 9..
//  Copyright © 2017년 Minhohihi. All rights reserved.
//

#ifndef __DATASTRUCT_NODE_H__
#define __DATASTRUCT_NODE_H__

#include    <stdio.h>
#include    "DataStruct_Misc.h"

typedef int     Element;


typedef struct _Node        Node;

typedef struct _Node
{
    Element             nData;
    Node                *pLPrev;
    Node                *pRNext;
    Node                *pDirAddr;
}Node;

#endif /* NodeBase_h */
