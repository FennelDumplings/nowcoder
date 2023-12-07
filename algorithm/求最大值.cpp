#include <iostream>
#include <vector>
#include<iomanip>
#include <iostream>

using namespace std;

class BIT_RMQ
{
public:
    BIT_RMQ():vec(1,0),a(1,0){}
    BIT_RMQ(int n):vec(n + 1, 0),a(n,0){}

    void update(int idx, int x)
    {
        // vec[idx] 管的是 [idx-lowbit[idx] + 1..idx] 这个区间
        // a[idx -  1] 改为 x
        // vec[idx]
        a[idx - 1] = x;
        vec[idx] = x;
        int n = a.size();
        for(int i = idx; i <= n; i += _lowbit(i))
        {
            for(int j = 1; j < _lowbit(i); j <<= 1)
            {
                // j < _lowbit(i) <= j - i < _lowbit(i) - i <= i - j > i - _lowbit(i)
                // i = 8，即改 vec[8]
                // 要看 vec[7] = i - 1
                //      vec[6] = i - 2
                //      vec[4] = i - 4
                vec[i] = max(vec[i], vec[i - j]);
            }
        }
    }

    int query(int l, int r)
    {
        // 直接看 vec[r] 不行
        // vec[r] 对应 [r - lowbit[r] + 1, r]
        int ans = a[r - 1];
        while(true)
        {
            ans = max(ans, a[r - 1]);
            if(l == r)
                break;
            --r;
            for(; r - _lowbit(r) >= l; r -= _lowbit(r))
                ans = max(ans, vec[r]);
        }
        return ans;
    }

    void view()
    {
        int n = a.size();
        for(int i = 0; i < n; ++i)
            cout << a[i] << " ";
        cout << endl;
        for(int i = 1; i <= n; ++i)
            cout << vec[i] << " ";
        cout << endl;
    }

private:
    vector<int> vec;
    vector<int> a;

    int _lowbit(int x)
    {
        return x & (-x);
    }
};

int main()
{
    int n;
    while(cin >> n && n > 0)
    {
        vector<int> a(n);
        for(int i = 0; i < n; ++i)
            cin >> a[i];
        BIT_RMQ bit_rmq(n);
        for(int i = 0; i < n - 1; ++i)
        {
            bit_rmq.update(i + 1, a[i + 1] - a[i]);
        }
        int Q;
        cin >> Q;
        for(int i = 0; i < Q; ++i)
        {
            int p, y;
            cin >> p >> y;
            p--;
            a[p] = y;
            if(p > 0)
                bit_rmq.update(p, a[p] - a[p-1]);
            if(p < n - 1)
                bit_rmq.update(p + 1, a[p + 1] - a[p]);
            cout << fixed << setprecision(2) << (double)bit_rmq.query(1, n - 1) << endl;
        }
    }
}
