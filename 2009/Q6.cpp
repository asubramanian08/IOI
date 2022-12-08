// 9:50 - 11:06
#include <iostream>
#include <queue>
using namespace std;
using pii = pair<int, int>;

int n, s, grid[805][805];
bool vis[805][805];
pii honey, home;
int x[] = {0, -1, 0, 1};
int y[] = {-1, 0, 1, 0};
bool inRange(pii pos, int dir) { return 0 <= pos.first + x[dir] && pos.first + x[dir] < n &&
                                        0 <= pos.second + y[dir] && pos.second + y[dir] < n; }

bool canReachHome(int wait)
{
    if (wait >= grid[honey.first][honey.second])
        return false;
    queue<pair<pii, pii>> BFS;
    BFS.push({{1, s}, honey});
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            vis[i][j] = false;
    while (!BFS.empty())
    {
        int time = BFS.front().first.first;
        int stepsLeft = BFS.front().first.second;
        pii pos = BFS.front().second;
        BFS.pop();
        if ((--stepsLeft) == 0)
            time++, stepsLeft = s;
        for (int i = 0; i < 4; i++)
            if (inRange(pos, i))
            {
                if (vis[pos.first + x[i]][pos.second + y[i]] == false &&
                    grid[pos.first + x[i]][pos.second + y[i]] != -1 &&
                    grid[pos.first + x[i]][pos.second + y[i]] - wait >= time)
                {
                    vis[pos.first + x[i]][pos.second + y[i]] = true;
                    BFS.push({{time, stepsLeft}, {pos.first + x[i], pos.second + y[i]}});
                }
                else if (grid[pos.first + x[i]][pos.second + y[i]] == -2)
                    return true;
            }
    }
    return false;
}

int main(void)
{
    cin >> n >> s;
    queue<pair<pii, int>> hive;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            char ch;
            cin >> ch;
            if (ch == 'T')
                grid[i][j] = -1;
            else if (ch == 'G')
                grid[i][j] = -3;
            else if (ch == 'M')
                grid[i][j] = -3, honey = {i, j};
            else if (ch == 'D')
                grid[i][j] = -2, home = {i, j};
            else // == 'H'
            {
                grid[i][j] = 0;
                hive.push({{i, j}, 0});
            }
        }
    while (!hive.empty())
    {
        pii loc = hive.front().first;
        int infectTime = hive.front().second;
        hive.pop();
        for (int i = 0; i < 4; i++)
            if (inRange(loc, i) && grid[loc.first + x[i]][loc.second + y[i]] == -3)
            {
                grid[loc.first + x[i]][loc.second + y[i]] = infectTime + 1;
                hive.push({{loc.first + x[i], loc.second + y[i]}, infectTime + 1});
            }
    }
    int lo = 0, hi = 1000000;
    while (hi - lo > 1)
        if (int mid = (lo + hi) / 2; canReachHome(mid))
            lo = mid;
        else
            hi = mid;
    if (lo == 0 && !canReachHome(0))
        cout << -1 << endl;
    else
        cout << lo << endl;
}