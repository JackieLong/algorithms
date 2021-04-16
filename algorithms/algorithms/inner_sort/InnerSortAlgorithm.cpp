#include "InnerSortAlgorithm.h"
#include <functional>
#include <algorithm>
#include <map>

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
    T a[data_size];
    for( int i = 0; i < data_size; i++ )
    {
        a[i] = i;
    }
    std::random_shuffle( std::begin( a ), std::end( a ) );

    algorithmMap[algorithm]( a, data_size, []( const int &a, const int &b ) {return a < b; } );

    for( int i = 0; i < data_size; i++ )
    {
        printf( "[%d]%d ", i, a[i] );
    }
    std::cout << std::endl << std::endl;
}
