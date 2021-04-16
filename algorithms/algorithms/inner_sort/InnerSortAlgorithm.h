#pragma once

#ifndef _INNERSORT_H_
#define _INNERSORT_H_

#include <iostream>

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

    // ��������
    template<class T, class Comp>
    void quick_sort( T t[], const int &len, Comp comp );

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
