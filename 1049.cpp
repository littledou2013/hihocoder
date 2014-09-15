/*
  #1049:后序遍历
  由前序遍历和中序遍历求后序遍历
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char preStr[27];
char inStr[27];

void getTree(int preI, int preJ, int inI, int inJ)
{
	if (preI > preJ)
		return ;
    int rootIndex = inI;
    while (rootIndex <= inJ && inStr[rootIndex] != preStr[preI])
         ++rootIndex;
    getTree(preI + 1, preI + rootIndex - inI, inI, rootIndex - 1);
    getTree(preI + rootIndex - inI + 1, preJ, rootIndex + 1, inJ);
    printf("%c", preStr[preI]);
}
 
int main(void)
{
    scanf("%s%s", preStr, inStr);
    getTree(0, strlen(preStr) - 1, 0, strlen(inStr) - 1);
    printf("\n");
    return 0;
}
