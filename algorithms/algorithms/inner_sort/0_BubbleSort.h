#pragma once

#ifndef _2_BUBBLESORT_H_
#define _2_BUBBLESORT_H_

#include <functional>
#include "../Macro.h"

NS_ALGORITHM_BEGIN

// ð������
template<class T>
void bubble_sort( T t[], const int &len, CompFunc comp )
{
    if( len <= 1 )
    {
        return;
    }

    // |---------ǰ---------| |----------��---------��|
    // t[0], ..., t[len-1-i], t[len-i], ..., t[len-1]
    // һ��iѭ������������һ����ֵ�������У�ֻ������len-1�������һ����Ȼ���ǵ�һ����
    for( int i = 0; i < len - 1; i++ )
    {
        // ǰ�ķ�Χ��[0, len - 1 - i]
        for( int j = 0; j < len - 1 - i; j++ )
            if( !comp( t[j], t[j + 1] ) )
            {
                std::swap( t[j], t[j + 1] );
            }
    }
}

NS_ALGORITHM_END

#endif