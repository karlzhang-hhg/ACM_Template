#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
const int maxn=101000,maxm=1000000;
inline int Min(int a,int b){return a<b?a:b;}
struct Edge{
	int y,ne;
};

struct Tarjan_Strong_Connected {
	int d[maxn],low[maxn],index;
	int *st,ee;
	Edge *e;
	int n;
	int s[maxn],ss;
	bool cs[maxn];
	int color[maxn],cc;//��Ⱦɫ��0 .. cc-1��cc��ʾ����
	void init(Edge* _e,int* _st,int _ee,int _n) {
		e = _e; st = _st; ee = _ee; n = _n;
		for (int i = 0; i<n ;i++) {
			d[i] = low[i] = cs[i] = 0;
		}
		index=0;ss=-1;
		cc=0;
	}
	void dfs(int u) {
		d[u] = low[u] = ++index;
		s[++ss] = u;
		cs[u] = 1;
		for (int i = st[u]; i!=-1; i = e[i].ne) {
			if (d[e[i].y] == 0) {
				dfs(e[i].y);
				low[u]=Min(low[u],low[e[i].y]);
			}
			else if (cs[e[i].y]) {
				low[u]=Min(low[u],d[e[i].y]);
			}
		}
		if (d[u]== low[u]) {
			while (cs[u]) {
				color[s[ss]]=cc;
				cs[s[ss--]]=0;
			}
			cc++;
		}
	}
	void work() {
		for (int i = 0; i<n; i++) if (d[i] == 0) dfs(i);
	}
};
struct Two_Sat {	//��0..2n-1,һ����i�Ķ�����Ϊi^1
	Edge e[maxm],l[maxm];
	int st[maxn],ee,lst[maxn],ll;
	int rudu[maxn];//e,st,ee����ԭͼ��l,lst,ll����������ķ�������ͼ
	int n;			//��������������*2
	Tarjan_Strong_Connected T;
	int color_t[maxn];//������ĵ��ѡȡ���-1��δ����1ѡ��2��ѡ
	int s[maxn],ss;		//���������б������Ϊ0��ջ
	int color[maxn];	//�����ķ���ÿ�����������Ƿ�ѡȡ��1ѡ��2��ѡ����֤�������ֵ��ͬ
	vector<int> cir[maxn];	//����ʱ������ÿ�����϶�Ӧ��Щ�㣨�ٶȽ�����������Сʱֱ��for��
	void addedge(int x,int y)	{ //�ֶ���ӱ�
		e[ee].y = y; e[ee].ne = st[x]; st[x] = ee++;
	}
	void T_addedge(int x,int y)	{	//�ڲ����� �������˼ӱ�
		if (x==y) return ;
		l[ll].y = y;
		l[ll].ne = lst[x];
		lst[x] = ll++;
		rudu[y]++;
	}
	void init(int _n)	{	//��ʼ�� ���������*2 ��Ŵ�0��ʼ
		ee = ll = 0;
		n=_n;
		for (int i=0;i<n;i++) {
			lst[i] = color_t[i] = -1;
			rudu[i] = 0;
			st[i] = -1;
			cir[i].clear();
		}
		ss = -1;
	}
	void dele(int k) {	//������ͼ��ɾ��һ����
		for (int i=lst[k];i!=-1;i=l[i].ne)
			if (--rudu[l[i].y]==0&&color_t[l[i].y]==-1) {
				s[++ss] = l[i].y;	//����е���ȱ��0����ջ
			}
	}
	void dfs_dele(int k) {	//������ͼ�н�k���µ�ȫ���Ƴ�
		color_t[k] = 2;		//�õ��ǲ�ѡ
		for (int i = lst[k];i != -1;i = l[i].ne) {
			if (color_t[l[i].y] != 2) {
				dfs_dele(l[i].y);	//����ֱ��ɾ������Ҫ������ջ�������Ϊ�ӵ�Ҳ��ɾ��
			}
		}
	}
	int work() {
		T.init(e,st, ee,n);
		T.work();		//Tarjan ����Ⱦɫ0 .. T.cc-1
		for (int i = 0; i<n; i++) {
			if (T.color[i]==T.color[i^1])
				return 0; //���޽�
			else
				cir[T.color[i]].push_back(i);		//����ÿ��������Щ��
		}
	//���¹���һ��⡣ע�����Ҫ����б������ĳ����k��ֻ���ڳ�ʼ��ʱ��ӱ�addedge(k^1,k)����
		for (int i = 0; i<n; i++) {
			for (int j = st[i]; j!=-1; j=e[j].ne) {
				T_addedge(T.color[e[j].y],T.color[i]);	//������������ͼ��ע������ӱ��Ǽӷ����
			}
		}

		for (int i=0;i<T.cc;i++) {
			if (rudu[i]==0) {
				s[++ss] = i;//ջ��ʼ��
			}
		}

		while (ss:=0) {
			int i;
			if (color_t[i=s[ss--]] != -1) continue; //��ջ
			dele(i);						//���������ͼ��ɾ��
			color_t[i]=1;				//�õ���ѡ
			for (int j = cir[i].size()-1; j>=0; j--) {
				dfs_dele(T.color[cir[i][j]^1]);		//�����Ķ����㼰�����µ�ȫ����ǲ�ѡɾ��
			}
		}
		for (int i=0; i<n; i++) {
			color[i] = color_t[T.color[i]];	//����ԭͼѡȡ���
		}
		return 1;
	}
};
Two_Sat TS;
int main() {
	int n,m;
#ifdef _DEBUG
	freopen("in.in","r",stdin);
#endif
	while (scanf("%d%d",&n,&m),n||m) {
		int i,j,k;
		char s[3],t[3];
		TS.init(n*2);
		while (m--) {
			scanf("%d%s%d%s",&i,s,&j,t);
			i=i*2+(s[0]=='w');j=j*2+(t[0]=='w');
			if (i==1||j==1) continue;
			TS.addedge(i,j^1);
			TS.addedge(j,i^1);
		}
		TS.addedge(1,0);
		if (TS.work()==0) puts("bad luck");
		else {
			for (i = 2; i<2*n; i++) if (TS.color[i]==2) {
				if (i&1) printf("%dw",i/2);
				else printf("%dh",i/2);
				if (i + 2 >= 2*n) puts("");else putchar(' ');
			}
		}
	}
	return 0;
}
