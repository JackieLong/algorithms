#pragma once

#ifndef _TOH_H_
#define _TOH_H_

#include <vector>
#include <functional>
#include "../Macro.h"

NS_ALGORITHM_BEGIN

struct Pole
{
    std::vector<int> data;
    int              id;
};

// 汉诺塔算法：
//
// 将柱子start上的圆盘自顶往下n个圆盘，移动到柱子goal，以temp作为“缓冲”柱子。
//
static void TOH( int n, Pole &start, Pole &goal, Pole &temp, std::function<void()> callback )
{
    if( start.data.empty() || n <= 0 ) { return; }      // 盘子为空，移动完毕

    TOH( n - 1, start, temp, goal, callback );          //把n-1个盘子从start移动到temp，goal做缓存的。

    if( !start.data.empty() )
    {
        //上面移动完毕了，goal作为缓存柱子应该已经空了
        //这时start仅剩的最底下的盘子移动到goal上
        goal.data.push_back( start.data.back() );
        start.data.pop_back();
    }

    if( callback ) { callback(); }                      // 打印当前三个柱子的内容

    //上面执行完毕，temp柱子上有n-1个圆盘，start是空的柱子，goal是目标柱子有1个圆盘
    //接下来的工作就是把temp柱子上的圆盘移动到goal柱子上，start柱子作为缓存。
    TOH( n - 1, temp, goal, start, callback );
}

// 汉诺塔算法：
//
// 将柱子start上的圆盘，移动到柱子goal，以temp作为“缓冲”柱子。
//
static void TOH( Pole &start, Pole &goal, Pole &temp )
{
    int maxSize = start.data.size() + 2;
    std::function<void()> printPoleStatus = [&]
    {
        for( int i = 0; i < maxSize; i++ )
        {
            if( start.data.size() < maxSize - i ) { printf( "-  " ); }
            else { printf( "%d  ", start.data[maxSize - i - 1] ); }

            if( goal.data.size() < maxSize - i ) { printf( "-  " ); }
            else { printf( "%d  ", goal.data[maxSize - i - 1] ); }

            if( temp.data.size() < maxSize - i ) { printf( "-  " ); }
            else { printf( "%d  ", temp.data[maxSize - i - 1] ); }

            printf( "\n" );
        }
        printf( "********************************************************\n" );
    };

    TOH( start.data.size(), start, goal, temp, printPoleStatus );
}

NS_ALGORITHM_END

#endif