
#include "TestLLKAlgorithm.h"
#include "../Algorithm.h"
#include <random>
#include <set>

USING_NS_ALGORITHM;

const static int TEST_BLOCK_NUM = 20;
static std::default_random_engine engine;
static std::uniform_int_distribution<int> randX( 0, LLKAlgorithm::WIDTH - 1 );                // 随机非空棋子的x坐标
static std::uniform_int_distribution<int> randY( 0, LLKAlgorithm::HEIGHT - 1 );               // 随机非空棋子的y坐标
static std::uniform_int_distribution<int> randBlock( 0, TEST_BLOCK_NUM - 1 );   // 随机TEST_BLOCK_NUM个棋子中的一个

void TestLLKAlgorithm::randomChess()
{
    for( auto &it : LLKAlgorithm::chess )
    {
        it = 0;
    }         // 置空，重新初始化。

    std::set<ChessPos> blocks;

    for( int i = 0; i < TEST_BLOCK_NUM; )       // 插入TEST_BLOCK_NUM个棋子，位置都随机。
    {
        auto x = randX( engine );
        auto y = randY( engine );
        if( blocks.find( { x, y } ) == blocks.end() )
        {
            blocks.insert( { x, y } );
            LLKAlgorithm::chess[y * LLKAlgorithm::WIDTH + x] = 1;
            i++;
        }
    }
}

void TestLLKAlgorithm::printChess( const int &idx ) // 打印棋盘布局
{
    printf( "%d***********************************************************************\n", idx );
    printf( "    " );
    for( int column = 0; column < LLKAlgorithm::WIDTH; column++ )
    {
        printf( " %d  ", column );
    }
    std::cout << std::endl;
    for( int row = 0; row < LLKAlgorithm::HEIGHT; row++ )
    {
        printf( " %d  ", row );
        for( int column = 0; column < LLKAlgorithm::WIDTH; column++ )
        {
            if( LLKAlgorithm::chess[column + row * LLKAlgorithm::WIDTH] == 0 )
            {
                printf( "--  " );
            }
            else
            {
                printf( " %d  ", LLKAlgorithm::chess[column + row * LLKAlgorithm::WIDTH] );
            }
        }
        std::cout << std::endl;
    }
    printf( "%d***********************************************************************\n", idx );
}

void TestLLKAlgorithm::test_turn0Corner_bool()
{
    for( int chessCount = 0; chessCount < 10; chessCount++ )
    {
        randomChess();

        printChess( chessCount );

        std::vector<int> posBlocks;
        int tmpIdx = 0;
        for( auto &it : LLKAlgorithm::chess )
        {
            if( it != 0 )
            {
                posBlocks.push_back( tmpIdx );
            }
            tmpIdx++;
        }

        for( int randomBlockCount = 0; randomBlockCount < 10; randomBlockCount++ )
        {
            // 循环多次，每次随机两个棋子，找出连接路线。

            auto block1 = posBlocks[randBlock( engine )];   // 随机棋子1
            auto block2 = posBlocks[randBlock( engine )];   // 随机棋子2

            auto block1_x = block1 % LLKAlgorithm::WIDTH;                 // 棋子1的坐标
            auto block1_y = block1 / LLKAlgorithm::WIDTH;

            auto block2_x = block2 % LLKAlgorithm::WIDTH;                 // 棋子2的坐标
            auto block2_y = block2 / LLKAlgorithm::WIDTH;

            bool result = LLKAlgorithm::turn0Corner_bool( block1_x, block1_y, block2_x, block2_y );
            if( result )
            {
                printf( "[%d, %d] and [%d, %d] can be connected with 0 corner.\n", block1_x, block1_y, block2_x, block2_y );
            }
            else
            {
                printf( "[%d, %d] and [%d, %d] can not be connected with 0 corner.\n", block1_x, block1_y, block2_x, block2_y );
            }
        }
    }
}

