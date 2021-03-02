
// https://www.nowcoder.com/practice/76fb9757332c467d933418f4adf5c73d?tpId=131&&tqId=33853&rp=1&ru=/ta/exam-kuaishou&qru=/ta/exam-kuaishou/question-ranking

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

bool inOrder(const vector<int>& tree, int node, int& prev)
{
    int n = tree.size();
    int left = node * 2, right = node * 2 + 1;
    if(left <= n)
    {
        if(!inOrder(tree, left, prev))
            return false;
    }

    if(prev != -1)
    {
        if(tree[prev] >= tree[node])
            return false;
    }
    prev = node;

    if(right <= n)
    {
        if(!inOrder(tree, right, prev))
            return false;
    }
    return true;
}

int main()
{
    vector<int> tree{-1};
    string str;
    cin >> str;
    int n = str.size();
    int left = 0;
    while(left < n)
    {
        int right = left;
        while(right < n && str[right] != ',')
            ++right;
        stringstream ss;
        if(str.substr(left, right - left) == "None")
            tree.push_back(-1);
        else
        {
            ss << str.substr(left, right - left);
            int x;
            ss >> x;
            tree.push_back(x);
        }
        left = right + 1;
    }
    if(tree[1] == -1)
    {
        cout << "True";
        return 0;
    }
    int prev = -1;
    if(inOrder(tree, 1, prev))
        cout << "True";
    else
        cout << "False";
}
