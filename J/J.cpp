/* 2017 UESTC Training for Data Structures. Problem J - wtmsb, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int main(void)
{
    int i = 0, j = 0;
    int ai = 0;
    int ans = 0;
    priority_queue<int, vector<int>, greater<int> > q;

    scanf("%d", &i);
    while(i--)
    {
        scanf("%d", &ai);
        q.push(ai);
    }
    while(q.size()>1)
    {
        i = q.top(); q.pop();
        j = q.top(); q.pop();
        ans += (i+j);
        q.push(i+j);
    }

    printf("%d\n", ans);
    return 0;
}
