#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>
#include <random>
using namespace std;

// 计算两点间距离的平方
int _count = 0; // 用来统计计算点距离的次数
inline double Distance(double x0, double y0, double x1, double y1)
{
    _count++;
    return sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
}

// 计算点表中指定两点间距离的平方
inline double Distance(const vector<pair<double, double>> &points, int i, int j)
{
    double x0 = points[i].first, y0 = points[i].second;
    double x1 = points[j].first, y1 = points[j].second;
    return Distance(x0, y0, x1, y1);
}

// 分治法求解最近点对的距离的平方
double ShortestDistance(const vector<pair<double, double>> &points, const vector<pair<int, int>> xIndex, const vector<int> &yIndex, int s, int t)
{
    // 终结条件
    if (s >= t)
        return DBL_MAX; // 不足两个点时
    if (s + 1 == t)
    {
        double d = Distance(points, xIndex[s].first, xIndex[t].first); // 只有两个点时
        return d;
    }

    // 沿x方向按点数平分区间，分别求解左右子区间中的最近点对的距离
    int k = (s + t) / 2; // 将xIndex[s]~xIndex[t]平分
    double d1 = ShortestDistance(points, xIndex, yIndex, s, k);
    double d2 = ShortestDistance(points, xIndex, yIndex, k + 1, t);
    double d = min(d1, d2);

    // 检索左半区间中距离分割线不超过d的点
    double splitX = points[xIndex[k + 1].first].first; // 分割线的x
    for (int i = k; i >= s; i--)
    {
        double x0 = points[xIndex[i].first].first;
        double y0 = points[xIndex[i].first].second;
        if (splitX - x0 >= d)
            break;
        // 沿y方向向上下两个方向检索右半区间距x0不超过d，距y0不超过d的点
        for (int j = xIndex[i].second - 1; j >= 0; j--)
        {
            // 略过区间外的点
            if (yIndex[j] <= k || yIndex[j] > t)
                continue;

            double x1 = points[xIndex[yIndex[j]].first].first;
            double y1 = points[xIndex[yIndex[j]].first].second;
            // 略过x距离分割线不小于d的点
            if (x1 - splitX >= d)
                continue;
            // 略过y距离(x0,y0)点不小于d的点
            if (y0 - y1 >= d)
                break;
            double d0 = Distance(x0, y0, x1, y1);
            if (d0 < d)
                d = d0;
        }
        for (int j = xIndex[i].second + 1; j < yIndex.size(); j++)
        {
            // 略过区间外的点
            if (yIndex[j] <= k || yIndex[j] > t)
                continue;

            double x1 = points[xIndex[yIndex[j]].first].first;
            double y1 = points[xIndex[yIndex[j]].first].second;
            // 略过x距离分割线不小于d的点
            if (x1 - splitX >= d)
                continue;
            // 略过y距离(x0,y0)点不小于d的点
            if (y1 - y0 >= d)
                break;
            double d0 = Distance(x0, y0, x1, y1);
            if (d0 < d)
                d = d0;
        }
    }
    return d;
}

// 分治法计算最短点对距离的入口（准备工作）
double ShortestDistance(const vector<pair<double, double>> &points)
{
    vector<pair<int, int>> xIndex(points.size());
    for (int i = 0; i < points.size(); i++)
        xIndex[i].first = i;
    sort(xIndex.begin(), xIndex.end(),
         [points](pair<int, int> a, pair<int, int> b) {
             return points[a.first].first < points[b.first].first;
         });

    vector<int> yIndex(points.size());
    for (int i = 0; i < points.size(); i++)
        yIndex[i] = i;
    sort(yIndex.begin(), yIndex.end(),
         [points, xIndex](int a, int b) {
             return points[xIndex[a].first].second < points[xIndex[b].first].second;
         });

    for (int i = 0; i < yIndex.size(); i++)
        xIndex[yIndex[i]].second = i;

    return ShortestDistance(points, xIndex, yIndex, 0, points.size() - 1);
}

// 穷举法计算最近点对的距离
double ShortestDistance_v2(const vector<pair<double, double>> &points)
{
    double minDistance = DBL_MAX, mini, minj;
    for (int i = 0; i < points.size(); i++)
    {
        for (int j = i + 1; j < points.size(); j++)
        {
            double aDistance = Distance(points, i, j);
            if (aDistance < minDistance)
            {
                mini = i;
                minj = j;
                minDistance = aDistance;
            }
        }
    }
    return minDistance;
}

int main()
{
    random_device rd;
    for (int i = 0; i < 1000; i++)
    {
        vector<pair<double, double>> points;

        // 生成随机测试数据
        for (int i = 0; i < 100; i++)
        {
            points.push_back(make_pair((rd() % 1000) / 10.0, (rd() % 1000) / 10.0));
        }

        // 用分治法计算
        _count = 0;
        double aShortestDistance = ShortestDistance(points);

        // 用穷举法验证计算结果
        _count = 0;
        double aShortestDistance_v2 = ShortestDistance_v2(points);

        if (aShortestDistance != aShortestDistance_v2)
        {
            for (auto point : points)
                cout << "{" << point.first << ", " << point.second << "}, ";
            cout << endl;
            cout << "分治法计算结果: " << aShortestDistance << ", 共计算点距 " << _count << "次。" << endl;
            cout << "穷举法计算结果: " << aShortestDistance_v2 << ", 共计算点距 " << _count << "次。" << endl;
        }
    }

    return 0;
}
