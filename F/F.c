/* 2017 UESTC Training for Data Structures. Problem F - 奇迹的魔法啊，再度出现！, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define NUMWIDTH    32
#define BIT(x,i)    (((x)>>(31-(i)))&(1))
#define SETBIT(x,i) (x=(x)|(1<<(31-(i))))

#define MAXN    100001

int trie[MAXN<<5][2], ntrienode=1;

void build(int x)
{
    int i = 0, v = 1;
    for(i = 0;i < NUMWIDTH;++i)
    {
        int bit = BIT(x,i);     
        if( 0 == trie[v][bit] )
            trie[v][bit] = ++ntrienode;
        v = trie[v][bit];
    }
}
int query(int x)
{
    int i = 0, v = 1;
    int ans = 0;
    for(i = 0;i < NUMWIDTH;++i)
    {
        int bit = BIT(x,i);
        if( 0 == trie[v][!bit] ) /* can not to be 1 */
            v = trie[v][bit];
        else
        {
            SETBIT(ans, i);
            v = trie[v][!bit];
        }
    }
    return ans;
}

int main(void)
{
    int n = 0, m = 0;
    int ax = 0;

    scanf("%d", &n);
    while(n--)
    {
        scanf("%d", &ax);
        build(ax);
    }
    scanf("%d", &m);
    while(m--)
    {
        scanf("%d", &ax);
        printf("%d\n", query(ax));
    }

    return 0;
}
