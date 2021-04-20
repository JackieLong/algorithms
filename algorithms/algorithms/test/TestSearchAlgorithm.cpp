#include "TestSearchAlgorithm.h"
#include "../Algorithm.h"
#include <functional>
#include <algorithm>
#include <map>
#include <random>
#include <iostream>

static std::default_random_engine e;
static std::uniform_int_distribution<int> u( 1, 100 );

void TestSearchAlgorithm::testBinary()
{
    using T = int;

    const int data_size = 100;
    T a[data_size];
    int last = 0;
    int tmpRandomInt = 0;
    for( int i = 0; i < data_size; i++ )
    {
        while( !tmpRandomInt )
        {
            tmpRandomInt = u( e );
        }
        a[i] = last + tmpRandomInt;
        last = a[i];
        tmpRandomInt = 0;
    }

    for( int i = 0; i < data_size; i++ )
    {
        printf( "[%d]%d ", i, a[i] );
    }
    std::cout << std::endl << std::endl;

    static std::uniform_int_distribution<int> randomIndex( 0, data_size );

    int tmpTargetIdx;
    int tmpTarget = 0;
    for( int i = 0; i < 10; i++ )
    {
        tmpTarget = a[randomIndex( e )];
        tmpTargetIdx = Algorithm::binarySearch<T>( a, data_size, tmpTarget, []( const int &a, const int &b ) {return a < b; } );
        printf( "result of searching target(%d) is a[%d] = %d\n", tmpTarget, tmpTargetIdx, a[tmpTargetIdx] );
    }
}

void TestSearchAlgorithm::testBinaryRecur()
{
    using T = int;

    const int data_size = 100;
    T a[data_size];
    int last = 0;
    int tmpRandomInt = 0;
    for( int i = 0; i < data_size; i++ )
    {
        while( !tmpRandomInt )
        {
            tmpRandomInt = u( e );
        }
        a[i] = last + tmpRandomInt;
        last = a[i];
        tmpRandomInt = 0;
    }

    for( int i = 0; i < data_size; i++ )
    {
        printf( "[%d]%d ", i, a[i] );
    }
    std::cout << std::endl << std::endl;

    static std::uniform_int_distribution<int> randomIndex( 0, data_size );

    int tmpTargetIdx;
    int tmpTarget = 0;
    for( int i = 0; i < 10; i++ )
    {
        tmpTarget = a[randomIndex( e )];
        tmpTargetIdx = Algorithm::binarySearch_recur<T>( a, data_size, tmpTarget, []( const int &a, const int &b ) {return a < b; } );
        printf( "result of searching target(%d) is a[%d] = %d\n", tmpTarget, tmpTargetIdx, a[tmpTargetIdx] );
    }
}
