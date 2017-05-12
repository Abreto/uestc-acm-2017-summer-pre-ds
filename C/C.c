/* 2017 UESTC Training for Data Structures. Problem C - An easy problem C, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define MAXN    100001
typedef long long int ll;

typedef struct
{
    ll mul,add;
}lazy_t;

int N, P, M;
int A[MAXN];

ll sum[MAXN<<2];
lazy_t lazy[MAXN<<2];

void build(int o, int l, int r) /* [l,r] */
{
    lazy[o].mul = 1; lazy[o].add = 0;
    if( r <= l )
    {
        sum[o] = A[l] % P;
    } else {
        int mid = l + (r-l)/2;
        build(o*2, l, mid);
        build(o*2+1, mid+1, r);
        sum[o] = (sum[o*2] + sum[o*2+1]) % P;
    }
}

void upd(lazy_t act, int o, int l, int r) /* perform act on all in [l,r] */
{
    sum[o] = (sum[o] * act.mul) % P;
    sum[o] = (sum[o] + (ll)(r-l+1)*act.add) % P;
    lazy[o].mul = (lazy[o].mul * act.mul) % P;
    lazy[o].add = (lazy[o].add * act.mul) % P;
    lazy[o].add = (lazy[o].add + act.add) % P;
}
void pushdown(int o, int l, int r)
{
    if( lazy[o].mul != 1 || lazy[o].add != 0 )
    {
        int mid = l + (r-l)/2;
        int lc = o*2, rc = o*2+1;
        upd((lazy_t){lazy[o].mul, lazy[o].add}, lc, l, mid);
        upd((lazy_t){lazy[o].mul, lazy[o].add}, rc, mid+1, r);
        lazy[o].mul = 1;
        lazy[o].add = 0;
    }
}

void perform(lazy_t act, int L, int R, int o, int l, int r)
{
    if( L <= l && r <= R )
    {
        upd(act, o, l, r);
    } else {
        int mid = l + (r-l)/2;
        pushdown(o, l, r);
        if(L <= mid) perform(act, L, R, o*2, l, mid);
        if(R > mid) perform(act, L, R, o*2+1, mid+1, r);
        sum[o] = (sum[o*2] + sum[o*2+1]) % P;
    }
}

ll query(int L, int R, int o, int l, int r)
{
    if( L <= l && r <= R )
    {
        return sum[o] % P;
    } else {
        int mid = l + (r-l)/2;
        int lc = o*2, rc = o*2+1;
        pushdown(o, l, r);
        if( R <= mid ) return query(L, R, lc, l, mid);
        if( L > mid ) return query(L, R, rc, mid+1, r);
        return (query(L, R, lc, l, mid)+query(L, R, rc, mid+1, r)) % P;
    }
}

int main(void)
{
    int i = 0;
    int op = 0, L = 0, R = 0;

    scanf("%d %d", &N, &P);
    for(i = 1;i <= N;++i)
        scanf("%d", A+i);
    build(1, 1, N);

    scanf("%d", &M);
    while(M--)
    {
        scanf("%d %d %d", &op, &L, &R);
        if( 3 == op )
        {
            printf("%lld\n", query(L, R, 1, 1, N));
        } else {
            int num = 0;
            scanf("%d", &num);
            if(2 == op && 0 == num) continue;
            if(1 == op) perform((lazy_t){num,0}, L, R, 1, 1, N);
            else if (2 == op) perform((lazy_t){1,num}, L, R, 1, 1, N);
        }
    }

    return 0;
}
