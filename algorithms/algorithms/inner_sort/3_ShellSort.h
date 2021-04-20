#pragma once

#ifndef _3_SHELLSORT_H_
#define _3_SHELLSORT_H_

#include <functional>
#include <vector>
#include "../Macro.h"

NS_ALGORITHM_BEGIN

//希尔排序
template<class T>
void shell_sort( T t[], const int &len, CompFunc comp )
{
    // ************************************************************************************
    // 获取一系列的incr增量，最简单的做法就是/2递减，比如对100个数排序，则增量依次如下；
    // 50, 25, 12, 6, 3, 1
    // 注意，最后一个必须是1，即普通版本的插入排序，进行一次完全的排序。
    // ************************************************************************************
    std::vector<int> increments;
    increments.reserve( len >> 1 + 1 );
    for( int incr = len >> 1; incr > 0; incr = incr >> 1 )
    {
        increments.push_back( incr );
    }

    for( auto &incr : increments )
    {
        // 假设有10个数，且incr=4，则分别以下子数列进行增量插入排序：
        // 1、t[0], t[4], t[8]
        // 2、t[1], t[5], t[9]
        // 3、t[2], t[6], t[10]
        // 4、t[3], t[7]
        for( int start = 0; start < incr; start++ )
        {
            insert_sort_n( t + start, len - start, incr, comp );
        }
    }
}

// *************************************************
// 增量插入排序（插入排序的变型）
// 对下面数列进行插入排序：
// t[incr*0], t[incr*1], t[incr*2], ..., t[incr*n]
// 其中，incr*n<len 且 incr*(n+1)>=len
// *************************************************
template<class T>
void insert_sort_n( T t[], const int &len, const int &incr, CompFunc comp )
{
    // i=incr，相当于普通版本中的i=1，即第2个开始。
    for( int i = incr; i < len; i += incr )
    {
        for( int j = i; j >= incr && comp( t[j], t[j - incr] ); j -= incr )
        {
            std::swap( t[j], t[j - incr] );
        }
    }
}

NS_ALGORITHM_END

#endif