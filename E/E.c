/* 2017 UESTC Training for Data Structures. Problem E - 曜酱的心意, by Abreto<m@abreto.net>. */
#include <stdio.h>

typedef long long int ll;
ll avs(ll x)
{
    return (x<0)?(-x):x;
}

#define MAXN    100001

int n;
int a[MAXN], tr[MAXN];
int fen[MAXN];

#define lowbit(x)   ((x)&(-(x)))
void init()
{
    int i = 0;
    for(i = 1;i <= n;++i)
        fen[i] = 0;
}
void upd(int i)
{
    while(i <= n)
    {
        fen[i]++;
        i += lowbit(i);
    }
}
int sum(int i)
{
    int ret=0;
    while(i > 0)
    {
        ret += fen[i];
        i -= lowbit(i);
    }
    return ret;
}

int main(void)
{
    int i = 0, j = 0, bi = 0;
    ll npar = 0;

    scanf("%d", &n);
    for(i = 0;i < n;++i)
    {
        scanf("%d", a+i);
    }
    for(i = 0;i < n;++i)
    {
        scanf("%d", &bi);
        tr[bi] = n-i;
    }
    for(i = 0;i < n;++i)
    {
        a[i] = tr[a[i]];
        npar += sum(a[i]);
        upd(a[i]);
    }

    printf("%lld\n", npar);
    return 0;
}
