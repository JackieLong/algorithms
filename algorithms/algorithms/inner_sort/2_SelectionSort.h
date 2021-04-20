#pragma once

#ifndef _0_SELECTIONSORT_H_
#define _0_SELECTIONSORT_H_

#include <functional>
#include "../Macro.h"

NS_ALGORITHM_BEGIN

// 选择排序
template<class T>
void selection_sort( T t[], const int &len,CompFunc comp )
{
    if( len <= 1 )
    {
        return;
    }

    // 用于保存当前找到的最“大”/“小”值的索引，可以减少交换操作
    int targetIdx = -1;

    // |-------前-------| |----------后--------------|
    // t[0], ..., t[i-1], t[i], t[i+1], ..., t[len-1]
    for( int i = 0; i < len - 1; i++ )
    {
        targetIdx = i;
        for( int j = i + 1; j < len; j++ )
        {
            if( !comp( t[targetIdx], t[j] ) )
            {
                targetIdx = j;
            }
        }
        if( targetIdx != i )
        {
            std::swap( t[i], t[targetIdx] );
        }
    }
}

NS_ALGORITHM_END

#endif