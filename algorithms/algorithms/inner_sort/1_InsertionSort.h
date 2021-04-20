#pragma once

#ifndef _1_INSERTIONSORT_H_
#define _1_INSERTIONSORT_H_

#include <functional>
#include "../Macro.h"

NS_ALGORITHM_BEGIN

// 插入排序
template<class T>
void insert_sort( T t[], const int &len, CompFunc comp )
{
    if( len <= 1 ) { return; }

    // 每一次i的循环，就是index=i的数插入到0~i-1已经排好序的数列中。当只有index=0的一个数时，其实就是已经排好序的，因此i从1开始排序
    for( int i = 1; i < len; i++ )
    {
        // j的循环，就是插入方法
        // 循环起始时的t[j]就是末尾index=i那个数。依次比较t[j-1]与t[j]，这里假设以升序排序，
        // 如果t[j-1]>t[j]，那就要交换，再比较t[j-2]与t[j-1]
        // 如果t[j-1]<t[j]，因为j-1之前的已经是排好序的，因此t[j]已经是在正确的位置上了，立即终止循环
        for( int j = i; j > 0 && comp( t[j], t[j - 1] ); j-- )
        {
            //std::swap( t[j], t[j - 1] );
            t[j] ^= t[j - 1] ^= t[j] ^= t[j - 1];
        }
    }
}

NS_ALGORITHM_END

#endif