void TestLLKAlgorithm::test_turn0Corner_callback()
{
    for( int chessCount = 0; chessCount < 10; chessCount++ )
    {
        randomChess();

        printChess( chessCount );

        std::vector<int> posBlocks;
        int tmpIdx = 0;
        for( auto &it : LLKAlgorithm::chess )
        {
            if( it != 0 )
            {
                posBlocks.push_back( tmpIdx );
            }
            tmpIdx++;
        }

        for( int randomBlockCount = 0; randomBlockCount < 10; randomBlockCount++ )
        {
            // 循环多次，每次随机两个棋子，找出连接路线。

            auto block1 = posBlocks[randBlock( engine )];   // 随机棋子1

            auto block1_x = block1 % LLKAlgorithm::WIDTH;                 // 棋子1的坐标
            auto block1_y = block1 / LLKAlgorithm::WIDTH;

            std::vector<ChessPos> targetPoints;
            targetPoints.reserve( 40 );
            LLKAlgorithm::turn0Corner_callback( block1_x, block1_y, [&]( const int &x, const int &y )
            {
                targetPoints.emplace_back( x, y );
            } );

            printf( "points that can be connected with point[%d, %d] are below:", block1_x, block1_y );
            for( auto &it : targetPoints )
            {
                printf( "(%d, %d),  ", it.first, it.second );
            }
            printf( "\n" );
        }
    }
}

void TestLLKAlgorithm::test_turn0Corner_vertical()
{
    for( int chessCount = 0; chessCount < 10; chessCount++ )
    {
        randomChess();

        printChess( chessCount );

        std::vector<int> posBlocks;
        int tmpIdx = 0;
        for( auto &it : LLKAlgorithm::chess )
        {
            if( it != 0 )
            {
                posBlocks.push_back( tmpIdx );
            }
            tmpIdx++;
        }

        for( int randomBlockCount = 0; randomBlockCount < 10; randomBlockCount++ )
        {
            // 循环多次，每次随机两个棋子，找出连接路线。

            auto block1 = posBlocks[randBlock( engine )];   // 随机棋子1

            auto block1_x = block1 % LLKAlgorithm::WIDTH;                 // 棋子1的坐标
            auto block1_y = block1 / LLKAlgorithm::WIDTH;

            std::vector<ChessPos> targetPoints;
            targetPoints.reserve( 40 );
            LLKAlgorithm::turn0Corner_vertical( block1_x, block1_y, [&]( const int &x, const int &y )
            {
                targetPoints.emplace_back( x, y );
            } );

            printf( "points that can be connected with point[%d, %d] vertically are below:", block1_x, block1_y );
            for( auto &it : targetPoints )
            {
                printf( "(%d, %d),  ", it.first, it.second );
            }
            printf( "\n" );
        }
    }
}

void TestLLKAlgorithm::test_turn0Corner_horizontal()
{
    for( int chessCount = 0; chessCount < 10; chessCount++ )
    {
        randomChess();

        printChess( chessCount );

        std::vector<int> posBlocks;
        int tmpIdx = 0;
        for( auto &it : LLKAlgorithm::chess )
        {
            if( it != 0 )
            {
                posBlocks.push_back( tmpIdx );
            }
            tmpIdx++;
        }

        for( int randomBlockCount = 0; randomBlockCount < 10; randomBlockCount++ )
        {
            // 循环多次，每次随机两个棋子，找出连接路线。

            auto block1 = posBlocks[randBlock( engine )];   // 随机棋子1

            auto block1_x = block1 % LLKAlgorithm::WIDTH;                 // 棋子1的坐标
            auto block1_y = block1 / LLKAlgorithm::WIDTH;

            std::vector<ChessPos> targetPoints;
            targetPoints.reserve( 40 );
            LLKAlgorithm::turn0Corner_horizontal( block1_x, block1_y, [&]( const int &x, const int &y )
            {
                targetPoints.emplace_back( x, y );
            } );

            printf( "points that can be connected with point[%d, %d] horizontally are below:", block1_x, block1_y );
            for( auto &it : targetPoints )
            {
                printf( "(%d, %d),  ", it.first, it.second );
            }
            printf( "\n" );
        }
    }
}

