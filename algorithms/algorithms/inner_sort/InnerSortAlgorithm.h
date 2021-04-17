#pragma once

#ifndef _INNERSORT_H_
#define _INNERSORT_H_

#include <iostream>
#include <vector>

namespace InnerSortAlgorithm
{
    enum Algorithm
    {
        INSERT,     // 插入排序
        SELECTION,  // 选择排序
        BUBBLE,     // 冒泡排序
        SHELL,      // 希尔排序
        MERGE,      // 归并排序
        QUICK,      // 快速排序
        HEAP,       // 堆排序
        COUNT,      // 计数排序
        BUCKET,     // 桶排序
        BASE        // 基数排序
    };

    // 插入排序
    template<class T, class Comp>
    void insert_sort( T t[], const int &len, Comp comp );

    template<class T, class Comp>
    void insert_sort_n( T t[], const int &len, const int &incr, Comp comp );

    // 选择排序
    template<class T, class Comp>
    void selection_sort( T t[], const int &len, Comp comp );

    // 冒泡排序
    template<class T, class Comp>
    void bubble_sort( T t[], const int &len, Comp comp );

    // 希尔排序
    template<class T, class Comp>
    void shell_sort( T t[], const int &len, Comp comp );

    // 归并排序
    template<class T, class Comp>
    void merge_sort( T t[], const int &len, Comp comp );

    template<class T, class Comp>
    int partition( T t[], const int &start, const int &end, const T &pivotVal, Comp comp );

    int findPivot( const int &start, const int &end );

    // 快速排序
    template<class T, class Comp>
    void quick_sort( T t[], const int &len, Comp comp );

    template<class T, class Comp>
    void quick_sort_n( T t[], const int &start, const int &end, Comp comp );

    // 堆排序
    template<class T, class Comp>
    void heap_sort( T t[], const int &len, Comp comp );

    // 计数排序
    template<class T, class Comp>
    void count_sort( T[], const int &len, Comp comp );

    // 桶排序
    template<class T, class Comp>
    void bucket_sort( T[], const int &len, Comp comp );

    // 基数排序
    template<class T, class Comp>
    void base_sort( T[], const int &len, Comp comp );

};

template<class T, class Comp>
void InnerSortAlgorithm::insert_sort( T t[], const int &len, Comp comp )
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
            std::swap( t[j], t[j - 1] );
        }
    }
}

template<class T, class Comp>
void InnerSortAlgorithm::selection_sort( T t[], const int &len, Comp comp )
{
    if( len <= 1 ) { return; }

    // 用于保存当前找到的最“大”/“小”值的索引，可以减少交换操作
    int targetIdx = -1;

    // |-------前-------| |----------后--------------|
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

    // |---------前---------| |----------后---------—|
    // t[0], ..., t[len-1-i], t[len-i], ..., t[len-1]
    // 一个i循环，就右移了一个最值到“后”中，只需右移len-1个，最后一个自然就是第一个。
    for( int i = 0; i < len - 1; i++ )
    {
        // 前的范围：[0, len - 1 - i]
        for( int j = 0; j < len - 1 - i; j++ )
            if( !comp( t[j], t[j + 1] ) ) { std::swap( t[j], t[j + 1] ); }
    }
}


// *************************************************
// 增量插入排序（插入排序的变型）
// 对下面数列进行插入排序：
// t[incr*0], t[incr*1], t[incr*2], ..., t[incr*n]
// 其中，incr*n<len 且 incr*(n+1)>=len
// *************************************************
template<class T, class Comp>
void InnerSortAlgorithm::insert_sort_n( T t[], const int &len, const int &incr, Comp comp )
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

template<class T, class Comp>
void InnerSortAlgorithm::shell_sort( T t[], const int &len, Comp comp )
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
