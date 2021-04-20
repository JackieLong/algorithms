#include "LLKAlgorithm.h"

NS_ALGORITHM_BEGIN

int LLKAlgorithm::chess[LLKAlgorithm::WIDTH * LLKAlgorithm::HEIGHT] = { 0 };  // 棋盘布局，初始都是0，非0则代表有棋子在该位置上

bool LLKAlgorithm::turn1Corner_bool( const int &x1, const int &y1, const int &x2, const int &y2 )
{
    if( ( x1 != x2 || y1 != y2 ) )
    {
        const int &corner1X = x1;
        const int &corner1Y = y2;
        const int &corner2X = x2;
        const int &corner2Y = y1;

        if( !isBlocked( corner1X, corner1Y ) &&
                turn0Corner_bool( x1, y1, corner1X, corner1Y ) &&
                turn0Corner_bool( x2, y2, corner1X, corner1Y ) )
        {
            return true;
        }

        if( !isBlocked( corner2X, corner2Y ) &&
                turn0Corner_bool( x1, y1, corner2X, corner2Y ) &&
                turn0Corner_bool( x2, y2, corner2X, corner2Y ) )
        {
            return true;
        }
    }

    return false;
}

std::pair<ChessPos, ChessPos> LLKAlgorithm::turn2Corner( const int &x1, const int &y1, const int &x2, const int &y2 )
{
    std::pair<ChessPos, ChessPos> path;

    path.first.first   = INVALID_POS;
    path.first.second  = INVALID_POS;
    path.second.first  = INVALID_POS;
    path.second.second = INVALID_POS;

    if( ( x1 != x2 || y1 != y2 ) )
    {
        int distanceMin = 0;        // 记录当前已知连通路线的最短距离
        int tmpDistance = 0;
        int tmpX = x1;
        int tmpY = y1;
        bool edgeTry = false;    // 两坐标相连的拐角可能在有效棋盘之外。

        edgeTry = false;
        tmpDistance = 0;
        tmpX = x1;
        tmpY = y1;
        while( !edgeTry && !isBlocked( tmpX, --tmpY ) )     // tmp坐标与坐标1直接相连
        {
            // 遍历坐标1的“下面”（y负方向）与坐标1直接相连的拐角坐标tmp，当tmp与坐标2经过一个拐角pos相连，则停止。
            // 遍历边界：超出有效棋盘坐标还有再试一次（拐角坐标可在棋盘之外）
            // 下面的3个while循环同理，遍历方向是其他3个方向（上、左、右）

            edgeTry = !beyondY( tmpY );
            ChessPos pos = turn1Corner( x2, y2, tmpX, tmpY );  // tmp与坐标2，经过pos拐角相连。
            if( pos.first != INVALID_POS )
            {
                // 计算上面1-3-4-2的距离
                // 1：x1, y1
                // 3：tmpX,tmpY
                // 4：pos
                // 2：x2, y2
                tmpDistance += distance( x1, y1, tmpX, tmpY );
                tmpDistance += distance( tmpX, tmpY, pos.first, pos.second );
                tmpDistance += distance( pos.first, pos.second, x2, y2 );

                distanceMin = tmpDistance;          // 保存当前最短距离，比这更长的，就舍弃
                path.first.first = tmpX;                // 第一个拐角：tmp
                path.first.second = tmpY;
                path.second = pos;     // 第二个拐角：pos
                break;
            }
        }

        edgeTry = false;
        tmpDistance = 0;
        tmpX = x1;
        tmpY = y1;
        while( !edgeTry && !isBlocked( tmpX, ++tmpY ) )
        {
            edgeTry = !beyondY( tmpY );
            ChessPos pos = turn1Corner( x2, y2, tmpX, tmpY );
            if( pos.first != INVALID_POS )
            {
                tmpDistance += distance( x1, y1, tmpX, tmpY );
                tmpDistance += distance( tmpX, tmpY, pos.first, pos.second );
                tmpDistance += distance( pos.first, pos.second, x2, y2 );
                if( distanceMin == 0 || tmpDistance < distanceMin )
                {
                    distanceMin = tmpDistance;
                    path.first.first  = tmpX;
                    path.first.second = tmpY;
                    path.second = pos;
                }
                break;
            }
        }

        edgeTry = false;
        tmpDistance = 0;
        tmpX = x1;
        tmpY = y1;
        while( !edgeTry && !isBlocked( --tmpX, tmpY ) )
        {
            edgeTry = !beyondX( tmpX );
            ChessPos pos = turn1Corner( x2, y2, tmpX, tmpY );
            if( pos.first != INVALID_POS )
            {
                tmpDistance += distance( x1, y1, tmpX, tmpY );
                tmpDistance += distance( tmpX, tmpY, pos.first, pos.second );
                tmpDistance += distance( pos.first, pos.second, x2, y2 );
                if( distanceMin == 0 || tmpDistance < distanceMin )
                {
                    distanceMin = tmpDistance;
                    path.first.first = tmpX;
                    path.first.second = tmpY;
                    path.second = pos;
                }
                break;
            }
        }

        edgeTry = false;
        tmpDistance = 0;
        tmpX = x1;
        tmpY = y1;
        while( !edgeTry && !isBlocked( ++tmpX, tmpY ) )
        {
            edgeTry = !beyondX( tmpX );
            ChessPos pos = turn1Corner( x2, y2, tmpX, tmpY );
            if( pos.first != INVALID_POS )
            {
                tmpDistance += distance( x1, y1, tmpX, tmpY );
                tmpDistance += distance( tmpX, tmpY, pos.first, pos.second );
                tmpDistance += distance( pos.first, pos.second, x2, y2 );
                if( distanceMin == 0 || tmpDistance < distanceMin )
                {
                    distanceMin = tmpDistance;
                    path.first.first  = tmpX;
                    path.first.second = tmpY;
                    path.second = pos;
                }
                break;
            }
        }
    }

    return path;
}

