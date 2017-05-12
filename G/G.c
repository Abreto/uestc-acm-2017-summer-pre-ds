/* 2017 UESTC Training for Data Structures. Problem G - 加帕里公园的friends, by Abreto<m@abreto.net>. */
#include <stdio.h>

int mymax(int a, int b)
{
    return (a>b)?a:b;
}
int mymax3(int a, int b, int c)
{
    return mymax(a, mymax(b,c));
}

#define MAXN    500001

typedef struct
{
    int max;
    int lm, rm;
    int sum;
}no_t;
no_t merge(no_t no1, no_t no2)
{
    no_t ans = {0,0,0,0};
    ans.max = mymax3(no1.max, no2.max, no1.rm+no2.lm);
    ans.lm = mymax(no1.lm, no1.sum+no2.lm);
    ans.rm = mymax(no2.rm, no2.sum+no1.rm);
    ans.sum = no1.sum + no2.sum;
    return ans;
}

int A[MAXN];
no_t st[MAXN<<2];

void maintain(int o)
{
    st[o] = merge(st[o*2], st[o*2+1]);
}

void build(int o, int l, int r)
{
    if(r <= l)
    {
        st[o] = (no_t){A[l], A[l], A[l], A[l]};
    } else {
        int mid = (l+r)>>1;
        build(o*2, l, mid);
        build(o*2+1, mid+1, r);
        maintain(o);
    }
}

void update(int pos, int x, int o, int l, int r)
{
    if( r <= l )
    {
        st[o] = (no_t){x,x,x,x};
    } else {
        int mid = (l+r)>>1;
        if( pos <= mid ) update(pos, x, o*2, l, mid);
        else if (pos > mid) update(pos, x, o*2+1, mid+1, r);
        maintain(o);
    }
}

no_t query(int L, int R, int o, int l, int r)
{
    if( L <= l && r <= R )
        return st[o];
    else
    {
        int mid = (l+r)>>1;
        if( R <= mid ) return query(L, R, o*2, l, mid);
        if( L > mid) return query(L, R, o*2+1, mid+1, r);
        return merge(query(L, R, o*2, l, mid), query(L, R, o*2+1, mid+1, r));
    }
}

int
main(void)
{
    int i = 0, op1 = 0, op2 = 0;
    int n = 0, m = 0;

    scanf("%d %d", &n, &m);
    for(i = 1;i <= n;++i)
        scanf("%d", A+i);
    build(1, 1, n);

    while(m--)
    {
        scanf("%d %d %d", &i, &op1, &op2);
        if(1 == i)
            printf("%d\n", query(op1,op2,1,1,n).max);
        else if (2 == i)
            update(op1, op2, 1, 1, n);
    }

    return 0;
}
