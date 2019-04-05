#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int Permutation(int n, int (*F)(const vector<int> &))
{
    // 创建并初始化状态结点，包括：已排列序列perm、占用标记向量used、正在排列的下标位置i
    vector<int> perm(n);
    vector<bool> used(n + 1);
    int i = 0;
    perm[i] = 0;

    // 开始遍历状态空间树
    while (i >= 0)
    {
        // 搜索下一个可排列的元素（可前进方向）
        int j;
        for (j = perm[i] + 1; j <= n && used[j]; j++) ;

        if (j <= n)
        {
            // 找到可排列的元素，将元素写入排列
            used[j] = true;
            perm[i] = j;

            // 准备排列下一个位置
            i++;
            if (i == n)
            {
                // 如果已经生成一个完整的排列，输出排列结果
                F(perm);

                // 回溯
                i--;
                used[perm[i]] = false;
            }
            else
            {
                // 为下一个位置开始排列做准备
                perm[i] = 0;
            }
        }
        else
        {
            // 没有找到可排列的元素，回溯
            i--;
            if (i >= 0) used[perm[i]] = false;
        }
    }

    return 0;
}

int Print(const vector<int> &L)
{
    copy(L.cbegin(), L.cend(), ostream_iterator<int>(cout, ", "));
    cout << endl;
    return 0;
}

int main()
{
    Permutation(5, Print);
    return 0;
}