bool LLKAlgorithm::turn2Corner_bool( const int &x1, const int &y1, const int &x2, const int &y2 )
{
    if( ( x1 != x2 || y1 != y2 ) )
    {
        bool edgeTry = false;
        int tmpX = x1;
        int tmpY = y1;
        while( !edgeTry && !isBlocked( tmpX, --tmpY ) )
        {
            edgeTry = !beyondY( tmpY );
            if( turn1Corner_bool( x2, y2, tmpX, tmpY ) )
            {
                return true;
            }
        }

        edgeTry = false;
        tmpX = x1;
        tmpY = y1;
        while( !edgeTry && !isBlocked( tmpX, ++tmpY ) )
        {
            edgeTry = !beyondY( tmpY );
            if( turn1Corner_bool( x2, y2, tmpX, tmpY ) )
            {
                return true;
            }
        }

        edgeTry = false;
        tmpX = x1;
        tmpY = y1;
        while( !edgeTry && !isBlocked( --tmpX, tmpY ) )
        {
            edgeTry = !beyondX( tmpX );
            if( turn1Corner_bool( x2, y2, tmpX, tmpY ) )
            {
                return true;
            }
        }

        edgeTry = false;
        tmpX = x1;
        tmpY = y1;
        while( !edgeTry && !isBlocked( ++tmpX, tmpY ) )
        {
            edgeTry = !beyondX( tmpX );
            if( turn1Corner_bool( x2, y2, tmpX, tmpY ) )
            {
                return true;
            }
        }
    }

    return false;
}

void LLKAlgorithm::path( const int &x1, const int &y1, const int &x2, const int &y2, std::vector<ChessPos> points )
{
    points.clear();

    bool _0corner = LLKAlgorithm::turn0Corner_bool( x1, y1, x2, y2 );
    if( _0corner )
    {
        points.emplace_back( x2, y2 );
    }
    else
    {
        ChessPos _1corner = LLKAlgorithm::turn1Corner( x1, y1, x2, y2 );
        if( _1corner.first != LLKAlgorithm::INVALID_POS )
        {
            points.push_back( _1corner );
            points.emplace_back( x2, y2 );
        }
        else
        {
            std::pair<ChessPos, ChessPos> _2corner = LLKAlgorithm::turn2Corner( x1, y1, x2, y2 );
            if( _2corner.first.first != LLKAlgorithm::INVALID_POS )
            {
                points.push_back( _2corner.first );
                points.push_back( _2corner.second );
                points.emplace_back( x2, y2 );
            }
        }
    }
}

bool LLKAlgorithm::path_bool( const int &x1, const int &y1, const int &x2, const int &y2 )
{
    return turn0Corner_bool( x1, y1, x2, y2 ) || turn1Corner_bool( x1, y1, x2, y2 ) || turn2Corner_bool( x1, y1, x2, y2 );
}


