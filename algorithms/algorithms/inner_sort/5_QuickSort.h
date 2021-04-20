#pragma once

#ifndef _5_QUICKSORT_H_
#define _5_QUICKSORT_H_

#include <functional>
#include "../Macro.h"

NS_ALGORITHM_BEGIN

// øÏÀŸ≈≈–Ú
template<class T>
void quick_sort( T t[], const int &len, CompFunc comp )
{
    quick_sort_n<T>( t, 0, len - 1, comp );
}

template<class T>
void quick_sort_n( T t[], const int &start, const int &end, CompFunc comp )
{
    if( start >= end )
    {
        return;
    }

    std::swap( t[( start + end ) >> 1], t[end] );

    int k = partition<T>( t, start, end - 1, t[end], comp );

    std::swap( t[end], t[k] );

    quick_sort_n<T>( t, start, k - 1, comp );
    quick_sort_n<T>( t, k + 1, end, comp );
}

template<class T>
int partition( T t[], const int &start, const int &end, const T &pivotVal, CompFunc comp )
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

NS_ALGORITHM_END

#endif