#include <iostream>
#include <cstdio>
using namespace std;

const int N = (1 + 100) * 100 / 2;
int award[N];
/*
	此方法使用的是自上而下的方法，在输入结点的同时计算从根节点到此结点的路径的值之和，最后在遍历叶子节点的值，便可求出最大值
*/
int main(void)
{
	int n;
	scanf("%d", &n);
	scanf("%d",&award[0]);
	int sum = 0, num = 1, t;
	for (int i = 1; i < n; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			scanf("%d", &t);
			if (j == 0)
				award[num] = award[num - i] + t;
			else if (j == i)
				award[num] = award[num - i - 1] + t;
			else
				award[num] = (award[num - i] > award[num - i - 1] ? award[num - i] : award[num - i - 1]) + t;
			++num;
		}
	}
	for (int i = 0; i < n; ++i)
	{
		--num;
		if (award[num] > sum)
			sum = award[num];
	}
	printf("%d\n", sum);
}