void TestLLKAlgorithm::test_turn1Corner()
{
    for( int chessCount = 0; chessCount < 10; chessCount++ )
    {
        randomChess();

        printChess( chessCount );

        std::vector<int> posBlocks;
        int tmpIdx = 0;
        for( auto &it : LLKAlgorithm::chess )
        {
            if( it != 0 )
            {
                posBlocks.push_back( tmpIdx );
            }
            tmpIdx++;
        }

        for( int randomBlockCount = 0; randomBlockCount < 10; randomBlockCount++ )
        {
            // 循环多次，每次随机两个棋子，找出连接路线。

            auto block1 = posBlocks[randBlock( engine )];   // 随机棋子1
            auto block2 = posBlocks[randBlock( engine )];   // 随机棋子2

            auto block1_x = block1 % LLKAlgorithm::WIDTH;                 // 棋子1的坐标
            auto block1_y = block1 / LLKAlgorithm::WIDTH;

            auto block2_x = block2 % LLKAlgorithm::WIDTH;                 // 棋子2的坐标
            auto block2_y = block2 / LLKAlgorithm::WIDTH;

            //if( block1_x == 0 && block1_y == 5 && block2_x == 0 && block2_y == 0 )
            //{
            //    printf( "" );
            //}

            // 找出连接路线
            ChessPos _1corner = LLKAlgorithm::turn1Corner( block1_x, block1_y, block2_x, block2_y );

            if( _1corner.first != LLKAlgorithm::INVALID_POS )
            {
                printf( "chess[%d, %d] and chess[%d, %d] can be connected with 1 corner[%d, %d]",
                        block1_x, block1_y, block2_x, block2_y,
                        _1corner.first, _1corner.second );
                printf( "\n" );
            }
            else
            {
                printf( "chess[%d, %d] and chess[%d, %d] can not be connected with 1 corner.", block1_x, block1_y, block2_x, block2_y );
                printf( "\n" );
            }
        }
    }
}

void TestLLKAlgorithm::test_turn1Corner_bool()
{
    for( int chessCount = 0; chessCount < 10; chessCount++ )
    {
        randomChess();

        printChess( chessCount );

        std::vector<int> posBlocks;
        int tmpIdx = 0;
        for( auto &it : LLKAlgorithm::chess )
        {
            if( it != 0 )
            {
                posBlocks.push_back( tmpIdx );
            }
            tmpIdx++;
        }

        for( int randomBlockCount = 0; randomBlockCount < 10; randomBlockCount++ )
        {
            // 循环多次，每次随机两个棋子，找出连接路线。

            auto block1 = posBlocks[randBlock( engine )];   // 随机棋子1
            auto block2 = posBlocks[randBlock( engine )];   // 随机棋子2

            auto block1_x = block1 % LLKAlgorithm::WIDTH;                 // 棋子1的坐标
            auto block1_y = block1 / LLKAlgorithm::WIDTH;

            auto block2_x = block2 % LLKAlgorithm::WIDTH;                 // 棋子2的坐标
            auto block2_y = block2 / LLKAlgorithm::WIDTH;

            //if( block1_x == 0 && block1_y == 5 && block2_x == 0 && block2_y == 0 )
            //{
            //    printf( "" );
            //}

            // 找出连接路线
            bool result = LLKAlgorithm::turn1Corner_bool( block1_x, block1_y, block2_x, block2_y );

            if( result )
            {
                printf( "chess[%d, %d] and chess[%d, %d] can be connected with 1 corner.",
                        block1_x, block1_y, block2_x, block2_y );
                printf( "\n" );
            }
            else
            {
                printf( "chess[%d, %d] and chess[%d, %d] can not be connected with 1 corner.", block1_x, block1_y, block2_x, block2_y );
                printf( "\n" );
            }
        }
    }
}

void TestLLKAlgorithm::test_turn2Corner()
{
    for( int chessCount = 0; chessCount < 10; chessCount++ )
    {
        randomChess();

        printChess( chessCount );

        std::vector<int> posBlocks;
        int tmpIdx = 0;
        for( auto &it : LLKAlgorithm::chess )
        {
            if( it != 0 )
            {
                posBlocks.push_back( tmpIdx );
            }
            tmpIdx++;
        }

        for( int randomBlockCount = 0; randomBlockCount < 10; randomBlockCount++ )
        {
            // 循环多次，每次随机两个棋子，找出连接路线。

            auto block1 = posBlocks[randBlock( engine )];   // 随机棋子1
            auto block2 = posBlocks[randBlock( engine )];   // 随机棋子2

            auto block1_x = block1 % LLKAlgorithm::WIDTH;                 // 棋子1的坐标
            auto block1_y = block1 / LLKAlgorithm::WIDTH;

            auto block2_x = block2 % LLKAlgorithm::WIDTH;                 // 棋子2的坐标
            auto block2_y = block2 / LLKAlgorithm::WIDTH;

            //if( block1_x == 0 && block1_y == 5 && block2_x == 0 && block2_y == 0 )
            //{
            //    printf( "" );
            //}

            // 找出连接路线
            std::pair<ChessPos, ChessPos> _2corner = LLKAlgorithm::turn2Corner( block1_x, block1_y, block2_x, block2_y );

            if( _2corner.first.first != LLKAlgorithm::INVALID_POS )
            {
                printf( "chess[%d, %d] and chess[%d, %d] can be connected with 2 corners[%d, %d][%d, %d]",
                        block1_x, block1_y, block2_x, block2_y,
                        _2corner.first.first, _2corner.first.second,
                        _2corner.second.first, _2corner.second.second );
                printf( "\n" );
            }
            else
            {
                printf( "chess[%d, %d] and chess[%d, %d] can not be connected with 2 corners.", block1_x, block1_y, block2_x, block2_y );
                printf( "\n" );
            }
        }
    }
}

