/* 2017 UESTC Training for Data Structures. Problem K - 老司机破阵, by Abreto<m@abreto.net>. */
#include <stdio.h>

typedef long long int ll;

ll mymax(ll a, ll b)
{
    return (a>b)?a:b;
}

#define MAXN 100001

int N;
int E[MAXN];
int brk[MAXN];
ll ans[MAXN];

int set[MAXN];
ll sum[MAXN];
int par[MAXN];
int fdr(int x)
{
    return (par[x] == x) ? x : (par[x] = fdr(par[x]));
}
void uni(int x, int y)
{
    int fx = fdr(x), fy = fdr(y);
    if(fx != fy)
    {
        sum[fy] += sum[fx];
        par[fx] = fy;
    }
}

int main(void)
{
    int i = 0, j = 0;
    const int dir[2] = {-1,1};

    scanf("%d", &N);
    for(i = 1;i <= N;++i)
        scanf("%d", E+i);
    for(i = 0;i < N;++i)
        scanf("%d", brk+i);
    for(i = 1;i <= N;++i)
        par[i] = i;
    
    ans[N-1] = 0;
    for(i = N-1;i > 0;i--)
    {
        int pos = brk[i];
        sum[pos] = E[pos];
        set[pos] = 1;
        for(j = 0;j < 2;++j)
        {
            int next = pos + dir[j];
            if(next >= 1 && next <= N && set[next])
            {
                uni(pos, next);
            }
        }
        // int boom!!
        ans[i-1] = mymax(sum[fdr(pos)], ans[i]);
    }

    for(i = 0;i < N;++i)
        printf("%lld\n", ans[i]);

    return 0;
}
