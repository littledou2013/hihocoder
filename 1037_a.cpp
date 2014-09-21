#include <iostream>
#include <cstdio>
using namespace std;
/*此方法使用的数组存储的方式，由于每个结点的位置都是有规律的，
比如第i层的第j个结点存放在的下标为(1+i-1)*(i-1)/2+j-1（这里第一个数据存放的下标为0)
*/
const int N = (1 + 200) * 200 / 2;
int award[N];

int main(void)
{
	int n;
	scanf("%d", &n);
	int length = (1 + n) * n / 2;
	for (int i = 0; i < length; ++i)
		scanf("%d", &award[i]);
	//从倒数第二层最后一个结点开始计算以此结点为根的某一条具有award之和的路径，只需计算此award之后的最大就可以
	//award最后一个元素的下标为index - 1, 最后一层的第一个元素的下标应该是length - 1 - n + 1 = length - n，倒数第二层的最后一个元素为length - n - 1
	int index = length - n; //index 指向最后一层的第一个元素
	for (int i = n - 1; i >= 0; --i)
	{
		//index的两个子元素分为index + i, index + i + 1;
		//第i层有i个元素
		for (int j = 0; j < i; ++j)
		{
			--index;
			award[index] += max(award[index + i], award[index + i + 1]);
		}	
	}
	printf("%d\n", award[0]);
	return 0;
}
