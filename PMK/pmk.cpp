
#include <iostream>
using namespace std;
const int maxn= 410000,maxm=1100;
void count(char* p,int* f,int m) {
	//ģ�崮p,ǰ׺�ѭ��ƥ�������f,ģ�崮����m
	for (f[1]=1;f[1]<m&&p[f[1]]==p[0];f[1]++);
	for (int i = 2, k = 1; i<=m; i++)
		if (f[i-k]+k<f[k]) f[i] = f[i-k]+k;
		else
			for (f[i]=f[k],k=i; f[i]<m && p[f[i]]==p[f[i]%i]; f[i]++);
}
void pipei(char* s,int n,char* p,int m,int* f,int* g)
{//ƥ�䴮s,����n,ƥ�䴮p,����m,ѭ���ǰ׺f,���s-pǰ׺ƥ�䵽g
	for (g[0]=0;g[0]<m && g[0]<n && p[g[0]]==s[g[0]];g[0]++);
	for (int i = 1, k = 0; i<n; i++) {
		g[i] = f[i-k]-(i-k);
		if (g[i]+i>=g[k]+k || i>=g[k]+k) {
			g[i] = g[k]-i+k;
			if (g[i]<0) g[i] = 0;
			while (g[i]+i<n && g[i]<n && s[g[i]+i]==p[g[i]]) g[i]++;
			k=i;
		}
	}
}
