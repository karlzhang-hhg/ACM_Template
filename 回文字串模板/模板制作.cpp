#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
inline int Min(int a,int b) {return a<b?a:b;}
inline int Max(int a,int b) {return a>b?a:b;}
void cal(int pos,char* s,int* len,int slen)//�������鳤�ȼӱ� �м�����˲�ո�� len��ÿ����Ϊ�Գ���Ļ���һ�볤�� slen���ַ�����
{
    int i,ans;
    bool flag;
    flag = true;
    ans=0;
    for(i=1;flag;i++)
        if(pos-i>=0 && pos+i<slen)
            if(s[pos-i]==s[pos+i])
            {
                i+=Min(len[pos-i],len[pos+i]);
                ans=i;
            }
            else flag=false;
        else flag=false;
    len[pos]=ans;
}

void dfs(int l,int r,char* s,int* len,int slen)
{
    if(l>r) return ;
    int mid = (l+r)/2;
    cal(mid,s,len,slen);
    dfs(l,mid-1,s,len,slen);
    dfs(mid+1,r,s,len,slen);
}
void work(char* s,int* len)
{//����δ�ӹ���s(ע��s���治���пո� �����޸ļ����) �����len �������鳤�ȿ���2��+3����
	int j;
	int l=strlen(s);
	memset(len,0,sizeof(int)*(l*2+2));
	for (j=l-1;j>=0;j--)
	{
		s[j*2+1]=s[j];
		s[j*2]=' ';
	}
	s[l*2]=' ';
	s[l*2+1]=0;
	dfs(0,l*2,s,len,l*2+1);
}
