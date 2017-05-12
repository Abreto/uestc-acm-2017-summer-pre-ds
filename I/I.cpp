/* 2017 UESTC Training for Data Structures. Problem I - BanG Dreamer, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <utility>
#include <set>
#include <vector>

using namespace std;

#define MAXN    100001
typedef pair<int,int> pii;
typedef set<pii> spii;

int N;
int A[MAXN];

spii candidate_par;
vector<int> roots;
int nchild[MAXN];
int par[MAXN];
vector<int> seq[MAXN];

void create_root(int idx)
{
    par[idx] = idx;
    roots.push_back(idx);
    seq[idx].clear();
}
void attach_leaf(int leaf, spii::iterator it)
{
    int parnt = it->second;
    nchild[parnt]++;
    par[leaf] = par[parnt];
    seq[par[leaf]].push_back(leaf);
    if(nchild[parnt] == 2)
        candidate_par.erase(it);
}

void proccess(void)
{
    int i = 0, ai = 0;
    scanf("%d", &N);
    candidate_par.clear();
    roots.clear();
    for(i = 1;i <= N;++i)
    {
        scanf("%d", &ai);
        if( 0 == candidate_par.size() )
        {
            create_root(i);
        } else {
            spii::iterator it = candidate_par.lower_bound(make_pair(ai, i));
            if(it == candidate_par.begin())
            {
                if( it->first <= ai )
                    attach_leaf(i, it);
                else
                    create_root(i);
            } else {
                it--;
                attach_leaf(i, it);
            }
        }
        nchild[i] = 0;
        candidate_par.insert(make_pair(ai, i));
    }
    printf("%lu\n", roots.size());
    for(i = 0;i < roots.size();++i)
    {
        printf("%lu %d", seq[roots[i]].size()+1, roots[i]);
        for(ai = 0;ai < seq[roots[i]].size();++ai)
            printf(" %d", seq[roots[i]][ai]);
        printf("\n");
    }
}

int main(void)
{
    int T = 0;
    scanf("%d", &T);
    while(T--) proccess();
    return 0;
}
