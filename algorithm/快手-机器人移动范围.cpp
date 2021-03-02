
// https://www.nowcoder.com/practice/8314cb12d35b4e2a920b3bd0474fe1f2?tpId=131&tqId=33853&rp=1&ru=%2Fta%2Fexam-kuaishou&qru=%2Fta%2Fexam-kuaishou%2Fquestion-ranking

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct State
{
    int x, y;
    State(int x, int y):x(x),y(y){}
};

bool check(int x, int y, int k)
{
    int a = 0;
    while(x)
    {
        a += x % 10;
        x /= 10;
    }
    int b = 0;
    while(y)
    {
        b += y % 10;
        y /= 10;
    }
    return a + b <= k;
}

int main()
{
    int m, n, k;
    cin >> m >> n >> k;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    queue<State> q;
    q.push(State(0, 0));
    visited[0][0] = true;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int ans = 0;
    while(!q.empty())
    {
        State cur = q.front();
        q.pop();
        ++ans;
        for(int d = 0; d < 4; ++d)
        {
            int x = cur.x + dx[d];
            int y = cur.y + dy[d];
            if(x < 0 || x >= m || y < 0 || y >= n)
                continue;
            if(visited[x][y])
                continue;
            if(!check(x, y, k))
                continue;
            visited[x][y] = true;
            q.push(State(x, y));
        }
    }
    cout << ans;
}
