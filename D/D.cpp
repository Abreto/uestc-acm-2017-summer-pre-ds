/* 2017 UESTC Training for Data Structures. Problem D - Washi与Sonochi的约定, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <algorithm>

using namespace std;

#define MAXN    100001
struct point_t
{
    int x,y;
    friend int operator<(const point_t p1, const point_t p2)
    {
        return (p1.x==p2.x) ? (p1.y < p2.y) : (p1.x < p2.x);
    }
};

int n;
point_t pnts[MAXN];
int nrank[MAXN];

#define LOWBIT(x)   (x&(-(x)))
int fen[MAXN];
void update(int i)
{
    while(i <= n)
    {
        fen[i]++;
        i += LOWBIT(i);
    }
}
int sum(int i)
{
    int ret=0;
    while(i > 0)
    {
        ret += fen[i];
        i -= LOWBIT(i);
    }
    return ret;
}

int main(void)
{
    int i = 0;

    scanf("%d", &n);
    for(i = 0;i < n;++i)
        scanf("%d %d", &(pnts[i].x), &(pnts[i].y));
    
    sort(pnts, pnts+n);
    for(i = 0;i < n;++i)
    {
        nrank[sum(pnts[i].y)]++;
        update(pnts[i].y);
    }

    for(i = 0;i < n;++i)
        printf("%d\n", nrank[i]);
    return 0;
}
