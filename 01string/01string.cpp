#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

string CreateStringAux(int k)
{
    string result;
    for(int idx = 0; idx < k; ++idx)
    {
        result += "01";
    }
    return result;
}

string CreateString(int n, int m)
{
    string result;
    if(m > n + 1)
    {
        return "NO";
    }

    if(m == n + 1)
    {
        return "1" + CreateStringAux(n);
    }

    return CreateStringAux(m) + string(n - m, '0');
}

int main()
{
    int n = 0, m = 0;
//    freopen("input.txt", "r", stdin);
    cin >> n >> m;
    cout << CreateString(n,m) <<endl;
    return 0;
}
