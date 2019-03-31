#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Task
{
    int Id;
    int StartTime;
    int OverTime;
};

// 从输入任务集合中选出一组可安排的任务，输出可安排任务的Id集合
vector<int> GetSchedule(vector<Task> &aTasks)
{
    vector<int> aSchedule;

    // 对任务按结束时间排序
    sort(aTasks.begin(), aTasks.end(), [](Task &t1, Task &t2) { return t1.OverTime < t2.OverTime; });

    // 按任务结束时间筛选任务
    int aOverTime = 0; // 目前任务表已经安排到的时间点
    for (auto &aTask : aTasks)
    {
        // 如果任务需要在已安排到的时间点之前开始，则不能安排
        if (aTask.StartTime < aOverTime)
            continue;

        // 将可安排的任务的Id记入任务表，并修正已安排到的时间点
        aSchedule.push_back(aTask.Id);
        aOverTime = aTask.OverTime;
    }
    return aSchedule;
}

int main()
{
    vector<Task> aTasks{
        {0, 1, 4},
        {1, 3, 5},
        {2, 0, 6},
        {3, 5, 7},
        {4, 3, 8},
        {5, 5, 9},
        {6, 6, 10},
        {7, 8, 11},
        {8, 8, 12},
        {9, 2, 13},
        {10, 12, 14},
    };

    auto aSchedule = GetSchedule(aTasks);

    cout << "Schedule: ";
    for (auto aId : aSchedule)
    {
        cout << aId << ", ";
    }
    cout << endl;

    return 0;
}