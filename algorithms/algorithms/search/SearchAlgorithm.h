#pragma once

#ifndef _SEARCHALGORITHM_H_
#define _SEARCHALGORITHM_H_

namespace SearchAlgorithm
{
    enum Algorithm
    {
        Binary,
        Binary_Recur,
    };

    // ≤∞Î≤È’“À„∑®£®—≠ª∑∞Ê£©
    template<class T, class Comp>
    int binarySearch( T t[], const int &data_size, const T &value, Comp comp )
    {
        int start = 0, end = data_size - 1, mid = -1;

        while( start <= end )
        {
            mid = ( start + end ) >> 1;
            if( t[mid] == value ) { return mid; }
            else if( comp( t[mid], value ) ) {  start = mid + 1; }
            else { end = mid - 1; }
        }
        return -1;
    }

    template<class T, class Comp>
    int binarySearch_recur( T t[], const int &data_size, const T &value, Comp comp )
    {
        if( data_size <= 0 ) { return -1; }
        int mid = ( 0 + data_size - 1 ) >> 1;
        if( t[mid] == value ) { return mid; }
        else if( comp( t[mid], value ) ) { return _binarySearch_recur( t, data_size, value, mid + 1, data_size - 1, comp ); }
        else { return _binarySearch_recur( t, data_size, value, 0, mid - 1, comp ); }
    }

    template<class T, class Comp>
    int _binarySearch_recur( T t[], const int &data_size, const T &value, const int &start, const int &end, Comp comp )
    {
        if( start > end ) { return -1; }
        int mid = ( start + end ) >> 1;
        if( t[mid] == value ) { return mid; }
        else if( comp( t[mid], value ) ) { return _binarySearch_recur( t, data_size, value, mid + 1, end, comp ); }
        else { return _binarySearch_recur( t, data_size, value, start, mid - 1, comp ); }
    }

}

class TestSearchAlgorithm
{
    using Algorithm = SearchAlgorithm::Algorithm;

public:
    void test( const Algorithm algorithm );
};

#endif
