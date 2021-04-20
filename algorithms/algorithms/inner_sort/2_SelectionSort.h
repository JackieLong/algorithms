#pragma once

#ifndef _0_SELECTIONSORT_H_
#define _0_SELECTIONSORT_H_

#include <functional>
#include "../Macro.h"

NS_ALGORITHM_BEGIN

// ѡ������
template<class T>
void selection_sort( T t[], const int &len,CompFunc comp )
{
    if( len <= 1 )
    {
        return;
    }

    // ���ڱ��浱ǰ�ҵ������/��С��ֵ�����������Լ��ٽ�������
    int targetIdx = -1;

    // |-------ǰ-------| |----------��--------------|
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