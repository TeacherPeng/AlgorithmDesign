#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Task
{
    int Deadline;
    int Punishment;
};

vector<int> GetSchedule(vector<Task> &aTasks)
{
    vector<int> aSchedule, aDelayedTasks;

    // 任务集合按误时惩罚从大到小排序
    sort(aTasks.begin(), aTasks.end(), [](const Task &t1, const Task &t2) { return t1.Punishment > t2.Punishment; });

    // 构造任务容忍度向量
    vector<int> tolerance(aTasks.size());

    // 按误时惩罚从大到小的顺序对任务进行筛选
    for (int i = 0; i < aTasks.size(); i++)
    {
        // 设置任务i的初始容忍度
        tolerance[i] = aTasks[i].Deadline - 1;

        vector<int> willAdjust; // 记录需要调整容忍度的任务的序号
        bool choosed = true;
        // 检索已选入任务
        for (int j : aSchedule)
        {
            if (aTasks[j].Deadline <= aTasks[i].Deadline) // 排在任务i之前的任务j不受影响
            {
                // 检查任务i是否有足够的容忍度允许任务j排在自己前面
                if (tolerance[i] > 0)
                {
                    // 任务i接受任务j排在前面
                    tolerance[i]--;
                }
                else
                {
                    // 任务i不接受任务j排在前面
                    choosed = false;
                    break;
                }
            }
            else if (tolerance[j] <= 0) // 排在任务i之后的任务j
            {
                // 排在任务i之后的任务j没有足够容忍度允许任务i排在自己前面，任务i被拒绝
                choosed = false;
                break;
            }
            else
            {
                // 任务j允许任务i排在自己前面
                willAdjust.push_back(j);
            }
        }

        if (choosed)
        {
            // 任务i被接受
            aSchedule.push_back(i);

            // 调整排在任务i后面的任务的容忍度
            for (auto j : willAdjust)
                tolerance[j]--;
        }
        else
        {
            // 任务i被拒绝
            aDelayedTasks.push_back(i);
        }
    }

    // 对选中的可安排的任务，按结束时间排序
    sort(aSchedule.begin(), aSchedule.end(), [aTasks](int i, int j) { return aTasks[i].Deadline < aTasks[j].Deadline; });

    // 将未选中的不能及时完成的任务排在任务表后面
    for (auto i : aDelayedTasks)
        aSchedule.push_back(i);

    return aSchedule;
}

int main()
{
    vector<Task> aTasks{
        {6, 10},
        {4, 20},
        {1, 30},
        {3, 40},
        {4, 50},
        {2, 60},
        {4, 70},
    };

    auto aSchedule = GetSchedule(aTasks);

    cout << "Schedule: ";
    for (auto aId : aSchedule)
        cout << aId << ", ";
    cout << endl;

    return 0;
}