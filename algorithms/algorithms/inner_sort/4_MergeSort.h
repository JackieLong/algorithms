#pragma once

#ifndef _4_MERGESORT_H_
#define _4_MERGESORT_H_

#include <functional>
#include "../Macro.h"

NS_ALGORITHM_BEGIN

// πÈ≤¢≈≈–Ú
template<class T>
void merge_sort( T t[], T tmp[], const int &start, const int &end, CompFunc comp )
{
    if( start >= end ) { return; }

    int mid = ( start + end ) >> 1;

    merge_sort( t, tmp, start, mid, comp );
    merge_sort( t, tmp, mid + 1, end, comp );

    memcpy( tmp + start, t + start, sizeof( T ) * ( end - start + 1 ) );

    for( int tmpPtrLeft = start, tmpPtrRight = mid + 1, ptr = start;; )
    {
        if( tmpPtrLeft != mid + 1 )
        {
            if( tmpPtrRight == end + 1 || comp( t[tmpPtrLeft], t[tmpPtrRight] ) )
            {
                t[ptr++] = tmp[tmpPtrLeft++];
            }
            else
            {
                t[ptr++] = tmp[tmpPtrRight++];
            }
        }
        else if( tmpPtrRight != end + 1 ) { t[ptr++] = tmp[tmpPtrRight++]; }
        else { break; }
    }
}

NS_ALGORITHM_END

#endif