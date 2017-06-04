#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int inf = ~(1<<31);

int Query(int root, int L, int R, int queryLeft, int queryRight, vector<int>& data)
{
    if(queryLeft <= L && R <= queryRight)
    {
        return data[root];
    }

    int M = L + (R - L)/2;
    int ans = inf;
    if (queryLeft <= M)
    {
        ans = min(ans,Query(root*2+1, L, M, queryLeft, queryRight, data));
    }
    if (queryRight > M)
    {
        ans = min(ans,Query(root*2+2, M+1, R, queryLeft, queryRight, data));
    }
    return ans;
}

void Update(int root, int L, int R, int idx, int value, vector<int>& data)
{
    if(L == R)
    {
        data[root] = value;
    }
    else
    {
        int M = L + (R - L)/2;
        if(idx <= M)
        {
            Update(root*2 + 1, L, M, idx, value, data);
        }
        else
        {
            Update(root*2 + 2, M+1, R, idx, value, data);
        }

        data[root] = min(data[root*2+1],data[root*2+2]);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);

    int N = 0;
    cin >> N;
    vector<int>minData(4*N,inf);
    for(int idx = 0; idx < N; ++idx)
    {
        int value = 0;
        scanf("%d",&value);// cannot use cin here, because when the input is large, the speed is slow.
        Update(0,0,N-1,idx,value,minData);
    }

    int M = 0;
    cin >> M;
    for(int idx = 0; idx < M; ++idx)
    {
        int type = -1;
        int p1, p2;
        scanf("%d%d%d",&type, &p1, &p2);// cannot use cin here, because when the input is large, the speed is slow.
        if(type == 0)
        {
            printf("%d\n", Query(0,0,N-1,p1-1,p2-1,minData));
        }
        else
        {
            Update(0,0,N-1,p1-1,p2,minData);
        }
    }

    return 0;
}
