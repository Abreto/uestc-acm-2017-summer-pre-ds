/* 2017 UESTC Training for Data Structures. Problem M - 老司机的毒奶, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <functional>
#include <set>

using namespace std;

int main(void)
{
	int i = 0, n = 0;
	set<int, greater<int> > s;
	int modified = 0;

	scanf("%d", &n);
	for (i = 0; i < n; ++i)
	{
		int tmp = 0;
		scanf("%d", &tmp);
		s.insert(tmp);
	}

	modified = 1;
	while (modified)
	{
		modified = 0;
		auto it = s.begin();
		int cur = (*it)/2, changeto = *it;
		while (cur)
		{
			if (!s.count(cur))
			{
				changeto = cur;
				break;
			}
			cur /= 2;
		}
		if (changeto != (*it))
		{
			s.erase(it);
			s.insert(changeto);
			modified = 1;
		}
	}

	printf("%d\n", *(s.begin()));
	return 0;
}
