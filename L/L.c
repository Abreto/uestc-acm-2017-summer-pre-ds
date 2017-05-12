/* 2017 UESTC Training for Data Structures. Problem L - 老司机的奇幻漂流, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define MAXN    50001
#define MAXP    (MAXN*3)
#define A(x)    (x)
#define B(x)   (MAXN+(x))
#define C(x)   (MAXN*2+(x))

int par[MAXP];
int fdr(int x)
{
    return (par[x] == x) ? x : (par[x] = fdr(par[x]));
}
void uni(int x, int y)
{
    par[fdr(x)] = fdr(y);
}

int main(void)
{
    int i = 0;
    int N = 0, M = 0;
    int t = 0, x = 0, y = 0;

    scanf("%d %d", &N, &M);
    for(i = 0;i < MAXP;++i)
        par[i] = i;
    for(i = 0;i < M;++i)
    {
        scanf("%d %d %d", &t, &x, &y);
        if( x > N || y > N )
            printf("%d ", i+1);
        else
        {
            int fax = fdr(A(x)), fay = fdr(A(y));
            int fbx = fdr(B(x)), fby = fdr(B(y));
            int fcx = fdr(C(x)), fcy = fdr(C(y));
            if(1 == t)
            {
                if( fax == fby || fax == fcy )
                {
                    printf("%d ", i+1);
                    continue;
                }
                uni(A(x), A(y));
                uni(B(x), B(y));
                uni(C(x), C(y));
            } else if (2 == t) {
                if( x == y || fax == fay || fcy == fax )
                {
                    printf("%d ", i+1);
                    continue;
                }
                uni(A(x), B(y));
                uni(B(x), C(y));
                uni(C(x), A(y));
            }
        }
    }

    return puts(""),0;
}