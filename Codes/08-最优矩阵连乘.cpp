#include <iostream>
#include <vector>
#include <random>

using namespace std;

// 输入联乘矩阵的行列数向量p，输出子问题最优值矩阵M和计算轨迹矩阵K
int MatrixMul(const vector<long long> &p, vector<vector<long long>> &M, vector<vector<int>> &K)
{
    // 确定联乘矩阵个数
    int n = p.size() - 1;

    // 分配结果表空间
    M = vector<vector<long long>>(n, vector<long long>(n));
    K = vector<vector<int>>(n, vector<int>(n));

    // 从叶子结点自底向上推导最优值M，并记录计算轨迹K
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            int k = j;
            M[j][j + i] = /*M[j][k] +*/ M[k + 1][j + i] + p[j] * p[k + 1] * p[j + i + 1];
            K[j][j + i] = k;
            for (k = j + 1; k < j + i; k++)
            {
                long long temp = M[j][k] + M[k + 1][j + i] + p[j] * p[k + 1] * p[j + i + 1];
                if (temp < M[j][j + i])
                {
                    M[j][j + i] = temp;
                    K[j][j + i] = k;
                }
            }
        }
    }
    return 0;
}

// 输出A[s]~A[t]的联乘式
int Output(const vector<vector<int>> &K, int s, int t)
{
    if (s == t)
    {
        cout << 'A' << s;
    }
    else
    {
        int p = K[s][t];
        if (s < p)
        {
            cout << '(';
            Output(K, s, p);
            cout << ')';
        }
        else
        {
            Output(K, s, p);
        }
        if (p + 1 < t)
        {
            cout << '(';
            Output(K, p + 1, t);
            cout << ')';
        }
        else
        {
            Output(K, p + 1, t);
        }
    }
    return 0;
}

int main()
{
    // 生成随机测试数据
    vector<long long> p;
    random_device rd;
    for (int i = 0; i < 16; i++)
        p.push_back(rd() % 100);
    cout << "p = ";
    for (int x : p)
        cout << x << ", ";
    cout << endl;
    
    // 计算
    vector<vector<long long>> M;
    vector<vector<int>> K;
    MatrixMul(p, M, K);

    // 输出结果式
    Output(K, 0, K.size() - 1);

    return 1;
}
