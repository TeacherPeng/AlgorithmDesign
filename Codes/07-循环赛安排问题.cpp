#include <cstdio>
#include <vector>
using namespace std;

vector<vector<int>> GetSchedule(int m)
{
    // 约定人数n是2的m次幂
    int n = 1 << m;

    // 分配赛程表的存储空间
    vector<vector<int>> aSchedule(n, vector<int>(n - 1));
    
    // 开始填表
    for (int i = 1; i < n; i += i)
    {
        // 补充缺少的一列
        for (int s = 0; s < n; s += i + i)
        {
            for (int k = s; k < s + i; k++)
            {
                aSchedule[k][i - 1] = k + i + 1;
                aSchedule[k + i][i - 1] = k + 1;
            }
        }

        // 复制相邻表
        for (int j = 0; j < i - 1; j++)
        {
            for (int s = 0; s < n; s += i + i)
            {
                for (int k = s; k < s + i; k++)
                {
                    aSchedule[k][i + j] = aSchedule[k + i][j];
                    aSchedule[k + i][i + j] = aSchedule[k][j];
                }
            }
        }
    }

    // 返回结果表
    return aSchedule;
}

int PrintSchedule(const vector<vector<int>> &aSchedule)
{
    for (int i = 0; i < aSchedule.size(); i++)
    {
        printf("%-4d", i + 1);
        for (int x : aSchedule[i])
        {
            printf("%-4d", x);
        }
        printf("\n");
    }
    return 0;
}

int main()
{
    vector<vector<int>> aSchedule = GetSchedule(4);
    PrintSchedule(aSchedule);
    return 0;
}