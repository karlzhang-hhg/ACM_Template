#include <iostream>
using namespace std;
const int maxn=1000,maxm=maxn*8*4;//��󶥵����ͱ���
const int maxl=999999999;
inline int Min(int a,int b){return a<b?a:b;}
inline int Max(int a,int b){return a>b?a:b;}
struct st
{
	int y,d;
	int ne;
	int bro;
	int f;
} e[maxm];
int ee;
int st[maxn];
int n,m;
void addedge(int x,int y,int d,int f)
{//������x��y�����һ������d,����f�ı�
	e[ee].y=y;e[ee].d=d;e[ee].ne=st[x];e[ee].f=f;st[x]=ee++;
	e[ee].y=x;e[ee].d=-1*d;e[ee].ne=st[y];e[ee].f=0;st[y]=ee++;
	e[ee-2].bro=ee-1;e[ee-1].bro=ee-2;
}
int d[maxn],p[maxn];
//spfa���õ�������̾���(��������൱��cost)��·����¼֮ǰ��һ���ڵ�
int c[maxn];//spfa��������:�Ƿ��ڶ�����
int que[maxn],head,tail;//spfaר�ö���
int spfa(int sx,int ex)//��sx��ex��һ�η�������
{//���û������·�ͷ���maxl ���򷵻ط���
	int i,j,k;
	for (i=0;i<maxn;i++) d[i]=maxl;//��ʼ��dΪmaxl
	memset(c,0,sizeof(c));//��ʼ����û��
	d[sx]=0;
	que[head=0]=sx;tail=1;
	c[sx]=1;
	while (head!=tail)//spfa��ʼ
	{
		k=que[head++];head%=maxn;
		c[k]=0;
		for (i=st[k];i!=-1;i=e[i].ne) if (e[i].f)
			if (d[k]+e[i].d<d[e[i].y])
			{
				d[e[i].y]=d[k]+e[i].d;
				p[e[i].y]=i;
				if (c[e[i].y]==0)
				{
					c[e[i].y]=1;
					if (e[i].d<0){head=(head-1+maxn)%maxn;que[head]=e[i].y;}
					else 
					{que[tail++]=e[i].y;tail%=maxn;}
				}
			}
	}
	if (d[ex]==maxl) return maxl;//����޷������յ㷵��maxl
	k=maxl;
	for (i=ex;i!=sx;i=e[e[p[i]].bro].y)	k=Min(k,e[p[i]].f);//������
	for (i=ex;i!=sx;i=e[e[p[i]].bro].y)//���ӷ����
	{
		e[p[i]].f-=k;
		e[e[p[i]].bro].f+=k;
	}
	return d[ex]*k;//���ط���Ϊ����С*·������(cost�ۼ�)
}
