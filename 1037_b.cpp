#include <iostream>
#include <cstdio>
using namespace std;
/*
	这个数字三角形层数最大为100,使用二维数组来存储，空间的冗余换时间
*/
const int N = 100;
int award[N][N];
int main(void)
{
	int n;
	scanf("%d", &n);
	//i表示的是第i+1层
	for (int i = 0; i < n; ++i)
	//i层表示的第i+1层具有i+1个结点
		for (int j = 0; j <= i; ++j)
			scanf("%d", &award[i][j]);
	for (int i = n - 2; i >= 0; --i)
		for (int j = 0; j <= i; ++j)
			award[i][j] += (award[i + 1][j] > award[i + 1][j + 1] ? award[i + 1][j] : award[i + 1][j + 1]);
	printf("%d\n", award[0][0]);
	return 0;
}
