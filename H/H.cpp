/* 2017 UESTC Training for Data Structures. Problem H - Rikka的烦恼, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

int mymax(int a, int b)
{
    return (a>b)?a:b;
}

#define MAXN    70001
#define MAXB    5

int N, M;
int A[MAXN];
int CHUNK;

int nmx[MAXB][MAXB];
vector<int> mx[MAXB][MAXB];

void pushup(int x0, int d, int o)
{
    mx[x0][d][o] = mymax(mx[x0][d][o<<1], mx[x0][d][o<<1|1]);
}

void build(int x0, int d, int o, int l, int r)
{
    if( r <= l )
    {
        mx[x0][d][o] = A[x0 + (l-1)*d];
    } else {
        int mid = l+r>>1;
        build(x0, d, o<<1, l, mid);
        build(x0, d, o<<1|1, mid+1, r);
        pushup(x0, d, o);
    }
}

/* p --> k */
void upd(int x0, int d, int k, int v, int o, int l, int r)
{
    if( r <= l )
    {
        mx[x0][d][o] += v;
    } else {
        int mid = l+r>>1;
        if( k <= mid ) upd(x0, d, k, v, o<<1, l, mid);
        else if (k > mid) upd(x0, d, k, v, o<<1|1, mid+1, r);
        pushup(x0, d, o);
    }
}

/* (x0,d) --> [L,R] */
int qmx(int x0, int d, int L, int R, int o, int l, int r)
{
    if( L <= l && r <= R )
    {
        return mx[x0][d][o];
    } else {
        int mid = l+r>>1;
        if( R <= mid ) return qmx(x0, d, L, R, o<<1, l, mid);
        if( L > mid ) return qmx(x0, d, L, R, o<<1|1, mid+1, r);
        return mymax(qmx(x0, d, L, R, o<<1, l, mid), qmx(x0, d, L, R, o<<1|1, mid+1, r));
    }
}

void build_trees(void)
{
    int i = 0, j = 0;
    if(N > 1)
        CHUNK = (int)(sqrt((double)N / log2(N)));
    else
        CHUNK = 1;
    if(CHUNK >= MAXB) CHUNK = MAXB-1;
    for(i = 1;i <= CHUNK;++i)
        for(j = i;j <= CHUNK;++j)
        {
            nmx[i][j] = (N-i)/j+1;
            mx[i][j].assign(nmx[i][j]<<2, 0);
            build(i, j, 1, 1, nmx[i][j]);
        }
}

void update(int p, int v)
{
    int d = 0;
    A[p] += v;
    for(d = 1;d <= CHUNK;++d)
    {
        int x0 = p % d; if(0 == x0) x0 = d;
        int k = (p-x0)/d + 1;
        upd(x0, d, k, v, 1, 1, nmx[x0][d]);
    }
}

int query(int xo, int d)
{
    if( d > CHUNK )
    {
        int ans = (1<<31);
        while(xo <= N)
        {
            ans = mymax(ans, A[xo]);
            xo += d;
        }
        return ans;
    } else {
        int x0 = xo % d; if(0 == x0) x0 = d;
        int k = (xo - x0) / d + 1;
        return qmx(x0, d, k, nmx[x0][d], 1, 1, nmx[x0][d]);
    }
}

int main(void)
{
    int i = 0;
    int op = 0, px = 0, vd = 0;

    scanf("%d", &N);
    for(i = 1;i <= N;++i)
        scanf("%d", A+i);
    build_trees();
    scanf("%d", &M);
    while(M--)
    {
        scanf("%d %d %d", &op, &px, &vd);
        if(0 == op)
        {
            update(px, vd);
        } else {
            printf("%d\n", query(px, vd));
        }
    }

    return 0;
}

