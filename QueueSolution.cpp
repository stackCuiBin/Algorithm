/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-27 20:51:38
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-27 21:42:03
 */
#include <iostream>

using namespace std;

/*
 * 为了检测方便，在棋盘的外围加了一圈边框(#号表示)。
 * SIZE表示是几皇后，SIZE=8表示八皇后问题。
 * 使用递归和回溯算法，从最底层开始放置皇后，所以只用
 * 检测左下、正下、右下方向上有没有放置皇后，棋盘上方
 * 都是空的，所以不用检测。  
 */

template <int SIZE>
class QueueSolution
{
protected:
    enum {N = SIZE + 2};

    struct Pos
    {
        Pos(int px = 0, int py = 0): x(px), y(py) {}
        int x;
        int y;
    };

    int m_count;
    int m_chessboard[N][N];
    Pos m_direction[3];

    void init()
    {
        m_count = 0;

        for(int x = 0; x < N; x += N-1)
        {
            for(int y = 0; y < N; y++)
            {
                m_chessboard[x][y] = 2;
                m_chessboard[y][x] = 2;
            }
        }

        for(int x = 1; x <= SIZE; x++)
        {
            for(int y = 1; y <= SIZE; y++)
            {
                m_chessboard[x][y] = 0;
            }
        }

        // 左下角方向
        m_direction[0].x = -1;
        m_direction[0].y = -1;
        // 正下方方向
        m_direction[1].x = 0;
        m_direction[1].y = -1;
        // 右下角方向
        m_direction[2].x = 1;
        m_direction[2].y = -1;
    }

    void print()
    {
        for(int x = 0; x < N; x++)
        {
            for(int y = 0; y < N; y++)
            {
                switch(m_chessboard[x][y])
                {
                    case 0: cout << " "; break;
                    case 1: cout << "*"; break; // 打印皇后
                    case 2: cout << "#"; break; // 打印边界
                    default: break;
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    // x,y表示坐标，d表示方向
    bool check(int x, int y, int d)
    {
        bool flag = true;

        do{
            x += m_direction[d].x;
            y += m_direction[d].y;
            flag = flag && (m_chessboard[x][y] == 0);
        }while(flag);

        // 在左下、正下、右下方向上查找到边界都没有皇后，说明x,y位置上可以放皇后
        return (m_chessboard[x][y] == 2);   
    }

    // 在y行上放置皇后
    void run(int y)
    {
        if ( y <= SIZE )
        {
            for(int x = 1; x <= SIZE; x++)
            {
                if ( check(x, y, 0) && check(x, y, 1) && check(x, y, 2) )
                {
                    m_chessboard[x][y] = 1;

                    run(y+1);

                    m_chessboard[x][y] = 0;
                }
            }
        }
        else
        {
            // 所有行上都放置了皇后，此方案可行
            m_count++;
            print();
        }
    }

public:
    QueueSolution()
    {
        init();
    }

    void run()
    {
        run(1);
    }

    int getCount()
    {
        return m_count;
    }
};

int main()
{
    QueueSolution<8> qs;

    qs.run();

    cout << "Total is " << qs.getCount() << endl;
}
