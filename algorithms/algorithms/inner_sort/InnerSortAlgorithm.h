#pragma once

#ifndef _INNERSORT_H_
#define _INNERSORT_H_

#include <iostream>
#include <vector>

namespace InnerSortAlgorithm
{
    enum Algorithm
    {
        INSERT,     // ��������
        SELECTION,  // ѡ������
        BUBBLE,     // ð������
        SHELL,      // ϣ������
        MERGE,      // �鲢����
        QUICK,      // ��������
        HEAP,       // ������
        COUNT,      // ��������
        BUCKET,     // Ͱ����
        BASE        // ��������
    };

    // ��������
    template<class T, class Comp>
    void insert_sort( T t[], const int &len, Comp comp );

    template<class T, class Comp>
    void insert_sort_n( T t[], const int &len, const int &incr, Comp comp );

    // ѡ������
    template<class T, class Comp>
    void selection_sort( T t[], const int &len, Comp comp );

    // ð������
    template<class T, class Comp>
    void bubble_sort( T t[], const int &len, Comp comp );

    // ϣ������
    template<class T, class Comp>
    void shell_sort( T t[], const int &len, Comp comp );

    // �鲢����
    template<class T, class Comp>
    void merge_sort( T t[], const int &len, Comp comp );

    template<class T, class Comp>
    int partition( T t[], const int &start, const int &end, const T &pivotVal, Comp comp );

    int findPivot( const int &start, const int &end );

    // ��������
    template<class T, class Comp>
    void quick_sort( T t[], const int &len, Comp comp );

    template<class T, class Comp>
    void quick_sort_n( T t[], const int &start, const int &end, Comp comp );

    // ������
    template<class T, class Comp>
    void heap_sort( T t[], const int &len, Comp comp );

    // ��������
    template<class T, class Comp>
    void count_sort( T[], const int &len, Comp comp );

    // Ͱ����
    template<class T, class Comp>
    void bucket_sort( T[], const int &len, Comp comp );

    // ��������
    template<class T, class Comp>
    void base_sort( T[], const int &len, Comp comp );

};

template<class T, class Comp>
void InnerSortAlgorithm::insert_sort( T t[], const int &len, Comp comp )
{
    if( len <= 1 ) { return; }

    // ÿһ��i��ѭ��������index=i�������뵽0~i-1�Ѿ��ź���������С���ֻ��index=0��һ����ʱ����ʵ�����Ѿ��ź���ģ����i��1��ʼ����
    for( int i = 1; i < len; i++ )
    {
        // j��ѭ�������ǲ��뷽��
        // ѭ����ʼʱ��t[j]����ĩβindex=i�Ǹ��������αȽ�t[j-1]��t[j]�������������������
        // ���t[j-1]>t[j]���Ǿ�Ҫ�������ٱȽ�t[j-2]��t[j-1]
        // ���t[j-1]<t[j]����Ϊj-1֮ǰ���Ѿ����ź���ģ����t[j]�Ѿ�������ȷ��λ�����ˣ�������ֹѭ��
        for( int j = i; j > 0 && comp( t[j], t[j - 1] ); j-- )
        {
            std::swap( t[j], t[j - 1] );
        }
    }
}

template<class T, class Comp>
void InnerSortAlgorithm::selection_sort( T t[], const int &len, Comp comp )
{
    if( len <= 1 ) { return; }

    // ���ڱ��浱ǰ�ҵ������/��С��ֵ�����������Լ��ٽ�������
    int targetIdx = -1;

    // |-------ǰ-------| |----------��--------------|
    // t[0], ..., t[i-1], t[i], t[i+1], ..., t[len-1]
    for( int i = 0; i < len - 1; i++ )
    {
        targetIdx = i;
        for( int j = i + 1; j < len; j++ )
        {
            if( !comp( t[targetIdx], t[j] ) ) { targetIdx = j; }
        }
        if( targetIdx != i ) { std::swap( t[i], t[targetIdx] ); }
    }
}

template<class T, class Comp>
void InnerSortAlgorithm::bubble_sort( T t[], const int &len, Comp comp )
{
    if( len <= 1 ) { return; }

    // |---------ǰ---------| |----------��---------��|
    // t[0], ..., t[len-1-i], t[len-i], ..., t[len-1]
    // һ��iѭ������������һ����ֵ�������У�ֻ������len-1�������һ����Ȼ���ǵ�һ����
    for( int i = 0; i < len - 1; i++ )
    {
        // ǰ�ķ�Χ��[0, len - 1 - i]
        for( int j = 0; j < len - 1 - i; j++ )
            if( !comp( t[j], t[j + 1] ) ) { std::swap( t[j], t[j + 1] ); }
    }
}


// *************************************************
// �����������򣨲�������ı��ͣ�
// ���������н��в�������
// t[incr*0], t[incr*1], t[incr*2], ..., t[incr*n]
// ���У�incr*n<len �� incr*(n+1)>=len
// *************************************************
template<class T, class Comp>
void InnerSortAlgorithm::insert_sort_n( T t[], const int &len, const int &incr, Comp comp )
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

template<class T, class Comp>
void InnerSortAlgorithm::shell_sort( T t[], const int &len, Comp comp )
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

template<class T, class Comp>
void InnerSortAlgorithm::quick_sort( T t[], const int &len, Comp comp )
{
    quick_sort_n<T, Comp>( t, 0, len - 1, comp );
}

template<class T, class Comp>
void InnerSortAlgorithm::quick_sort_n( T t[], const int &start, const int &end, Comp comp )
{
    if( start >= end ) { return; }

    std::swap( t[findPivot( start, end )], t[end] );

    int k = partition<T, Comp>( t, start, end - 1, t[end], comp );

    std::swap( t[end], t[k] );

    quick_sort_n<T, Comp>( t, start, k - 1, comp );
    quick_sort_n<T, Comp>( t, k + 1, end, comp );
}

template<class T, class Comp>
int InnerSortAlgorithm::partition( T t[], const int &start, const int &end, const T &pivotVal, Comp comp )
{
    int tmpStart = start - 1, tmpEnd = end + 1;
    while( true )
    {
        while( ++tmpStart != tmpEnd && comp( t[tmpStart], pivotVal ) );
        while( --tmpEnd != tmpStart && !comp( t[tmpEnd], pivotVal ) );
        if( tmpStart < tmpEnd ) { std::swap( t[tmpStart], t[tmpEnd] ); }
        else { break; }
    }
    return tmpStart;
}

template<class T, class Comp>
void InnerSortAlgorithm::merge_sort( T t[], const int &len, Comp comp )
{

}

template<class T, class Comp>
void InnerSortAlgorithm::heap_sort( T t[], const int &len, Comp comp )
{

}

template<class T, class Comp>
void InnerSortAlgorithm::count_sort( T[], const int &len, Comp comp )
{

}

template<class T, class Comp>
void InnerSortAlgorithm::bucket_sort( T[], const int &len, Comp comp )
{

}

template<class T, class Comp>
void InnerSortAlgorithm::base_sort( T[], const int &len, Comp comp )
{

}

class TestInnerSortAlgorithm
{
    using Algorithm = InnerSortAlgorithm::Algorithm;
public:
    void test( const Algorithm algorithm );
    void testPartition();
};


#endif
