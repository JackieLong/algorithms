#include "LLKAlgorithm.h"

NS_ALGORITHM_BEGIN

int LLKAlgorithm::chess[LLKAlgorithm::WIDTH * LLKAlgorithm::HEIGHT] = { 0 };  // ���̲��֣���ʼ����0����0������������ڸ�λ����

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
        int distanceMin = 0;        // ��¼��ǰ��֪��ͨ·�ߵ���̾���
        int tmpDistance = 0;
        int tmpX = x1;
        int tmpY = y1;
        bool edgeTry = false;    // �����������Ĺսǿ�������Ч����֮�⡣

        edgeTry = false;
        tmpDistance = 0;
        tmpX = x1;
        tmpY = y1;
        while( !edgeTry && !isBlocked( tmpX, --tmpY ) )     // tmp����������1ֱ������
        {
            // ��������1�ġ����桱��y������������1ֱ�������Ĺս�����tmp����tmp������2����һ���ս�pos��������ֹͣ��
            // �����߽磺������Ч�������껹������һ�Σ��ս������������֮�⣩
            // �����3��whileѭ��ͬ����������������3�������ϡ����ң�

            edgeTry = !beyondY( tmpY );
            ChessPos pos = turn1Corner( x2, y2, tmpX, tmpY );  // tmp������2������pos�ս�������
            if( pos.first != INVALID_POS )
            {
                // ��������1-3-4-2�ľ���
                // 1��x1, y1
                // 3��tmpX,tmpY
                // 4��pos
                // 2��x2, y2
                tmpDistance += distance( x1, y1, tmpX, tmpY );
                tmpDistance += distance( tmpX, tmpY, pos.first, pos.second );
                tmpDistance += distance( pos.first, pos.second, x2, y2 );

                distanceMin = tmpDistance;          // ���浱ǰ��̾��룬��������ģ�������
                path.first.first = tmpX;                // ��һ���սǣ�tmp
                path.first.second = tmpY;
                path.second = pos;     // �ڶ����սǣ�pos
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
                // ֻ��ݹ����targetX, targetYˮƽ��turn0Corner����ֱ�ĺ�x1��y1��һ��
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
                // ֻ��ݹ����targetX, targetY��ֱ��turn0Corner��ˮƽ�ĺ�x1��y1��һ��
                traverse( targetX, targetY, true, depth, stopFlag, callback );
            }
        } );
    }
}

bool LLKAlgorithm::path_bool_1( const int &x1, const int &y1, const int &x2, const int &y2 )
{
    if( x1 == x2 && y1 == y2 ) { return false; }

    bool gotIt = false;     // ȷ��x2��y2����2���ս�֮�ں�x1��y1��ͨ��
    int  depth = 1;         // �ݹ����+1����ʾ�ս�+1��depth=1��ʾ0���սǣ�depth=3��ʾ2���ս�
    std::set<ChessPos> pointsHistory;   // ��¼�����������꣬�����ظ�

    // ������һ�����Ժ�x1��y1��2���ս�֮����ͨ������
    auto callback = [&]( const int &x, const int &y )
    {
        if( gotIt ) { return; }

        if( x == x2 && y == y2 ) { gotIt = true; }  // ������x2��y2��������ֹȫ���ݹ����

        if( pointsHistory.find( { x, y } ) == pointsHistory.end() )
        {
            pointsHistory.emplace( x, y );
        }
    };

    // ���ȣ�����x1��y1��ˮƽturn0Corner����
    turn0Corner_horizontal( x1, y1, [ &, depth]( const int &targetX, const int &targetY )
    {
        callback( targetX, targetY );

        // �ݹ����targetX��targetY�Ĵ�ֱturn0Corner����
        if( !gotIt && !isBlocked( targetX, targetY ) ) { traverse( targetX, targetY, true, depth, gotIt, callback ); }
    } );

    // ��Σ�����x1��y1�Ĵ�ֱturn0Corner����
    turn0Corner_vertical( x1, y1, [ &, depth]( const int &targetX, const int &targetY )
    {
        callback( targetX, targetY );

        // �ݹ����targetX��targetY��ˮƽturn0Corner����
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
        if( x1 == x2 )                                              // ����������ͬһ��
        {
            const int tmpYMax = std::max( y1, y2 );
            const int tmpYMin = std::min( y1, y2 );
            int       tmpY = tmpYMin;

            while( ++tmpY < tmpYMax && !isBlocked( x1, tmpY ) );    // tmpY�����ƶ���ֱ�������ǿ����ӣ�������������һ��Ŀ������
            connected = tmpY == tmpYMax;                            // tmpY�����������һ��Ŀ�����ӣ�˵��֮����û���������ӵģ�Ҳ���ǿ���ֱ������
        }
        else if( y1 == y2 )                                         // ����������ͬһ�У�ͬ����
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

    if( ( x1 != x2 || y1 != y2 ) )      // �����ڵ���ͬһ�㣬����Ϊ������
    {
        // �����������ս�3��4������
        const int &corner1X = x1;
        const int &corner1Y = y2;
        const int &corner2X = x2;
        const int &corner2Y = y1;

        const bool connected_corner1 = !isBlocked( corner1X, corner1Y ) &&              // �սǲ���������
                                       turn0Corner_bool( x1, y1, corner1X, corner1Y ) &&     // �ս��루x1,y1������ֱ����ͨ
                                       turn0Corner_bool( x2, y2, corner1X, corner1Y );       // �ս��루x2,y2������ֱ����ͨ

        const bool connected_corner2 = !isBlocked( corner2X, corner2Y ) &&              // ͬ����
                                       turn0Corner_bool( x1, y1, corner2X, corner2Y ) &&
                                       turn0Corner_bool( x2, y2, corner2X, corner2Y );

        // �����Ƿ�������һ������ͨ�Ĺս�����
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