void TestLLKAlgorithm::test_turn2Corner_bool()
{
    for( int chessCount = 0; chessCount < 10; chessCount++ )
    {
        randomChess();

        printChess( chessCount );

        std::vector<int> posBlocks;
        int tmpIdx = 0;
        for( auto &it : LLKAlgorithm::chess )
        {
            if( it != 0 )
            {
                posBlocks.push_back( tmpIdx );
            }
            tmpIdx++;
        }

        for( int randomBlockCount = 0; randomBlockCount < 10; randomBlockCount++ )
        {
            // 循环多次，每次随机两个棋子，找出连接路线。

            auto block1 = posBlocks[randBlock( engine )];   // 随机棋子1
            auto block2 = posBlocks[randBlock( engine )];   // 随机棋子2

            auto block1_x = block1 % LLKAlgorithm::WIDTH;                 // 棋子1的坐标
            auto block1_y = block1 / LLKAlgorithm::WIDTH;

            auto block2_x = block2 % LLKAlgorithm::WIDTH;                 // 棋子2的坐标
            auto block2_y = block2 / LLKAlgorithm::WIDTH;

            //if( block1_x == 0 && block1_y == 5 && block2_x == 0 && block2_y == 0 )
            //{
            //    printf( "" );
            //}

            // 找出连接路线
            bool result = LLKAlgorithm::turn2Corner_bool( block1_x, block1_y, block2_x, block2_y );

            if( result )
            {
                printf( "chess[%d, %d] and chess[%d, %d] can be connected with 2 corners.", block1_x, block1_y, block2_x, block2_y );
                printf( "\n" );
            }
            else
            {
                printf( "chess[%d, %d] and chess[%d, %d] can not be connected with 2 corners.", block1_x, block1_y, block2_x, block2_y );
                printf( "\n" );
            }
        }
    }
}

void TestLLKAlgorithm::test_path()
{
    for( int chessCount = 0; chessCount < 10; chessCount++ )
    {
        randomChess();

        printChess( chessCount );

        std::vector<int> posBlocks;
        int tmpIdx = 0;
        for( auto &it : LLKAlgorithm::chess )
        {
            if( it != 0 )
            {
                posBlocks.push_back( tmpIdx );
            }
            tmpIdx++;
        }

        for( int randomBlockCount = 0; randomBlockCount < 10; randomBlockCount++ )
        {
            // 循环多次，每次随机两个棋子，找出连接路线。

            auto block1 = posBlocks[randBlock( engine )];   // 随机棋子1
            auto block2 = posBlocks[randBlock( engine )];   // 随机棋子2

            auto block1_x = block1 % LLKAlgorithm::WIDTH;                 // 棋子1的坐标
            auto block1_y = block1 / LLKAlgorithm::WIDTH;

            auto block2_x = block2 % LLKAlgorithm::WIDTH;                 // 棋子2的坐标
            auto block2_y = block2 / LLKAlgorithm::WIDTH;

            //if( block1_x == 0 && block1_y == 5 && block2_x == 0 && block2_y == 0 )
            //{
            //    printf( "" );
            //}

            // 找出连接路线
            std::vector<ChessPos> path;
            path.reserve( 3 );
            LLKAlgorithm::path( block1_x, block1_y, block2_x, block2_y, path );

            if( path.size() == 1 )
            {
                printf( "chess[%d, %d] and chess[%d, %d] can be connected with 0 corner",
                        block1_x, block1_y,
                        block2_x, block2_y );
                printf( "\n" );

            }
            else if( path.size() == 2 )
            {
                printf( "chess[%d, %d] and chess[%d, %d] can be connected with 1 corner[%d, %d]",
                        block1_x, block1_y,
                        block2_x, block2_y,
                        path[0].first, path[0].second );
                printf( "\n" );
            }
            else if( path.size() == 3 )
            {
                printf( "chess[%d, %d] and chess[%d, %d] can be connected with 2 corners[%d, %d][%d, %d]",
                        block1_x, block1_y, block2_x, block2_y,
                        path[0].first, path[0].second,
                        path[1].first, path[1].second );
                printf( "\n" );
            }
            else
            {
                printf( "chess[%d, %d] and chess[%d, %d] can not be connected.", block1_x, block1_y, block2_x, block2_y );
                printf( "\n" );
            }
        }
    }
}

