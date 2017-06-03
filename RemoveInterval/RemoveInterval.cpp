#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void MergeInterval(vector<pair<int,int>>& intervalSet)
{
    vector<pair<int,int>>originIntervalSet;
    swap(originIntervalSet, intervalSet);
    sort(originIntervalSet.begin(), originIntervalSet.end());

    for(int idx = 0; idx < originIntervalSet.size(); ++idx)
    {
        if(intervalSet.size() == 0 || originIntervalSet[idx].first > intervalSet[intervalSet.size() - 1].second)
        {
            intervalSet.push_back(originIntervalSet[idx]);
        }
        else
        {
            intervalSet[intervalSet.size() - 1].second = max(originIntervalSet[idx].second,intervalSet[intervalSet.size() - 1].second);
        }
    }
}

vector<pair<int,int>> DiffInterval(vector<pair<int,int>>& intervalSetA, vector<pair<int,int>>& intervalSetB)
{
    vector<pair<int,int>>result;
    int idxA = 0, idxB = 0;

    while(idxA < intervalSetA.size())
    {
        if(idxB == intervalSetB.size())
        {
            result.push_back(intervalSetA[idxA++]);
        }
        else
        {
            if(intervalSetA[idxA].first>=intervalSetB[idxB].second)
            {
                ++idxB;
                continue;
            }

            if(intervalSetA[idxA].second<= intervalSetB[idxB].first)
            {
                result.push_back(intervalSetA[idxA++]);
                continue;
            }

            if(intervalSetA[idxA].first >= intervalSetB[idxB].first)
            {
                if(intervalSetA[idxA].second <= intervalSetB[idxB].second)
                {
                    ++idxA;
                }
                else
                {
                    intervalSetA[idxA].first = intervalSetB[idxB].second;
                    ++idxB;
                }
            }
            else
            {
                result.push_back(make_pair(intervalSetA[idxA].first,intervalSetB[idxB].first));
                if(intervalSetA[idxA].second > intervalSetB[idxB].second)
                {
                    intervalSetA[idxA].first = intervalSetB[idxB].second;
                    ++idxB;
                }
                else
                {
                    ++idxA;
                }
            }
        }
    }

    return result;
}

int IntervalLength(vector<pair<int,int>>& intervalSet)
{
    int result = 0;
    for(auto& each : intervalSet)
    {
        result += each.second - each.first;
    }
    return result;
}

int main()
{
    int N,M;
    //freopen("input.txt", "r", stdin);
    cin >> N >> M;
    vector<pair<int,int>>intervalSetA(N);
    vector<pair<int,int>>intervalSetB(M);
    for(int idx = 0; idx < N; ++idx)
    {
        cin >> intervalSetA[idx].first >> intervalSetA[idx].second;
    }

    for(int idx = 0; idx < M; ++idx)
    {
        cin >> intervalSetB[idx].first >> intervalSetB[idx].second;
    }

    MergeInterval(intervalSetA);
    MergeInterval(intervalSetB);
    vector<pair<int,int>>resultSet = DiffInterval(intervalSetA,intervalSetB);
    MergeInterval(resultSet);
    int length = IntervalLength(resultSet);
    cout << length << endl;
    return 0;
}
