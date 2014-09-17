#include <iostream>
#include <cstdio>
using namespace std;

int day[100];
int main(void)
{
	int n;
	scanf("%d", &n);
	int N, M;
	//n为测试数据的组数
	while (n--)
	{
		//N为没有提交的天数，M为可以补交的天数
		scanf("%d%d", &N, &M);
		for (int i = 0; i < N; ++i)
			scanf("%d", &day[i]);
		if (M >= N)
			printf("100\n");
		else
		{
			int max = day[M];
			for (int i = M + 1; i < N; ++i)
			{
				if (day[i] - day[i - M - 1] >= max)
					max = day[i] - day[i - M - 1];
			}
			printf("%d\n", max-1);
		}
	}
	return 0;
}
