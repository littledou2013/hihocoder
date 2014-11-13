#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char str[11];
//存储根
/*
 * 方法一：此方法空间换时间存储Trie树的节点
 */
struct Node{
	int number;
	Node *next[26];
};
int main(void)
{
	int m;
	Node *tri = new Node;
	tri->number = 0;
	for(int i = 0; i < 26; ++i)
		tri->next[i] = NULL;
	scanf("%d",&m);
	while(m--)
	{
		scanf("%s",str);
		Node *head = tri;
		++(head->number);
		for(int i = 0; str[i] != 0; ++i)
		{
			if(head->next[str[i]-'a'] == NULL)
			{
				Node *next = new Node;
				next->number = 0;
				for(int i = 0; i < 26; ++i)
					next->next[i] = NULL;
				head->next[str[i]-'a'] = next;
			}	
			head = head->next[str[i] - 'a'];
			++(head->number);
		}
	}
	int n;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s",str);
		Node *head = tri;
		bool has_num = true;
		for(int i = 0; str[i] != 0; ++i)
		{
			if(head->next[str[i] - 'a'] == NULL)
			{
				has_num = false;
				break;
			}
			else
			{
				head= head->next[str[i] - 'a'];
			}
		}
		if(has_num)
			printf("%d\n",head->number);
		else
			printf("0\n");
	}
	return 0;
}
//
/*
 * 方法二：对上面代码进行简化，此方法同时增加了释放空间的代码
 */

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
struct Node
{
	int number;
	Node* sons[26];
	Node():number(1)
	{
		memset(sons, NULL, sizeof(sons));
	}
};
Node *buildTrie(int n)
{
	Node *root = new Node();
	root -> number = 0;
	char str[11];
	int i, j;
	Node *father;
	for (i = 0; i < n; ++i)
	{
		scanf("%s", str);
		father = root;
		/*
		for (j = 0; str[j]; ++j)
		{
			++father -> number;
			if (father -> sons[str[j] - 'a'] != NULL)
				father = father -> sons[str[j] - 'a'];
			else
				break;
		}
		if (!str[j]) //如果采用这种形式千万别忘了加上这一句，如果读入的单词是Trie里某个单词的前缀
		             //则读到最后一个字母时，father等于str的最后一个字母，但是str[j]不满足条件了，for循环结束，但是father的number没有加1
		            //这个小错误导致我答案错误，并且头痛半天
			++fahter -> number;
		*///或者将上述代码换成下面形式
		++father -> number;
		for (j = 0; str[j]; ++j)
		{
			if (father -> sons[str[j] - 'a'] != NULL)
			{
			  father = father -> sons[str[j] - 'a'];
			  ++father -> number;
			}
			else
				break;
		}
		while (str[j])
		{
			father -> sons[str[j] - 'a'] = new Node();
			father = father -> sons[str[j] - 'a'];
			++j;
		}
	}
	return root;
}
int findStr(char str[], Node *root)
{
	int i = 0;
	while (str[i])
	{
		if (root -> sons[str[i] - 'a'] == NULL)
			break;
		else
		{
			root = root -> sons[str[i] - 'a'];
			++i;
		}
	}
	if (str[i])
		return 0;
	else
		return root -> number;
}
void deleteTrie(Node *root)
{
	for (int i = 0; i < 26; ++i)
	{
		if (root -> sons[i] != NULL)
			deleteTrie(root->sons[i]);
	}
	delete(root);
}
int main(void)
{
	int n, m;
	scanf("%d", &n);
	Node *root = buildTrie(n);
	scanf("%d", &m);
	char str[27];
	for (int i = 0; i < m; ++i)
	{
		scanf("%s", str);
		printf("%d\n", findStr(str, root));
	}
	deleteTrie(root);
	return 0;
}

/*
 *  此方法就是便插入单词边申请相应的空间建立树
 */
 #include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
struct Node
{
    int number;  //记录单词数量
    char ch;   //记录节点
    vector<Node *> sons;
    Node (char _ch):number(1), ch(_ch)
    {
        sons.clear();
    }
};
int main(void)
{
    int n, m;
    scanf("%d", &n);
    char str[11];

	//构建Trie树
    Node *root = new Node(' ');  //根节点
	root -> number = 0;
    Node *father, *son;
    int i, j, k, size;
    //构建Trie树
    for (i = 0; i < n; ++i)
    {
        scanf("%s", str);
        father = root;
        j = 0;
	    	++father -> number;
        while (str[j])
        {
           
            size = father -> sons.size();
            for (k = 0; k < size; ++k)
            {
                if (father -> sons[k] -> ch == str[j])
                {
                    father = father ->sons[k];
                    break;
                }
            }
            if (k == size)
                break;
			    ++father -> number; //这里的++father->number同样要注意位置
            ++j;
        }
        while (str[j])
        {
            son = new Node(str[j]);
            father -> sons.push_back(son);
            father = son;
            ++j;
        }
    }
    scanf("%d", &m); //查找
    for (i = 0; i < m; ++i)
    {
        scanf("%s", str);
        father = root;
        j = 0;
        while (str[j])
        {
            size = father -> sons.size();
            for (k = 0; k < size; ++k)
            {
                if (father -> sons[k] -> ch == str[j])
                {
                    father = father -> sons[k];
                    break;
                }
            }
            if (k == size)
                break;
            ++j;
        }
        if (str[j])
            printf("0\n");
        else
            printf("%d\n", father -> number);
    }
    return 0;
}
