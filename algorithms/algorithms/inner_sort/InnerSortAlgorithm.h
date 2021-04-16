#pragma once

#ifndef _INNERSORT_H_
#define _INNERSORT_H_

#include <iostream>

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

    // 快速排序
    template<class T, class Comp>
    void quick_sort( T t[], const int &len, Comp comp );

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
    int targetIdx = -1;
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
    if( len <= 1 )
    {
        return;
    }
    for( int i = 0; i < len - 1; i++ )
    {
        for( int j = i + 1; j < len; j++ )
        {
            if( comp( t[j], t[j - 1] ) )
            {
                std::swap( t[j], t[j - 1] );
            }
        }
    }
}

template<class T, class Comp>
void InnerSortAlgorithm::shell_sort( T t[], const int &len, Comp comp )
{

}

template<class T, class Comp>
void InnerSortAlgorithm::merge_sort( T t[], const int &len, Comp comp )
{

}

template<class T, class Comp>
void InnerSortAlgorithm::quick_sort( T t[], const int &len, Comp comp )
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
};


#endif
