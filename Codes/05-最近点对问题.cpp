#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>
using namespace std;

double Distance2(const vector<pair<double, double>> &aPoints, int i, int j)
{
    double x0 = aPoints[i].first, y0 = aPoints[i].second;
    double x1 = aPoints[j].first, y1 = aPoints[j].second;
    return (x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0);
}

double ShortestDistance(const vector<pair<double, double>> &aPoints, const vector<pair<int, int>> xIndex, const vector<int> &yIndex, int s, int t)
{
    if (s >= t)
        return DBL_MAX;
    if (s + 1 == t)
        return Distance2(aPoints, s, t);
    int k = (s + t) / 2;
    double d1 = ShortestDistance(aPoints, xIndex, yIndex, s, k);
    double d2 = ShortestDistance(aPoints, xIndex, yIndex, k + 1, t);
    return min(d1, d2);
}

double ShortestDistance(const vector<pair<double, double>> &aPoints)
{
    vector<pair<int, int>> xIndex(aPoints.size());
    for (int i = 0; i < aPoints.size(); i++)
        xIndex[i].first = i;
    sort(xIndex.begin(), xIndex.end(), [aPoints](pair<int, int> a, pair<int, int> b) { return aPoints[a.first].first < aPoints[b.first].first; });

    vector<int> yIndex(aPoints.size());
    for (int i = 0; i < aPoints.size(); i++)
        yIndex[i] = i;
    sort(yIndex.begin(), yIndex.end(), [aPoints, xIndex](int a, int b) { return aPoints[xIndex[a].first].second < aPoints[xIndex[b].first].second; });

    for (int i = 0; i < yIndex.size(); i++)
        xIndex[yIndex[i]].second = i;

    return sqrt(ShortestDistance(aPoints, xIndex, yIndex, 0, aPoints.size() - 1));
}

double ShortestDistance_v2(const vector<pair<double, double>> &aPoints)
{
    double minDistance = DBL_MAX;
    for (int i = 0; i < aPoints.size(); i++)
    {
        for (int j = i + 1; j < aPoints.size(); j++)
        {
            double aDistance = Distance2(aPoints, i, j);
            if (aDistance < minDistance)
                minDistance = aDistance;
        }
    }
    return sqrt(minDistance);
}

int main()
{
    vector<pair<double, double>> aPoints{{5, 2}, {4, 3}, {3, 4}, {2, 5}};
    double aShortestDistance = ShortestDistance(aPoints);
    cout << "Shortest distance: " << aShortestDistance << endl;
    double aShortestDistance_v2 = ShortestDistance_v2(aPoints);
    cout << "Shortest distance v2: " << aShortestDistance_v2 << endl;

    return 0;
}