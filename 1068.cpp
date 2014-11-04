/*
 * 使用RMQ-ST算法解决区间最小值是最快捷的算法
 */
 
 /* 
 * 使用MRQ-ST算法解决这个题目，比较重要的是元素数据的修改
 */

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 1000002;
const int Level = 20;
int weight[Level][N];

int main(void)
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &weight[0][i]);
	int level = log(n * 1.0) / log (2.0);
	int next;
	for (int i = 1; i <= level; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			weight[i][j] = weight[i-1][j];
			next = j + (1 << (i - 1)); //注意加减号比移位运算符优先级高
			if (next <= n && weight[i-1][next] < weight[i][j])
				weight[i][j] = weight[i-1][next];
		}
	}
	int q, left, right, length; 
	scanf("%d", &q);
	for (int i = 0; i < q; ++i)
	{
		scanf("%d%d", &left, &right);
		length = log(right - left + 1.0) / log (2.0);
		printf("%d\n", min(weight[length][left], weight[length][right - (1 << length) + 1]));
	}
	return 0;
}
