/* 最近公共祖先一:
 * 繁殖树，edge表示父子关系（只有父子关系，如果加上女子则就是繁殖图），多棵繁殖树便可简化为输入森林
 * 输入为edge：fatherName, sonName,首先重组树
 * 第一种方法是将name映射到数组中唯一的下标值作为key值
 * struct Node
 * {
 *     string name;
 *     int parent;
 *     vector<int> son;
 * }
 * 每输入一对父子，将其转换为其映射的key值，其父结点和子结点也对应key值。
 * 数组提前分配内存，无法提前预知所需内存。
 * 此题采用从子结点向祖先遍历的方式，记录遍历的祖先。
 * 
 */
 
 
 
 
 
 
#include <iostream>
#include <cstdio>
#include <string>
#include <map>
using namespace std;
/* 此方法：对于每个结点创建一个map元素，其键为string名字，其值为包含父结点以及访问标记。
 * 
 */
struct Node
{
	string parent;
	bool visit;
	Node():visit(false){}
};
map<string, Node> mp;
int main(void)
{
	int n, m;
	scanf("%d", &n);
	string str1, str2;
	while (n--)
	{
		cin >> str1 >> str2;
		mp[str2].parent = str1;
		//注意这里并没有为每个名字进行了隐射，作为根节点的string类型没有做为key放入map里。但是这个根节点对应的标记记录却是必须要有的
	}
	scanf("%d", &m);
	while (m--)
	{
		cin >> str1 >> str2;
		for (map<string, Node>::iterator iter = mp.begin(); iter != mp.end(); ++iter)
			iter->second.visit = false;
		//如果str1,str2循环到根节点，则将会创建根节点所对应的键值对放入到mp里。
		while (!str1.empty())
		{
			mp[str1].visit = true;
			str1 = mp[str1].parent;
		}
		while (!str2.empty() && mp[str2].visit == false)
			str2 = mp[str2].parent;
		if (str2.empty())
			printf("-1\n");
		else
			cout << str2 << endl;
	}
	return 0;
}




#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <string>
using namespace std;

map<string, string> mp; //son -> father
set<string> visit;
void getNearestAnceser(string son1, string son2)
{
	visit.clear();
	while (mp.find(son1) != mp.end())
	{
		visit.insert(son1);
		son1 = mp[son1];
	}
	visit.insert(son1);
	while (mp.find(son2) != mp.end())
	{
		if (visit.find(son2) != visit.end())
			break; 
		son2 = mp[son2];
	}
	if (visit.find(son2) == visit.end())
		cout << -1 << endl;
	else 
		cout << son2 << endl;
}


int main(void)
{
	int n;
	scanf("%d", &n);
	/* 输入n对父子关系，建立深林树,不存在两个相同的名字
	 * 由字符串来检索节点，说明字符串是每个节点的关键值
	 * 
	 */
	string father, son;
	for (int i = 0; i < n; ++i)
	{
		cin >> father >> son;
		mp.insert(make_pair(son, father));
	}
	int q;
	scanf("%d", &q);
	string son1, son2;
	for (int i = 0; i < q; ++i)
	{
		cin >> son1 >> son2;
		getNearestAnceser(son1, son2);
	}
	return 0;
}
