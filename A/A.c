/* 2017 UESTC Training for Data Structures. Problem A - An easy problem A, by Abreto<m@abreto.net>. */
#include <stdio.h>

int mymin(int a, int b)
{
    return (a<b)?a:b;
}
int mymax(int a, int b)
{
    return (a>b)?a:b;
}

#define MAXN    50001

int N, Q;
int a[MAXN];
int min[MAXN<<2], max[MAXN<<2];

void build(int o, int l, int r) /* [l,r] */
{
    if( r <= l )
    {
        min[o] = max[o] = a[l];
    } else {
        int mid = l + (r-l)/2;
        build(o*2,l,mid);
        build(o*2+1,mid+1,r);
        min[o] = mymin(min[o*2], min[o*2+1]);
        max[o] = mymax(max[o*2], max[o*2+1]);
    }
}

typedef struct
{
    int mi,ma;
}mm;

mm query(int L, int R, int o, int l, int r)
{
    if( L <= l && r <= R )
    {
        mm ans = {min[o], max[o]};
        return ans;
    } else {
        int mid = l + (r-l)/2;
        if( R <= mid )
        {
            return query(L,R,o*2,l,mid);
        } else if ( L > mid ) {
            return query(L,R,o*2+1,mid+1,r);
        } else {
            mm t1,t2;
            mm ans;
            t1 = query(L,R,o*2,l,mid);
            t2 = query(L,R,o*2+1,mid+1,r);
            ans.mi = mymin(t1.mi,t2.mi);
            ans.ma = mymax(t1.ma,t2.ma);
            return ans;
        }
    }
}

int main(void)
{
    int i = 0;
    int L = 0, R = 0;
    mm ans;

    scanf("%d%d", &N, &Q);
    for(i = 1;i <= N;++i)
        scanf("%d", a+i);

    build(1, 1, N);
    while(Q--)
    {
        scanf("%d%d", &L, &R);
        ans = query(L,R,1,1,N);
        printf("%d\n", ans.ma-ans.mi);
    }

    return 0;
}
