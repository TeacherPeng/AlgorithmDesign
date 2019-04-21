#include <iostream>
using namespace std;

int FourColors()
{
    int count = 0;
    for (int a = 0; a < 4; a++)
    {
        for (int b = 0; b < 4; b++)
        {
            if (a == b) continue;
            for (int c = 0; c < 4; c++)
            {
                if (b == c) continue;
                for (int d = 0; d < 4; d++)
                {
                    if (a == d || c == d) continue;
                    count++;
                }
            }
        }
    }
    return count;
}

int main()
{
    cout << "Count is " << FourColors() << endl;
    return 0;
}