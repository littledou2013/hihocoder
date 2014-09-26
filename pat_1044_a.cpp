#include <iostream>
#include <cstdio>
#include <memory.h>
using namespace std;
//value数组存储输入值
int dp[1001][1024];
int value[1001];
int bitcnt(int x)
{
	int ret = 0;
	while (x > 0)
	{
		++ ret;
		//求x中的最末的0去掉的表达式
		x &= (x - 1);
	}
	return ret;
}
int main(void)
{
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &value[i]);
	memset(dp, 0, sizeof(dp));
	int maxMask = 1 << m, bit;
	for (int i = 1; i <= n; ++i)
	{
		for (int mask = 0; mask < maxMask; ++mask)
		{
			if (dp[i-1][mask] > dp[i][mask>>1])
				dp[i][mask>>1] = dp[i-1][mask];
			bit = bitcnt(mask>>1);
			if (bit >= q) continue;
			/*
				参照别人代码写的，它的上面的bit是根据mask来求的，然后maxMask编程移两位，这个我自己不是很能理解，
				我先让mask右移一位后，求里面有多少1，也就是说在判断第i不选择时，它的前m-1位有多少被选择，如果少于q被选择，那么我可以选择i
				给右移一位的mask再加上一位1。
			*/
			int newmask = (mask >> 1) | (maxMask >> 1);
			if (dp[i - 1][mask] + value[i] > dp[i][newmask])
				dp[i][newmask] = dp[i - 1][mask] + value[i];
		}
	}
	int ret = 0;
	for (int mask = 0; mask < maxMask; ++mask)
		ret = max(ret, dp[n][mask]);
	printf("%d\n", ret);
	return 0;
}
