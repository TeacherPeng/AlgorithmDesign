#include <iostream>
#include <vector>
using namespace std;

class NQueenQuestion
{
  public:
    // 初始化状态结点，开始遍历状态空间树
    NQueenQuestion(int n, int (*F)(const vector<int> &))
        : _board(n), _col(n), _L1(n + n - 1), _L2(n + n - 1), N(n), _F(F)
    {
        Solve();
    }

  private:
    bool CanPut(int row, int col)
    {
        return !_col[col] && !_L1[row + col] && !_L2[row - col + N - 1];
    }
    int Put(int row, int col)
    {
        _board[row] = col;
        _col[col] = true;
        _L1[row + col] = true;
        _L2[row - col + N - 1] = true;
        return 0;
    }
    int Remove(int row)
    {
        int col = _board[row];
        _col[col] = false;
        _L1[row + col] = false;
        _L2[row - col + N - 1] = false;
        return 0;
    }
    int GetNextCol(int row)
    {
        int col;
        for (col = _board[row] + 1; col < N && !CanPut(row, col); col++)
            ;
        return col;
    }
    int BackTracking()
    {
        _row--;
        if (_row >= 0)
            Remove(_row);
        return 0;
    }
    int Solve()
    {
        // 初始化遍历结点
        _row = 0;
        _board[_row] = -1;

        // 遍历状态空间树
        while (_row >= 0)
        {
            // 在当前行查找下一个可摆放王后的位置
            int col = GetNextCol(_row);

            if (col < N)
            {
                // 找到一个可摆放王后的位置，放王后
                Put(_row, col);

                // 准备开始摆下一行的王后
                _row++;
                if (_row == N)
                {
                    // 已经摆完所有的王后，输出结果
                    _F(_board);

                    // 回溯
                    BackTracking();
                }
                else
                {
                    // 为下一行开始摆王后做准备
                    _board[_row] = -1;
                }
            }
            else
            {
                // 回溯
                BackTracking();
            }
        }
        return 0;
    }

  private:
    vector<int> _board;             // 棋盘布局，记录每行王后所在的列
    vector<bool> _col, _L1, _L2;    // 记录三组直线上是否有王后
    int _row, N;                    // 当前行，行数
    int (*_F)(const vector<int> &); // 棋局输出方法
};

int Print(const vector<int> &board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
            cout << (board[i] == j ? 'Q' : '.');
        cout << endl;
    }
    cout << endl;
    return 0;
}
int main()
{
    NQueenQuestion question(5, Print);
    return 0;
}