void LLKAlgorithm::traverse( const int &x1, const int &y1, bool vertical, int depth, const bool &stopFlag, std::function<void( const int &, const int & )> callback )
{
    if( !callback || ++depth > 3 || stopFlag ) { return; }

    if( vertical )
    {
        turn0Corner_vertical( x1, y1, [ &, depth]( const int &targetX, const int &targetY )
        {
            callback( targetX, targetY );
            if( stopFlag ) { return; }
            if( !isBlocked( targetX, targetY ) )
            {
                // 只需递归遍历targetX, targetY水平的turn0Corner，垂直的和x1，y1的一样
                traverse( targetX, targetY, false, depth, stopFlag, callback );
            }
        } );
    }
    else
    {
        turn0Corner_horizontal( x1, y1, [ &, depth]( const int &targetX, const int &targetY )
        {
            callback( targetX, targetY );
            if( stopFlag ) { return; }
            if( !isBlocked( targetX, targetY ) )
            {
                // 只需递归遍历targetX, targetY垂直的turn0Corner，水平的和x1，y1的一样
                traverse( targetX, targetY, true, depth, stopFlag, callback );
            }
        } );
    }
}

bool LLKAlgorithm::path_bool_1( const int &x1, const int &y1, const int &x2, const int &y2 )
{
    if( x1 == x2 && y1 == y2 ) { return false; }

    bool gotIt = false;     // 确定x2，y2可在2个拐角之内和x1，y1连通。
    int  depth = 1;         // 递归深度+1，表示拐角+1，depth=1表示0个拐角，depth=3表示2个拐角
    std::set<ChessPos> pointsHistory;   // 记录遍历过的坐标，避免重复

    // 遍历到一个可以和x1，y1在2个拐角之内连通的坐标
    auto callback = [&]( const int &x, const int &y )
    {
        if( gotIt ) { return; }

        if( x == x2 && y == y2 ) { gotIt = true; }  // 遍历到x2，y2，立即终止全部递归遍历

        if( pointsHistory.find( { x, y } ) == pointsHistory.end() )
        {
            pointsHistory.emplace( x, y );
        }
    };

    // 首先，遍历x1，y1的水平turn0Corner坐标
    turn0Corner_horizontal( x1, y1, [ &, depth]( const int &targetX, const int &targetY )
    {
        callback( targetX, targetY );

        // 递归遍历targetX，targetY的垂直turn0Corner坐标
        if( !gotIt && !isBlocked( targetX, targetY ) ) { traverse( targetX, targetY, true, depth, gotIt, callback ); }
    } );

    // 其次，遍历x1，y1的垂直turn0Corner坐标
    turn0Corner_vertical( x1, y1, [ &, depth]( const int &targetX, const int &targetY )
    {
        callback( targetX, targetY );

        // 递归遍历targetX，targetY的水平turn0Corner坐标
        if( !gotIt && !isBlocked( targetX, targetY ) ) { traverse( targetX, targetY, false, depth, gotIt, callback ); }
    } );

    return gotIt;
}

void LLKAlgorithm::turn0Corner_vertical( const int &x, const int &y, std::function<void( const int &, const int & )> findOne )
{
    if( !findOne ) { return; }

    int tmpY = y;
    while( ++tmpY <= HEIGHT )
    {
        if( isBlocked( x, tmpY ) )
        {
            findOne( x, tmpY );
            break;
        }
        findOne( x, tmpY );
    }

    tmpY = y;
    while( --tmpY >= -1 )
    {
        if( isBlocked( x, tmpY ) )
        {
            findOne( x, tmpY );
            break;
        }
        findOne( x, tmpY );
    }
}

void LLKAlgorithm::turn0Corner_horizontal( const int &x, const int &y, std::function<void( const int &, const int & )> findOne )
{
    if( !findOne ) { return; }

    int tmpX = x;
    while( ++tmpX <= WIDTH )
    {
        if( isBlocked( tmpX, y ) )
        {
            findOne( tmpX, y );
            break;
        }
        findOne( tmpX, y );
    }

    tmpX = x;
    while( --tmpX >= -1 )
    {
        if( isBlocked( tmpX, y ) )
        {
            findOne( tmpX, y );
            break;
        }
        findOne( tmpX, y );
    }
}

bool LLKAlgorithm::beyondX( const int &x )
{
    return x >= 0 && x < WIDTH;
}

