/*
 * 最近公共祖先三：将树转换为数组，然后使用MRQ-ST算法
 */
#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
struct Person
{
	string name;
	int rd;
	int father; //对于此题入度和父亲节点都不需要存储，如果没有指定树的根节点需要存储入度，一遍寻找根节点
	int level;
	vector<int> son;
	Person():name(""), rd(0), father(-1), level(0)
	{
		son.clear();
	}
};
const int N = 100000;
Person person[N];
map<string, int> mp;

int Level[18][N * 2 + 100]; //树转换为数组节点个数为2 * N + 1,
int number = 0;
void getTable(int root, int height) //将树转换为数组
{
	person[root].level = height;
	int size = person[root].son.size();
	for (int i = 0; i < size; ++i)
	{
		Level[0][number++] = root;
		getTable(person[root].son[i], height+1);
	}
	Level[0][number] = root;
	mp[person[root].name] = number;
	++number;
}
int main(void)
{
	int n;
	scanf("%d", &n);
	string father, son;
	int findex, sindex, index = 0;
	for (int i = 0; i < n; ++i)
	{
		cin >> father >> son;
		if (mp.find(father) == mp.end())
		{
			mp.insert(make_pair(father, index));
			findex = index;
			person[findex].name = father;
			++index;
		}
		else
			findex = mp[father];
		
		if (mp.find(son) == mp.end())
		{
			mp.insert(make_pair(son, index));
			sindex = index;
			person[sindex].name = son;
			++index;
		}
		else
			sindex = mp[son];
		++person[sindex].rd;
		person[findex].son.push_back(sindex);
		person[sindex].father = findex;
	}
	int root = 0; //记录根节点
	/*
	for (int i = 0; i < index; ++i)
	{
		if (person[i].rd == 0)
		{
			root = i;
			break;
		}
	} */
	getTable(root, 1);

	int level = log (number * 1.0) / log (2.0), next;
	for (int i = 1; i <= level; ++i) //注意测试条件是小于等于level
	{
		for (int j = 0 ;j < number; ++j)
		{
			Level[i][j] = Level[i-1][j];
			next = j + (1 << i - 1);
			if (next < number && person[Level[i - 1][next]].level < person[Level[i][j]].level)
				Level[i][j] = Level[i - 1][next];
		}
	}
	int m; //询问次数
	scanf("%d", &m);
	string son1, son2;
	int s1index, s2index, length, temp, result;
	while (m--)
	{
		cin >> son1 >> son2;
		s1index = mp[son1];
		s2index = mp[son2];
		if (s2index < s1index)
		{
			temp = s2index;
			s2index = s1index;
			s1index = temp;
		}
		length = log(s2index - s1index + 1.0) / log(2.0);
		s1index = Level[length][s1index];
		s2index = Level[length][s2index - (1 << length) + 1];
		result = person[s1index].level < person[s2index].level ? s1index : s2index;
		cout << person[result].name << endl;
	}
	return 0;
}
