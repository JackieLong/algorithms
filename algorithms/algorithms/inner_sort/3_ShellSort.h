#pragma once

#ifndef _3_SHELLSORT_H_
#define _3_SHELLSORT_H_

#include <functional>
#include <vector>
#include "../Macro.h"

NS_ALGORITHM_BEGIN

//ϣ������
template<class T>
void shell_sort( T t[], const int &len, CompFunc comp )
{
    // ************************************************************************************
    // ��ȡһϵ�е�incr��������򵥵���������/2�ݼ��������100���������������������£�
    // 50, 25, 12, 6, 3, 1
    // ע�⣬���һ��������1������ͨ�汾�Ĳ������򣬽���һ����ȫ������
    // ************************************************************************************
    std::vector<int> increments;
    increments.reserve( len >> 1 + 1 );
    for( int incr = len >> 1; incr > 0; incr = incr >> 1 )
    {
        increments.push_back( incr );
    }

    for( auto &incr : increments )
    {
        // ������10��������incr=4����ֱ����������н���������������
        // 1��t[0], t[4], t[8]
        // 2��t[1], t[5], t[9]
        // 3��t[2], t[6], t[10]
        // 4��t[3], t[7]
        for( int start = 0; start < incr; start++ )
        {
            insert_sort_n( t + start, len - start, incr, comp );
        }
    }
}

// *************************************************
// �����������򣨲�������ı��ͣ�
// ���������н��в�������
// t[incr*0], t[incr*1], t[incr*2], ..., t[incr*n]
// ���У�incr*n<len �� incr*(n+1)>=len
// *************************************************
template<class T>
void insert_sort_n( T t[], const int &len, const int &incr, CompFunc comp )
{
    // i=incr���൱����ͨ�汾�е�i=1������2����ʼ��
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