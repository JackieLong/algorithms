#pragma once

#ifndef _6_HEAPSORT_H_
#define _6_HEAPSORT_H_

#include <functional>
#include <algorithm>
#include <cassert>
#include "../Macro.h"

NS_ALGORITHM_BEGIN

// ������
template<class T>
void heap_sort( T t[], const int &len, CompFunc comp )
{
    Heap<T> heap( t, len, len, comp );      // ���ѣ�����洢���ݣ�
    const int &size = heap.size();          // �Ѵ�С

    // ����ɾ�����ʱ�����鼴�Ѿ��ź���
    while( size )
    {
        // �����ڵ�ֵ����ǰ�ѵ����/Сֵ�����βҶ�ڵ㽻����Ȼ��Ѵ�С-1���ٶԸ��ڵ�siftdown������λ���Ա�֤�ѽṹ��
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
    bool add( const T & );  // �ڶ�β���룬siftup������ȷ����λ�ã��Ա�֤�ѽṹ
    void popRoot( );        // �����ڵ�ֵ����ǰ�ѵ����/Сֵ�����βҶ�ڵ㽻����Ȼ��Ѵ�С-1���ٶԸ��ڵ�siftdown������λ���Ա�֤�ѽṹ��
    const int &size();      // ��ǰ������size��ע�ⲻ������capacity

private:
    int  leftChild( const int &pos );   // pos�ڵ�����ӽڵ��������е�����
    int  rightChild( const int &pos );  // pos�ڵ�����ӽڵ��������е�����
    int  parent( const int &pos );      // pos�ڵ�ĸ��׽ڵ��������е�����
    bool leaf( const int &pos );        // pos�Ƿ���Ҷ�ڵ�

    void siftup( int pos );             // ���ϸ���pos�ڵ㣬�Ա�֤pos�ڵ��븸�ڵ㱣�ֶѽṹ��
    void siftdown( int pos );           // ���³���pos�ڵ㣬�Ա�֤pos�ڵ����ӽڵ㱣�ֶѽṹ��

private:
    T*       _dataContainer;            // ������洢���ݣ����Ч
    int      _dataSize;                 // ��ǰ�ѵ���������
    int      _capacity;                 // ��ǰ�ѵ������������������С
    CompFunc _comp;                     // �Ƚϲ�������
};

template<class T>
Algorithm::Heap<T>::Heap( T t[], const int &data_size, const int &capacity, CompFunc comp )
    : _dataContainer( t )
    , _dataSize( data_size )
    , _capacity( capacity )
    , _comp( comp )
{
    assert( capacity >= data_size && comp );    // �����Ϸ���

    if( data_size <= 1 ) { return; }            // ֻ��һ��Ԫ�صĶ�

    // ���һ����Ҷ�ڵ㿪ʼ����ǰ������siftdown���³������������ѽṹ
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
    // ʵ���Ͽ���û�����ӽڵ�
    return ( pos << 1 ) + 1;                    // 2 * n + 1
}

template<class T>
int Algorithm::Heap<T>::rightChild( const int &pos )
{
    // ʵ���Ͽ���û�����ӽڵ�
    return ( pos << 1 ) + 2;                    // 2 * n + 2
}

template<class T>
bool Algorithm::Heap<T>::add( const T &val )
{
    if( _dataSize >= _capacity ) { return false; }  // �ռ�����
    _dataContainer[_dataSize++] = val;              // ��ӵ���β
    siftup( _dataContainer[_dataSize - 1] );        // valֵ���ڵĽڵ���п����ƻ��˶ѽṹ����Ҫ���ϸ���
    return true;
}

template<class T>
void Algorithm::Heap<T>::popRoot()
{
    if( _dataSize <= 0 ) { return; }

    else if( _dataSize == 1 ) { _dataSize--; }

    else
    {
        // ɾ�����ڵ㣬���佻������β
        std::swap( *_dataContainer, *( _dataContainer + _dataSize-- -1 ) );

        // ���ڵ��Ǹոս����Ķ�β�ڵ㣬��Ҫ���³�������֤�ѽṹ
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