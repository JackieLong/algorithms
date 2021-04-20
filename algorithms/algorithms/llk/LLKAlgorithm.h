#pragma once

#ifndef _LLKALGORITHM_H_
#define _LLKALGORITHM_H_

#include "../Macro.h"

#include <set>
#include <list>
#include <cassert>
#include <algorithm>
#include <vector>
#include <tuple>
#include <random>
#include <iostream>
#include <functional>

#define ChessPos std::pair<int, int>

#include "../Macro.h"

NS_ALGORITHM_BEGIN

class LLKAlgorithm
{
public:
    // x坐标在棋盘之外，因为连线消除的位置可以通过棋盘之外
    static bool beyondX( const int &x );

    // 同上理
    static bool beyondY( const int &y );

    // 两坐标间的距离值
    static int distance( const int &x1, const int &y1, const int &x2, const int &y2 );

    // 该坐标上是否有棋子，如果是有效棋盘之外，则认为没有棋子
    // 0：没有棋子；非0：有棋子。
    static int isBlocked( const int &x, const int &y );

    // 两坐标位置是否可以直接相连，无需拐角，两种情况：x坐标相同；y坐标相同
    // 注意这两个坐标不一定非要有棋子，仅仅是表示坐标
    static bool turn0Corner_bool( const int &x1, const int &y1, const int &x2, const int &y2 );
    static void turn0Corner_callback( const int &x, const int &y, std::function<void( const int &, const int & )> findOne );
    static void turn0Corner_vertical( const int &x, const int &y, std::function<void( const int &, const int & )> findOne );
    static void turn0Corner_horizontal( const int &x, const int &y, std::function<void( const int &, const int & )> findOne );

    // 两个坐标是否经过一个拐角就能相连。如果相连则返回(x1,y1)到(x2,y2)中间的拐角坐标。
    // 如下：目标棋子是1和2，经过1个拐角相连只能是两条路线：132和142。
    // 132要能连通，其实就是13和32能同时连通，也就转化成了上面的0个拐角相连的情况。
    // 142情况相同。
    // 3 ---------- 2
    // |            |
    // |            |
    // 1 ---------- 4
    // 注意这两个坐标不一定非要有棋子，仅仅是表示坐标
    static ChessPos turn1Corner( const int &x1, const int &y1, const int &x2, const int &y2 );

    // 两个坐标是否经过一个拐角就能相连。
    // 注意这两个坐标不一定非要有棋子，仅仅是表示坐标
    static bool turn1Corner_bool( const int &x1, const int &y1, const int &x2, const int &y2 );

    // 返回两个坐标经过两个拐角相连的路线。比如：
    // ---------------2
    // |              |
    // 3--------------4
    // |              |
    // 1 --------------
    //
    // 1到2经过3、4两个拐角相连。
    // 返回3、4拐角坐标。
    //
    // 类似turn1Corner“降维”原理，将2corner的情况降成1corner的情况。
    // 首先找到与x1,y1坐标直接相连的坐标，设为x3，y3，从x1,y1坐标的四个方向各寻找一个（用于找出最短路径）
    // 然后通过turn1Corner找到x3，y3到x2，y2经过一个拐角相连的拐角坐标。
    // 返回其中距离最短的路线。
    static std::pair<ChessPos, ChessPos> turn2Corner( const int &x1, const int &y1, const int &x2, const int &y2 );

    // 坐标1是否经过两个拐角与坐标2相连。
    static bool turn2Corner_bool( const int &x1, const int &y1, const int &x2, const int &y2 );

    // points为（x1,y1）和（x2,y2）之间的连接路线。
    // points为空，则表示无法连通（2个拐角以内），points的最后一个坐标为x2，y2。
    // 例如 a经过拐角b、c和d相连，则返回b、c、d的坐标。
    static void path( const int &x1, const int &y1, const int &x2, const int &y2, std::vector<ChessPos> points );

    // 判断坐标x1，y1与坐标x2，y2是否连通，通过前面的turn*Corner_bool方法。
    static bool path_bool( const int &x1, const int &y1, const int &x2, const int &y2 );

    // 判断坐标x1，y1与坐标x2，y2是否连通，递归搜索原理。
    // 总结为：水平遍历target的turn0Corner坐标时，则递归遍历每一个turn0Corner坐标的垂直turn0Corner坐标
    //        垂直遍历target的turn0Corner坐标时，则递归遍历每一个turn0Corner坐标的水平turn0Corner坐标
    //        每次垂直和水平的切换，表示拐角+1
    static bool path_bool_1( const int &x1, const int &y1, const int &x2, const int &y2 );

private:

    // 递归遍历函数
    // vertical:    为true，则遍历x1，y1的垂直turn0Corner坐标；反之，为水平turn0Corner坐标。
    // depth:       为递归遍历深度，depth-1为当前拐角数
    // stopFlag:    为true，会终止所有的遍历，一般就表示遍历到了目标坐标
    // callback:    为遍历到一个坐标的回调。
    static void traverse( const int &x1, const int &y1, bool vertical, int depth, const bool &stopFlag, std::function<void( const int &, const int & )> callback );

public:
    const static int WIDTH       = 10;      // 棋盘宽高
    const static int HEIGHT      = 6;
    const static int INVALID_POS = -1;      // 无效坐标值（初始坐标值）
    static int chess[WIDTH * HEIGHT];       // 棋盘布局，初始都是0，非0则代表有棋子在该位置上
};

NS_ALGORITHM_END

#endif