#include "InnerSortAlgorithm.h"
#include <functional>
#include <algorithm>
#include <map>
#include <random>

#define testArray(_name_, _len_,...)                 \
    int _name_[_len_] = {##__VA_ARGS__};                         \
    algorithmMap[algorithm]( _name_, _len_, []( const int &a, const int &b ) {return a < b; } );    \
    for( int i = 0; i < _len_; i++ ) {                  \
        printf( "[%d]%d ", i, _name_[i] );              \
    }                                                   \
    std::cout << std::endl << std::endl;                \

int InnerSortAlgorithm::findPivot( const int &start, const int &end )
{
    return ( start + end ) / 2;
}



void TestInnerSortAlgorithm::test( const Algorithm algorithm )
{
    using T = int;
    using Comp = std::function<bool( const int &, const int & )>;

    using SortFunc = std::function<void( int t[], const int &len, Comp shit )>;
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;

    std::map<Algorithm, SortFunc> algorithmMap;
    algorithmMap[Algorithm::INSERT]    = std::bind( &InnerSortAlgorithm::insert_sort<T, Comp>, _1, _2, _3 );
    algorithmMap[Algorithm::SELECTION] = std::bind( &InnerSortAlgorithm::selection_sort<T, Comp>, _1, _2, _3 );
    algorithmMap[Algorithm::BUBBLE]    = std::bind( &InnerSortAlgorithm::bubble_sort<T, Comp>, _1, _2, _3 );
    algorithmMap[Algorithm::SHELL]     = std::bind( &InnerSortAlgorithm::shell_sort<T, Comp>, _1, _2, _3 );
    algorithmMap[Algorithm::MERGE]     = std::bind( &InnerSortAlgorithm::merge_sort<T, Comp>, _1, _2, _3 );
    algorithmMap[Algorithm::QUICK]     = std::bind( &InnerSortAlgorithm::quick_sort<T, Comp>, _1, _2, _3 );
    algorithmMap[Algorithm::HEAP]      = std::bind( &InnerSortAlgorithm::heap_sort<T, Comp>, _1, _2, _3 );
    algorithmMap[Algorithm::COUNT]     = std::bind( &InnerSortAlgorithm::count_sort<T, Comp>, _1, _2, _3 );
    algorithmMap[Algorithm::BUCKET]    = std::bind( &InnerSortAlgorithm::bucket_sort<T, Comp>, _1, _2, _3 );
    algorithmMap[Algorithm::BASE]      = std::bind( &InnerSortAlgorithm::base_sort<T, Comp>, _1, _2, _3 );

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
        algorithmMap[algorithm]( a, size, []( const int &a, const int &b ) {return a < b; } );

        for( int i = 0; i < size; i++ )
        {
            printf( "[%d]%d ", i, a[i] );
        }
        std::cout << std::endl << std::endl;
    }

    testArray( f1, 5, 1, 1, 1, 1, 0 );
    testArray( f2, 5, 1, 0, 1, 1, 0 );

    int fuck[] = {5, 2, 3, 3};
    for( int i = 0; i < 4; i++ )
    {
        printf( "[%d]%d ", i, fuck[i] );
    }
    std::cout << std::endl << std::endl;
    printf( "%d\n", InnerSortAlgorithm::partition<T, Comp>( fuck, 0, 3, 3, []( const int &a, const int &b ) {return a < b; } ) );
    for( int i = 0; i < 4; i++ )
    {
        printf( "[%d]%d ", i, fuck[i] );
    }
    std::cout << std::endl << std::endl;
}



void TestInnerSortAlgorithm::testPartition()
{
}
