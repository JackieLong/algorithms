#pragma once

#ifndef _2_BUBBLESORT_H_
#define _2_BUBBLESORT_H_

#include <functional>
#include "../Macro.h"

NS_ALGORITHM_BEGIN

// 冒泡排序
template<class T>
void bubble_sort( T t[], const int &len, CompFunc comp )
{
    if( len <= 1 )
    {
        return;
    }

    // |---------前---------| |----------后---------—|
    // t[0], ..., t[len-1-i], t[len-i], ..., t[len-1]
    // 一个i循环，就右移了一个最值到“后”中，只需右移len-1个，最后一个自然就是第一个。
    for( int i = 0; i < len - 1; i++ )
    {
        // 前的范围：[0, len - 1 - i]
        for( int j = 0; j < len - 1 - i; j++ )
            if( !comp( t[j], t[j + 1] ) )
            {
                std::swap( t[j], t[j + 1] );
            }
    }
}

NS_ALGORITHM_END

#endif