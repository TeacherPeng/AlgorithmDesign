#include <iostream>
using namespace std;

int Permutation(int perm[], int n, int (*F)(int *, int), int index)
{
    if (index >= n - 1)
    {
        F(perm, n);
        return 0;
    }
    
    for (int i = index; i < n; i++)
    {
        swap(perm[index], perm[i]);
        Permutation(perm, n, F, index + 1);
        swap(perm[index], perm[i]);
    }
    return 0;
}

int Print(int perm[], int n)
{
    for (int i = 0; i < n; i++)
        cout << perm[i] << ", ";
    cout << endl;
    return 0;
}

int main()
{
    int perm[5];
    for (int i = 0; i < 5; i++)
        perm[i] = i + 1;
    Permutation(perm, 5, Print, 0);
    return 0;
}