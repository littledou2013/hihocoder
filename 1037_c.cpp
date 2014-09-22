#include <iostream>
#include <cstdio>
using namespace std;
//存储数字三角形
const int N = (1 + 100) * 100 / 2 + 1;
int tree[N];
int maxAward = 0;
/*
	这种深度递归遍历会超时，究其原因，是因为这种递归遍历会遍历结点的次数达到2的n-1次方的级别，因为会出现重复遍历
	注意：这里如何理解为什么会出现重复遍历的情况
	比如下面数字三角形，数字代表的仅仅是位置，不代表权值。
			0
		  1   2
		3   4   5
	  6   7   8   9
    11  12  13  14  15
	如果已经深度递归了0-1-4-8-14这条路径，后面深度递归0-2-4-8-14时，如果0、1结点之和的权值大于那就重复遍历了4、8、14结点。
	如果想要使用深度遍历，就需要避免不必要的重复的搜索。但是对于极端的情况其时间复杂度并不会降低。
 */

void trans(int node, int award, int n, int level)
{
	//首先判断是否在规定的层内
	if (level > n)
	{
		if (award > maxAward)
			maxAward = award;
	}
	else
	{
		//在规定的层内需要去遍历它的两个子节点
		trans(node + level, award + tree[node], n, level + 1);
		trans(node + level + 1, award + tree[node], n, level + 1);
	}
}
int main(void)
{
	//n为数字三角形的层数
	int n;
	scanf("%d", &n);
	int index = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < i; ++j)
			scanf("%d", &tree[index++]);
	//去遍历这个数字三角形的每一条从根节点到叶节点的路径，也就是树的深度遍历
	trans(0, 0, n, 1);
	printf("%d\n", maxAward);
	return 0;
}
