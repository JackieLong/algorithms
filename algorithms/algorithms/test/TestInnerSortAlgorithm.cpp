#include "TestInnerSortAlgorithm.h"
#include "../Algorithm.h"
#include <iostream>
#include <map>
#include <functional>
#include <algorithm>

USING_NS_ALGORITHM;

#define testArray(_name_, _len_,...)                    \
    int _name_[_len_] = {##__VA_ARGS__};                \
    algorithmMap[algorithm]( _name_, _len_, []( const int &a, const int &b ) {return a < b; } );    \
    for( int i = 0; i < _len_; i++ ) {                  \
        printf( "[%d]%d ", i, _name_[i] );              \
    }                                                   \
    std::cout << std::endl << std::endl;                \


void TestInnerSortAlgorithm::test( const Algorithm algorithm )
{
    using T       = int;
    auto compFunc = []( const T & a, const T & b ) {return a < b; };
    auto compFunc_1 = []( const T & a, const T & b ) {return a > b; };

    const int data_size = 100;
    int test_data_size = data_size;
    T a[data_size];
    for( int i = 0; i < data_size; i++ )
    {
        a[i] = i;
    }
    std::random_shuffle( std::begin( a ), std::end( a ) );

    int data_size_array[5] = { 0, 1, 2, 3, data_size };
    for( auto &size : data_size_array )
    {
        switch( algorithm )
        {
            case INSERT:     // ≤Â»Î≈≈–Ú
                insert_sort<T>( a, size, compFunc );
                break;
            case SELECTION:  // —°‘Ò≈≈–Ú
                selection_sort<T>( a, size, compFunc );
                break;
            case BUBBLE:     // √∞≈›≈≈–Ú
                bubble_sort<T>( a, size, compFunc );
                break;
            case SHELL:      // œ£∂˚≈≈–Ú
                shell_sort<T>( a, size, compFunc );
                break;
            case MERGE:      // πÈ≤¢≈≈–Ú
            {
                T tmp[data_size];
                merge_sort<T>( a, tmp, 0, data_size - 1, compFunc );
                break;
            }
            case QUICK:      // øÏÀŸ≈≈–Ú
                quick_sort<T>( a, size, compFunc );
                break;
            case HEAP:       // ∂—≈≈–Ú
                heap_sort<T>( a, size, compFunc_1 );
                break;
            case COUNT:      // º∆ ˝≈≈–Ú
            case BUCKET:     // Õ∞≈≈–Ú
            case BASE:      // ª˘ ˝≈≈–Ú
            default:
                break;
        }

        for( int i = 0; i < size; i++ )
        {
            printf( "[%d]%d ", i, a[i] );
        }
        std::cout << std::endl << std::endl;
    }
}
