/* 2017 UESTC Training for Data Structures. Problem B - An easy problem B, by Abreto<m@abreto.net>. */
#include <stdio.h>

int mymax(int a, int b)
{
    return (a>b)?a:b;
}
int mymax3(int a, int b, int c)
{
    return mymax(a, mymax(b,c));
}

typedef struct
{
    int maxl[2];
    int lcon[2];
    int rcon[2];
}no;
/* write nocpy() if neccessary */

#define MAXN    100002

int N, M;
int A[MAXN];

no st[MAXN<<2];
int rev[MAXN<<2];

void maintain(int o, int l, int r)
{
    int i = 0;
    int mid = l + (r-l)/2;
    int lc = o*2, rc = o*2+1;
    for(i = 0;i < 2;++i)
    {
        st[o].maxl[i] = mymax3(st[lc].maxl[i], st[rc].maxl[i], st[lc].rcon[i]+st[rc].lcon[i]);
        if( st[lc].lcon[i] == mid-l+1 ) st[o].lcon[i] = mid-l+1+st[rc].lcon[i];
        else st[o].lcon[i] = st[lc].lcon[i];
        if( st[rc].rcon[i] == r-mid ) st[o].rcon[i] = r-mid+st[lc].rcon[i];
        else st[o].rcon[i] = st[rc].rcon[i];
    }
}

void build(int o, int l, int r) /* [l,r] */
{
    if( r <= l ) /* leaf */
    {
        st[o].maxl[A[l]] = 1;
        st[o].lcon[A[l]] = 1;
        st[o].rcon[A[l]] = 1;
        rev[o] = 0;
    } else {
        int mid = l + (r-l)/2;
        build(o*2, l, mid);
        build(o*2+1, mid+1, r);
        maintain(o, l, r);
    }
}

void upd(int o)
{
    int i = 0;
    no tmp = st[o];
    rev[o] = !(rev[o]);
    for(i = 0;i < 2;++i)
    {
        st[o].maxl[i] = tmp.maxl[!i];
        st[o].lcon[i] = tmp.lcon[!i];
        st[o].rcon[i] = tmp.rcon[!i];
    }
}

void pushdown(int o)
{
    int lc = o*2, rc = o*2+1;
    if( rev[o] )
    {
        upd(lc);
        upd(rc);
        rev[o] = 0;
    }
}

void reverse(int L, int R, int o, int l, int r)
{
    int lc = o*2, rc = o*2+1;
    if(L <= l && r <= R)
    {
        upd(o);
    } else {
        int mid = l + (r-l)/2;
        pushdown(o);
        if( L <= mid ) reverse(L, R, lc, l, mid);
        if( R > mid ) reverse(L, R, rc, mid+1, r);
        maintain(o, l, r);
    }
}

no query(int L, int R, int o, int l, int r)
{
    if( L <= l && r <= R )
    {
        return st[o];
    } else {
        int i = 0;
        no t1, t2, ans;
        int mid = l + (r-l)/2;
        pushdown(o);
        if (R <= mid) return query(L, R, o*2, l, mid);
        if( L > mid ) return query(L, R, o*2+1, mid+1, r);
        t1 = query(L, R, o*2, l, mid);
        t2 = query(L, R, o*2+1, mid+1, r);
        for(i = 0;i < 2;++i)
        {
            ans.maxl[i] = mymax3(t1.maxl[i], t2.maxl[i], t1.rcon[i]+t2.lcon[i]);
            if( t1.lcon[i] == mid-l+1 ) ans.lcon[i] = mid-l+1+t2.lcon[i];
            else ans.lcon[i] = t1.lcon[i];
            if( t2.rcon[i] == r-mid ) ans.rcon[i] = r-mid+t1.rcon[i];
            else ans.rcon[i] = t2.rcon[i];
        }
        return ans;
    }
}

int main(void)
{
    int i = 0;
    int K = 0, L = 0, R = 0;

    scanf("%d", &N);
    for(i = 1;i <= N;++i)
        scanf("%d", A+i);
    build(1, 1, N);
    scanf("%d", &M);
    while(M--)
    {
        scanf("%d%d%d", &K, &L, &R);
        if(K == 1)
        {
            reverse(L, R, 1, 1, N);
        } else {
            no ans = query(L, R, 1, 1, N);
            printf("%d\n", ans.maxl[1]);
        }
    }

    return 0;
}
