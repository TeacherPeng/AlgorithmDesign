#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum DirectEnum
{
    top,
    topleft,
    left,
};

int GetMaxSubStringLen(const string &X, const string &Y, vector<vector<DirectEnum>> &d)
{
    // 分配最优值矩阵c和计算轨迹矩阵d的空间
    vector<vector<int>> c(X.size() + 1, vector<int>(Y.size() + 1));
    d = vector<vector<DirectEnum>>(X.size() + 1, vector<DirectEnum>(Y.size() + 1));

    // 初始化叶子结点
    for (size_t i = 0; i < X.size() + 1; i++)
        c[i][0] = 0;
    for (size_t i = 0; i < Y.size() + 1; i++)
        c[0][i] = 0;

    // 逐行逐列计算子问题的最优值c，并记录计算轨迹d
    for (size_t i = 1; i < X.size() + 1; i++)
    {
        for (size_t j = 1; j < Y.size() + 1; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                d[i][j] = DirectEnum::topleft;
            }
            else if (c[i][j - 1] < c[i - 1][j])
            {
                c[i][j] = c[i - 1][j];
                d[i][j] = DirectEnum::top;
            }
            else
            {
                c[i][j] = c[i][j - 1];
                d[i][j] = DirectEnum::left;
            }
        }
    }

    // 返回最优值
    int result = c[X.size()][Y.size()];
    return result;
}

string GetMaxSubString(const string X, const string Y, const vector<vector<DirectEnum>> &d)
{
    string s;
    for (int i = X.size(), j = Y.size(); i > 0 && j > 0;)
    {
        switch (d[i][j])
        {
        case DirectEnum::top:
            i--;
            break;
        case DirectEnum::left:
            j--;
            break;
        case DirectEnum::topleft:
            s = X[i - 1] + s;
            i--;
            j--;
            break;
        }
    }
    return s;
}

int main()
{
    string X, Y;
    cin >> X >> Y;
    vector<vector<DirectEnum>> d;
    cout << "最长公共子序列长度为：" << GetMaxSubStringLen(X, Y, d) << endl;

    string result = GetMaxSubString(X, Y, d);
    cout << "最长公共子序列为：" << result << endl;
    return 0;
}
