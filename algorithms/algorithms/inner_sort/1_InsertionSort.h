#pragma once

#ifndef _1_INSERTIONSORT_H_
#define _1_INSERTIONSORT_H_

#include <functional>
#include "../Macro.h"

NS_ALGORITHM_BEGIN

// ��������
template<class T>
void insert_sort( T t[], const int &len, CompFunc comp )
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
            //std::swap( t[j], t[j - 1] );
            t[j] ^= t[j - 1] ^= t[j] ^= t[j - 1];
        }
    }
}

NS_ALGORITHM_END

#endif