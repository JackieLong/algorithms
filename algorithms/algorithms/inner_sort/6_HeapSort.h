#pragma once

#ifndef _6_HEAPSORT_H_
#define _6_HEAPSORT_H_

#include <functional>
#include <algorithm>
#include <cassert>
#include "../Macro.h"

NS_ALGORITHM_BEGIN

// 堆排序
template<class T>
void heap_sort( T t[], const int &len, CompFunc comp )
{
    Heap<T> heap( t, len, len, comp );      // 建堆（数组存储数据）
    const int &size = heap.size();          // 堆大小

    // 当堆删除完毕时，数组即已经排好序。
    while( size )
    {
        // 将根节点值（当前堆的最大/小值）与堆尾叶节点交换，然后堆大小-1，再对根节点siftdown到合适位置以保证堆结构。
        heap.popRoot( );
    }
}

template<class T>
class Heap
{
public:
    Heap( T t[], const int &data_size, const int &capacity, CompFunc comp );
    ~Heap() = default;

public:
    bool add( const T & );  // 在堆尾加入，siftup到“正确”的位置，以保证堆结构
    void popRoot( );        // 将根节点值（当前堆的最大/小值）与堆尾叶节点交换，然后堆大小-1，再对根节点siftdown到合适位置以保证堆结构。
    const int &size();      // 当前堆数据size，注意不是容量capacity

private:
    int  leftChild( const int &pos );   // pos节点的左子节点在数组中的索引
    int  rightChild( const int &pos );  // pos节点的右子节点在数组中的索引
    int  parent( const int &pos );      // pos节点的父亲节点在数组中的索引
    bool leaf( const int &pos );        // pos是否是叶节点

    void siftup( int pos );             // “上浮”pos节点，以保证pos节点与父节点保持堆结构。
    void siftdown( int pos );           // “下沉”pos节点，以保证pos节点与子节点保持堆结构。

private:
    T*       _dataContainer;            // 用数组存储数据，最高效
    int      _dataSize;                 // 当前堆的数据数量
    int      _capacity;                 // 当前堆的数据容量，即数组大小
    CompFunc _comp;                     // 比较操作函数
};

template<class T>
Algorithm::Heap<T>::Heap( T t[], const int &data_size, const int &capacity, CompFunc comp )
    : _dataContainer( t )
    , _dataSize( data_size )
    , _capacity( capacity )
    , _comp( comp )
{
    assert( capacity >= data_size && comp );    // 参数合法性

    if( data_size <= 1 ) { return; }            // 只有一个元素的堆

    // 最后一个非叶节点开始，往前，挨个siftdown“下沉”，来建立堆结构
    for( int i = ( data_size >> 1 ) - 1; i >= 0; i-- ) { siftdown( i ); }
}

template<class T>
int Algorithm::Heap<T>::parent( const int &pos )
{
    return ( pos - 1 ) >> 1;                    // (n - 1) / 2
}

template<class T>
bool Algorithm::Heap<T>::leaf( const int &pos )
{
    return pos > ( ( _dataSize >> 1 ) - 1 );    // n / 2 - 1
}

template<class T>
int Algorithm::Heap<T>::leftChild( const int &pos )
{
    // 实际上可能没有左子节点
    return ( pos << 1 ) + 1;                    // 2 * n + 1
}

template<class T>
int Algorithm::Heap<T>::rightChild( const int &pos )
{
    // 实际上可能没有右子节点
    return ( pos << 1 ) + 2;                    // 2 * n + 2
}

template<class T>
bool Algorithm::Heap<T>::add( const T &val )
{
    if( _dataSize >= _capacity ) { return false; }  // 空间已满
    _dataContainer[_dataSize++] = val;              // 添加到堆尾
    siftup( _dataContainer[_dataSize - 1] );        // val值所在的节点很有可能破坏了堆结构，需要“上浮”
    return true;
}

template<class T>
void Algorithm::Heap<T>::popRoot()
{
    if( _dataSize <= 0 ) { return; }

    else if( _dataSize == 1 ) { _dataSize--; }

    else
    {
        // 删除根节点，将其交换到堆尾
        std::swap( *_dataContainer, *( _dataContainer + _dataSize-- -1 ) );

        // 根节点是刚刚交换的堆尾节点，需要“下沉”来保证堆结构
        siftdown( 0 );
    }
}

template<class T>
const int &Algorithm::Heap<T>::size()
{
    return _dataSize;
}

template<class T>
void Algorithm::Heap<T>::siftup( int pos )
{
    if( pos >= _dataSize ) { return; }

    int tmpParent = -1;
    while( pos )
    {
        tmpParent = parent( pos );
        if( _comp( _dataContainer[pos], _dataContainer[tmpParent] ) )
        {
            std::swap( _dataContainer[tmpParent], _dataContainer[pos] );
            pos = tmpParent;
        }
        else { break; }
    }
}

template<class T>
void Algorithm::Heap<T>::siftdown( int pos )
{
    while( !leaf( pos ) )
    {
        int _leftChild  = leftChild( pos );
        int _rightChild = rightChild( pos );
        int maxChild    = _leftChild;

        if( _rightChild < _dataSize && _comp( _dataContainer[_rightChild], _dataContainer[_leftChild] ) ) { maxChild = _rightChild; }

        if( _comp( _dataContainer[maxChild], _dataContainer[pos] ) )
        {
            std::swap( _dataContainer[maxChild], _dataContainer[pos] );
            pos = maxChild;
        }
        else { break; }
    }
}

NS_ALGORITHM_END

#endif