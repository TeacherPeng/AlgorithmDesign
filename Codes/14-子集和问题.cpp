#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
using namespace std;

enum ProcessingStatusEnum
{
    unknown,
    select,
    discard,
};

// 从指定正整数集合W中找出一个和等于M的子集
class SubsetSumSolver
{
  public:
    SubsetSumSolver(vector<int> aW, int aM, int (*aF)(const vector<int> &))
        : W(aW), M(aM), A(aW.size()), F(aF)
    {
        Solve();
    }

  private:
    int BackTracking()
    {
        Index--;
        if (Index >= 0)
        {
            SW += W[Index];
            if (A[Index] == ProcessingStatusEnum::select)
                SA -= W[Index];
        }
        return 0;
    }
    int GoForward()
    {
        Index++;
        if (Index >= A.size())
            BackTracking();
        else
            A[Index] = ProcessingStatusEnum::unknown;
        return 0;
    }
    int CheckResult()
    {
        if (SA != M)
            return 0;

        // 收集计算结果并返回结果
        vector<int> aSubset;
        for (int j = 0; j <= Index; j++)
        {
            if (A[j] == ProcessingStatusEnum::select)
                aSubset.push_back(W[j]);
        }
        F(aSubset);
        return 0;
    }
    int Solve()
    {
        // 初始化遍历结点
        sort(W.begin(), W.end());
        SW = accumulate(W.begin(), W.end(), 0);
        SA = 0;
        Index = 0;
        A[Index] = ProcessingStatusEnum::unknown;

        // 遍历状态空间树
        while (Index >= 0)
        {
            // 处理当前元素W[Index]
            switch (A[Index])
            {
            case ProcessingStatusEnum::unknown:
                // 检查必要遍历条件
                if (SA + W[Index] > M || SA + SW < M)
                {
                    // 已经不满足必要遍历条件，回溯
                    BackTracking();
                    continue;
                }
                // 当前元素还未被处理过，首次尝试选中该元素
                A[Index] = ProcessingStatusEnum::select;
                SW -= W[Index];
                SA += W[Index];
                CheckResult();
                GoForward();
                break;
            case ProcessingStatusEnum::select:
                // 当前元素已被选中过，尝试放弃该元素
                A[Index] = ProcessingStatusEnum::discard;
                SW -= W[Index];
                CheckResult();
                GoForward();
                break;
            case ProcessingStatusEnum::discard:
                // 当前元素已被选中和放弃过，回溯
                BackTracking();
                break;
            }
        }

        return 0;
    }

  private:
    vector<int> W;                  // 输入正整数集合
    int M;                          // 目标值
    vector<ProcessingStatusEnum> A; // 记录每个元素的处理状态
    int SW;                         // 剩余和
    int SA;                         // 选入和
    int Index;                      // 待处理元素的下标
    int (*F)(const vector<int> &);  // 接收结果的回调函数
};

int Print(const vector<int> &aSubset)
{
    cout << "{ ";
    copy(aSubset.begin(), aSubset.end(), ostream_iterator<int>(cout, ", "));
    cout << '}' << endl;
    return 0;
}
int main()
{
    vector<int> W{5, 1, 14, 12, 7};
    SubsetSumSolver aSolver(W, 20, Print);
    return 0;
}