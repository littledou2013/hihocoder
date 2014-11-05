#include <iostream>
#include <string>
#include <map>
#include <cstdio>
#include <vector>
using namespace std;

#define MP make_pair
struct Person
{
	string name;
	vector<int> sons;
	Person() : name("")
	{
		sons.clear();
	}
};
const int N = 100002; //还要注意N的取值是节点的个数，而题目中的N的范围是边的个数，节点的个数应该比边数大1
Person person[N];
map<string, int> mp;
vector<pair<int, int> >vec[N];
string anc[N];
int f[N];
bool vit[N] = {false};
int Find(int x)
{
    if(f[x]==x) return x;
    else return f[x]=Find(f[x]);
}
void Union(int x,int y)
{
    f[y] = x;  //别人算法里面把这里的代码写的很啰嗦，个人认为由于是从子节点回溯会父节点的，可以把子节点的集合直接合并到父节点中
			  //这里一定要想清楚为什么一句话就可以解决了，首先我们能确定y是x的子节点，并且y子树已经合并成了一个集合，并且集合的根就是y
	          //但是对于其他的并查集就不可以这么来，需要依题意决定
}
 
void lca(int u)
{
    f[u]=u;
	int size = person[u].sons.size();
    for(int i = 0; i < size; ++i)
    {
        lca(person[u].sons[i]);
        Union(u,person[u].sons[i]);
    }
    vit[u]=true;
	size = vec[u].size();
    for(int i = 0; i < size; ++i)
    {
        if (vit[vec[u][i].first])
            anc[vec[u][i].second] = person[Find(f[vec[u][i].first])].name;
    }
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
			mp.insert(MP(father, index));
			findex = index; 
			person[findex].name = father;
			++index;
		}
		else
			findex = mp[father];
		if (mp.find(son) == mp.end())
		{
			mp.insert(MP(son, index));
			sindex = index;
			person[sindex].name = son;
			++index;
		}
		else
			sindex = mp[son];
		person[findex].sons.push_back(sindex);
	}

	int m; //询问次数
	scanf("%d", &m);
	string son1, son2;
	int s1index, s2index;
	for (int i = 0; i < m; ++i)
	{
		cin >> son1 >> son2;
		s1index = mp[son1];
		s2index = mp[son2];
		vec[s1index].push_back(MP(s2index, i));
		if (s1index != s2index)
			vec[s2index].push_back(MP(s1index, i));
	}
	lca(0);
	for (int i = 0; i < m; ++i)
		cout << anc[i] << endl;
	return 0;
}
