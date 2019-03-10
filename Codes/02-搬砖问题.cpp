#include <iostream>
#include <tuple>
using namespace std;

tuple<int, int, int> CarryBricks_v1(int aTotalBricks, int aManBricks, int aWomanBricks, int aChildBricks)
{
    int menNum = aTotalBricks / aManBricks;
    int womenNum = aTotalBricks / aWomanBricks;
    int childrenNum = aTotalBricks / aChildBricks;
    int sum = menNum + womenNum + childrenNum;
    for (int men = 0; men <= aTotalBricks / aManBricks; men++)
    {
        for (int women = 0; women <= aTotalBricks / aWomanBricks; women++)
        {
            for (int children = 0; children <= aTotalBricks / aChildBricks; children++)
            {
                if (men * aManBricks + women * aWomanBricks + children * aChildBricks == aTotalBricks)
                {
                    if (men + women + children < sum)
                    {
                        sum = men + women + children;
                        menNum = men;
                        womenNum = women;
                        childrenNum = children;
                    }
                }
            }
        }
    }
    return make_tuple(menNum, womenNum, childrenNum);
}

tuple<int, int, int> CarryBricks_v2(int aTotalBricks, int aManBricks, int aWomanBricks, int aChildBricks)
{
    int menNum = aTotalBricks / aManBricks;
    int womenNum = aTotalBricks / aWomanBricks;
    int childrenNum = aTotalBricks / aChildBricks;
    int sum = menNum + womenNum + childrenNum;
    int menMaxNum = aTotalBricks / aManBricks;
    for (int men = 0; men <= menMaxNum; men++)
    {
        int womenMaxNum = (aTotalBricks - men * aManBricks) / aWomanBricks;
        for (int women = 0; women <= womenMaxNum; women++)
        {
            int restBricks = aTotalBricks - men * aManBricks - women * aWomanBricks;
            if ((restBricks % aChildBricks) == 0)
            {
                int children = restBricks / aChildBricks;
                if (men + women + children < sum)
                {
                    sum = men + women + children;
                    menNum = men;
                    womenNum = women;
                    childrenNum = children;
                }
            }
        }
    }
    return make_tuple(menNum, womenNum, childrenNum);
}

int main()
{
    auto aResult = CarryBricks_v1(100, 7, 5, 2);
    cout << "Men " << get<0>(aResult) << ", Women " << get<1>(aResult) << ", Childiren " << get<2>(aResult) << endl;

    aResult = CarryBricks_v2(100, 7, 5, 2);
    cout << "Men " << get<0>(aResult) << ", Women " << get<1>(aResult) << ", Childiren " << get<2>(aResult) << endl;
    return 0;
}