//
//  DataStruct_Sort.h
//  DataStructureCore
//
//  Created by Maverick on 2017. 2. 10..
//  Copyright © 2017년 Minhohihi. All rights reserved.
//

#ifndef __DATASTRUCT_SORT_H__
#define __DATASTRUCT_SORT_H__

#include    <stdio.h>
#include    "DataStruct_Misc.h"
#include    "DataStruct_Node.h"
#include    "DataStruct_List.h"
#include    "DataStruct_Queue.h"


int DS_Sort_BubbleSort(IN int *pData, IN const int nNumofData, IN const fpCompData CompData);
int DS_Sort_SelectionSort(IN int *pData, IN const int nNumofData, IN const fpCompData CompData);
int DS_Sort_InsertionSort(IN int *pData, IN const int nNumofData, IN const fpCompData CompData);
int DS_Sort_QuickSort(IN int *pData, IN const int nNumofData, IN const fpCompData CompData);
int DS_Sort_RadixSort(IN int *pData, IN const int nNumofData, IN const int nMaxLen);


void DS_Sort_ShowData(IN const int *pData, IN const int nNumofData);

#endif /* DataStruct_Sort_h */
