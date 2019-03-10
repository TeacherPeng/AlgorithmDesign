#include <iostream>
#include <tuple>
using namespace std;

tuple<int, int> ChickenAndRabit(int heads, int feet)
{
    for (int chickens = 0; chickens <= heads; chickens++)
    {
        int rabits = heads - chickens;
        if (chickens * 2 + rabits * 4 == feet)
        {
            return make_tuple(chickens, rabits);
        }
    }
    return make_tuple(0, 0);
}

int main()
{
    auto aResult = ChickenAndRabit(35, 94);
    cout << "Chickens: " << get<0>(aResult) << ", Rabits: " << get<1>(aResult) << endl;
    return 0;
}
