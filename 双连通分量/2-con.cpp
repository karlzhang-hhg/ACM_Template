#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
const int maxn=110000,maxm=210000;
inline int Min(int a,int b){return a<b?a:b;}
struct Edge {
	int y,ne;
};

struct Tarjan_Cut_Point {
	int d[maxn],low[maxn],index;
	int *st,ee;
	Edge *e;
	int n;
	int s[maxn],ss;
	int color[maxn],cc;//˫��ͨ����Ⱦɫ��0 .. cc-1��cc��ʾ��ͨ������
	int expt[maxn];//һ�����������ںܶ�ֿ飬����ÿ���ֿ�ֻ��Ψһһ�����������ĵ㣬������ߵ㡣�����鱣������������ߵ�
	//ע�������ǽ����ģ��ڱ�����ͬ��ɫ�ֿ��ʱ��Ҫ��������㣬�Լ��������õ��������ϢҪ��ԭ��
	bool isCut[maxn];//һ�����Ƿ��Ǹ��
	void init(Edge* _e,int* _st,int _ee,int _n) { //����˫��߼����Լ�����n,����0..n-1
		e=_e; st=_st; ee=_ee; n=_n;
		for (int i = 0; i<n; i++) {
			d[i]=low[i]=isCut[i]=0;
			color[i]=-1;
		}
		index=0;ss=-1;
		cc=0;
	}
	void dfs(int u,int fa) { //Tarjan����
		int i,son=0;
		d[u]=low[u]=++index;
		s[++ss]=u;
		for (i=st[u];i!=-1;i=e[i].ne) if (e[i].y!=fa) {
			if (d[e[i].y]==0) {
				son++;//ͳ�ƶ�����������Ҫ��
				dfs(e[i].y, u);
				low[u]=Min(low[u], low[e[i].y]);
				if (low[e[i].y]>=d[u]) {
					isCut[u] = 1;//������������õ��Ǹ��
					while (s[ss]!=e[i].y) {
						color[s[ss--]]=cc;
					}
					color[s[ss--]] = cc;//���ö�������һ�µ�ȫ����ջ����Щ�㣬����u����һ���ֿ�
					color[expt[cc]=u] = cc;//u��Ϊ����㱣��
					cc++;
				}
			}
			else {
				low[u]=Min(low[u],d[e[i].y]);
			}
		}
		if (u==fa) {
			isCut[u] = (son>1);//�����Ǹ������������������϶���
		}
	}
	void work() {
		for (int i = 0; i<n; i++) if (d[i]==0) {
			ss = -1;
			dfs(i, i);
			if (color[i]==-1) color[i] = cc++;//��ֹ����ͨ����ֻ��һ�������� ��������㲻��һ���ֿ������ĿҪ�����
		}
	}
};
Tarjan_Cut_Point T;
Edge e[maxm];
int st[maxn],ee;
void addedge(int x,int y) {
	e[ee].y=y;e[ee].ne=st[x];st[x]=ee++;
	e[ee].y=x;e[ee].ne=st[y];st[y]=ee++;
}
int color[maxn];
int h[maxn];
int que[maxn],head,tail;
int bfs(int k,int c) {
	que[0]=k;head=0;tail=1;
	while (head<tail) {
		k=que[head++];
		for (int i=st[k]; i!=-1; i=e[i].ne) if (T.color[e[i].y]==c||e[i].y==T.expt[c])
			if (color[e[i].y]==-1) {
				color[e[i].y] = 1-color[k];
				que[tail++] = e[i].y;
			}
			else if (color[e[i].y]==color[k]) return 1;
	}
	return 0;
}

char buf[1048576],*o;
int getint() {
	while (!isdigit(*o)) o++;
	int f = 0;
	while (isdigit(*o)) f=f*10+*o-'0',o++;
	return f;
}

int can[maxn];
int main() {
#ifdef _DEBUG
	freopen("D.in", "r", stdin);
#endif
	int n,m,i,j,k;
	int cass;
	for (scanf("%d\n",&cass);cass--;) {
		o = gets(buf);
		n = getint(); m = getint();
		for (i=0;i<n;i++) st[i]=color[i]=h[i]=-1,can[i]=0;
		ee=0;
		while (m--) {
			o = gets(buf);
			i = getint()-1; j = getint()-1;
			addedge(i,j);
		}

		T.init(e,st,ee,n);
		T.work();


		k=0;
		for (i=0;i<n;i++) {
			if (h[T.color[i]]==-1) {
				color[T.expt[T.color[i]]]=-1;
				color[i]=0;
				h[T.color[i]]=bfs(i,T.color[i]);
				can[T.expt[T.color[i]]]|=h[T.color[i]];
				color[T.expt[T.color[i]]]=-1;
			}
			can[i]|=h[T.color[i]];
		}
		for (i=0;i<n;i++)
			k+=can[i];
		printf("%d\n",k);
	}
	return 0;
}