bool LLKAlgorithm::beyondY( const int &y )
{
    return y >= 0 && y < HEIGHT;
}

int LLKAlgorithm::distance( const int &x1, const int &y1, const int &x2, const int &y2 )
{
    return y1 > y2 ? y1 - y2 : y2 - y1 +
           x1 > x2 ? x1 - x2 : x2 - x1;
}

int LLKAlgorithm::isBlocked( const int &x, const int &y )
{
    if( ( x >= 0 && x < WIDTH ) && ( y >= 0 && y < HEIGHT ) )
    {
        return chess[x + y * WIDTH] == 0 ? 0 : chess[x + y * WIDTH];
    }
    return 0;
}

void LLKAlgorithm::turn0Corner_callback( const int &x, const int &y, std::function<void( const int &, const int & )> findOne )
{
    if( !findOne ) { return; }

    int tmpX = x;
    int tmpY = y;

    tmpY = y;
    while( ++tmpY <= HEIGHT )
    {
        if( isBlocked( x, tmpY ) )
        {
            findOne( x, tmpY );
            break;
        }
        findOne( x, tmpY );
    }

    tmpY = y;
    while( --tmpY >= -1 )
    {
        if( isBlocked( x, tmpY ) )
        {
            findOne( x, tmpY );
            break;
        }
        findOne( x, tmpY );
    }

    tmpX = x;
    while( ++tmpX <= WIDTH )
    {
        if( isBlocked( tmpX, y ) )
        {
            findOne( tmpX, y );
            break;
        }
        findOne( tmpX, y );
    }

    tmpX = x;
    while( --tmpX >= -1 )
    {
        if( isBlocked( tmpX, y ) )
        {
            findOne( tmpX, y );
            break;
        }
        findOne( tmpX, y );
    }
}

bool LLKAlgorithm::turn0Corner_bool( const int &x1, const int &y1, const int &x2, const int &y2 )
{
    bool connected = false;
    if( ( x1 != x2 || y1 != y2 ) )
    {
        if( x1 == x2 )                                              // 两颗棋子在同一行
        {
            const int tmpYMax = std::max( y1, y2 );
            const int tmpYMin = std::min( y1, y2 );
            int       tmpY = tmpYMin;

            while( ++tmpY < tmpYMax && !isBlocked( x1, tmpY ) );    // tmpY坐标移动，直到遇到非空棋子，或者遇到了另一颗目标旗子
            connected = tmpY == tmpYMax;                            // tmpY坐标最后到了另一颗目标棋子，说明之间是没有其他棋子的，也就是可以直接相连
        }
        else if( y1 == y2 )                                         // 两颗棋子在同一列，同上理
        {
            const int tmpXMax = std::max( x1, x2 );
            const int tmpXMin = std::min( x1, x2 );
            int       tmpX = tmpXMin;

            while( ++tmpX < tmpXMax && !isBlocked( tmpX, y1 ) );
            connected = tmpX == tmpXMax;
        }
    }
    return connected;
}

ChessPos LLKAlgorithm::turn1Corner( const int &x1, const int &y1, const int &x2, const int &y2 )
{
    ChessPos corner;
    corner.first = corner.second = INVALID_POS;

    if( ( x1 != x2 || y1 != y2 ) )      // 两个节点是同一点，则认为不相连
    {
        // 下面是两个拐角3和4的坐标
        const int &corner1X = x1;
        const int &corner1Y = y2;
        const int &corner2X = x2;
        const int &corner2Y = y1;

        const bool connected_corner1 = !isBlocked( corner1X, corner1Y ) &&              // 拐角不能有棋子
                                       turn0Corner_bool( x1, y1, corner1X, corner1Y ) &&     // 拐角与（x1,y1）可以直接连通
                                       turn0Corner_bool( x2, y2, corner1X, corner1Y );       // 拐角与（x2,y2）可以直接连通

        const bool connected_corner2 = !isBlocked( corner2X, corner2Y ) &&              // 同上理
                                       turn0Corner_bool( x1, y1, corner2X, corner2Y ) &&
                                       turn0Corner_bool( x2, y2, corner2X, corner2Y );

        // 以下是返回其中一个可连通的拐角坐标
        if( connected_corner1 )
        {
            corner.first  = corner1X;
            corner.second = corner1Y;
        }
        else if( connected_corner2 )
        {
            corner.first  = corner2X;
            corner.second = corner2Y;
        }
    }
    return corner;
}

NS_ALGORITHM_END
