#include <stdio.h>

#define MAXN    1000002
#define MAXP    (MAXN<<1)
#define nt(x)   (MAXP-x)

int N, M;
int par[MAXP];

int fdr(int x)
{
    return (par[x]==x)?x:(par[x]=fdr(par[x]));
}
void uni(int x, int y)
{
    par[fdr(x)] = fdr(y);
}

int main(void)
{
    int i = 0;
    int t = 0, a = 0, b = 0;

    for(i = 0;i < MAXP;++i)
        par[i] = i;
    
    scanf("%d %d", &N, &M);
    while(M--)
    {
        scanf("%d %d %d", &t, &a, &b);
        if( 1 == t )
        {
            uni(a, b);
            uni(nt(a), nt(b));
        } else if (0 == t) {
            uni(a, nt(b));
            uni(nt(a), b);
        }
        if( fdr(a)==fdr(nt(a)) || fdr(b)==fdr(nt(b)) )
            return !printf("NO\n");
    }
    printf("YES\n");
    return 0;
}
