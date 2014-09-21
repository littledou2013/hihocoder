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
		/*注意：本人也不太清楚数组根据下标寻址的时间是否比较大，
		但是好像用数先把数组寻址的数保存下来后再用，会比两次数组下标寻址块
		如使用下面代码会快些：
		left = award[i+1][j];//个人习惯将一些循环使用的变量放在循环之外声明，
				    //这样可以减少程序新建一个变量然后又销毁的时间
		right = award[i+1][j+1];
		award[i][j] += (left > right ? left : right);
		*/
		
			award[i][j] += (award[i + 1][j] > award[i + 1][j + 1] ? award[i + 1][j] : award[i + 1][j + 1]);

	printf("%d\n", award[0][0]);
	return 0;
}
