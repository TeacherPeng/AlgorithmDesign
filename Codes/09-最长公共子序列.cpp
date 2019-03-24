#include <iostream>
#include <vector>
#include <string>
using namespace std;

int MaxSubStringLen(const string &X, const string &Y)
{
    vector<vector<int>> c(X.size() + 1, vector<int>(Y.size() + 1));
    
    for (size_t i = 0; i < X.size() + 1; i++)
        c[i][0] = 0;
    for (size_t i = 0; i < Y.size() + 1; i++)
        c[0][i] = 0;

    for (size_t i = 1; i < X.size() + 1; i++)
    {
        for (size_t j = 1; j < Y.size() + 1; j++)
        {
            if (X[i - 1] == Y[j - 1])
                c[i][j] = c[i - 1][j - 1] + 1;
            else if (c[i][j - 1] < c[i - 1][j])
                c[i][j] = c[i - 1][j];
            else
                c[i][j] = c[i][j - 1];
        }
    }

    int result = c[X.size()][Y.size()];
    return result;
}

int main()
{
    string X, Y;
    while (cin >> X >> Y)
    {
        cout << MaxSubStringLen(X, Y) << endl;
    }
    return 0;
}