void TestLLKAlgorithm::test_path_bool()
{
    for( int chessCount = 0; chessCount < 10; chessCount++ )
    {
        randomChess();

        printChess( chessCount );

        std::vector<int> posBlocks;
        int tmpIdx = 0;
        for( auto &it : LLKAlgorithm::chess )
        {
            if( it != 0 )
            {
                posBlocks.push_back( tmpIdx );
            }
            tmpIdx++;
        }

        for( int randomBlockCount = 0; randomBlockCount < 10; randomBlockCount++ )
        {
            // 循环多次，每次随机两个棋子，找出连接路线。

            auto block1 = posBlocks[randBlock( engine )];   // 随机棋子1
            auto block2 = posBlocks[randBlock( engine )];   // 随机棋子2

            auto block1_x = block1 % LLKAlgorithm::WIDTH;                 // 棋子1的坐标
            auto block1_y = block1 / LLKAlgorithm::WIDTH;

            auto block2_x = block2 % LLKAlgorithm::WIDTH;                 // 棋子2的坐标
            auto block2_y = block2 / LLKAlgorithm::WIDTH;

            //if( block1_x == 0 && block1_y == 5 && block2_x == 0 && block2_y == 0 )
            //{
            //    printf( "" );
            //}

            bool result = LLKAlgorithm::path_bool( block1_x, block1_y, block2_x, block2_y );

            if( result )
            {
                printf( "chess[%d, %d] and chess[%d, %d] can be connected", block1_x, block1_y, block2_x, block2_y );
                printf( "\n" );
            }
            else
            {
                printf( "chess[%d, %d] and chess[%d, %d] can not be connected.", block1_x, block1_y, block2_x, block2_y );
                printf( "\n" );
            }
        }
    }
}

void TestLLKAlgorithm::test_path_bool_1()
{
    for( int chessCount = 0; chessCount < 10; chessCount++ )
    {
        randomChess();

        printChess( chessCount );

        std::vector<int> posBlocks;
        int tmpIdx = 0;
        for( auto &it : LLKAlgorithm::chess )
        {
            if( it != 0 )
            {
                posBlocks.push_back( tmpIdx );
            }
            tmpIdx++;
        }

        for( int randomBlockCount = 0; randomBlockCount < 10; randomBlockCount++ )
        {
            // 循环多次，每次随机两个棋子，找出连接路线。

            auto block1 = posBlocks[randBlock( engine )];   // 随机棋子1
            auto block2 = posBlocks[randBlock( engine )];   // 随机棋子2

            auto block1_x = block1 % LLKAlgorithm::WIDTH;                 // 棋子1的坐标
            auto block1_y = block1 / LLKAlgorithm::WIDTH;

            auto block2_x = block2 % LLKAlgorithm::WIDTH;                 // 棋子2的坐标
            auto block2_y = block2 / LLKAlgorithm::WIDTH;

            //if( block1_x == 0 && block1_y == 5 && block2_x == 0 && block2_y == 0 )
            //{
            //    printf( "" );
            //}

            bool result = LLKAlgorithm::path_bool_1( block1_x, block1_y, block2_x, block2_y );

            if( result )
            {
                printf( "chess[%d, %d] and chess[%d, %d] can be connected", block1_x, block1_y, block2_x, block2_y );
                printf( "\n" );
            }
            else
            {
                printf( "chess[%d, %d] and chess[%d, %d] can not be connected.", block1_x, block1_y, block2_x, block2_y );
                printf( "\n" );
            }
        }
    }
}