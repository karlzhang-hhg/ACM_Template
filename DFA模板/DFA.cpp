

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <memory.h>
using namespace std;

const int maxn=1502;
typedef long long lld;
///////////////////////////////////
#include <cmath>
const int maxBt=30,maxUt=4,maxMo=pow(10.0,maxUt);
//maxBt�Ǹ߾������ĳ���,maxUt�ǽ���,maxMo��10^maxUt
struct BigInt {
	int s[maxBt];
	int ss;
	BigInt() {
		ss=0;
		memset(s,0,sizeof(s));
	}
	BigInt(int k) { //������k��ʼ��
		ss=0;
		memset(s,0,sizeof(s));
		while (k) s[ss++]=k%maxMo,k/=maxMo;
	}
	int& operator [](int k){return s[k];}
	void printBt() { //���
		if (ss==0) printf("0\n");
		else {
			printf("%d",s[ss-1]);
			for (int i=ss-2;i>=0;i--) printf("%04d",s[i]);
			//ע����������Ľ��Ƹ�ʽ��0�������Ƶ���ʱһ�����
			puts("");
		}
	}
};
BigInt operator + (BigInt a,BigInt b) {
	int i,t=0,code;
	for (i=0;i<a.ss||i<b.ss||t!=0;i++) {
		code=a[i]+b[i]+t;
		a[i]=code%maxMo;
		t=code/maxMo;
	}
	a.ss=i;return a;
}
BigInt operator *(BigInt a,BigInt b) {
	int i,j,t=0,code;
	BigInt c;
	for (i=0;i<a.ss;i++) {
		for (j=t=0;j<b.ss||t>0;j++) {
			code=a[i]*b[j]+t+c[i+j];
			c[i+j]=code%10000;
			t=code/10000;
		}
		if (c.ss<i+j) c.ss=i+j;
	}
	return c;
}



////////////////////////////////////dfaģ��
const int maxch=52,maxnode=maxn;//maxch=����ַ�����С,maxnode=���ڵ���(����)
struct DFA {
	DFA* pt[maxch];//ָ��
	DFA* pre;//ǰ��ָ��
	int term,id;//�Ƿ����ս�(���term��0����ʾ���ս�,�������ս��ĸ���,id=�����ı��
	DFA() {memset(pt,NULL,sizeof(pt)); pre=NULL; term = 0; id = 0;}
};
void addDFA(int* s,int ss,DFA *root,int& nDFA) { //��trie�� nDFA�����нڵ���,*s��Ҫ����Ĵ�,ss�Ǵ���
	for (int i = 0; i<ss; i++) {
		if (root->pt[s[i]] == NULL) {
			root->pt[s[i]] = new DFA;
			root->pt[s[i]]->id = nDFA++;
		}
		root=root->pt[s[i]];
	}
	root->term++;//β�͵��ս����++
}
DFA* bfs[maxnode];//bfs����DFA
int head,tail;//bfs������ָ��
void makeDFA(DFA *root,int mch) { //DFA����ǰ��ָ��,Ȼ�����������ڵ����ת
	DFA* proot=new DFA;//����һ����ʱ�ĳ�����,������ָ��ָ��root
	for (int i = 0; i<mch; i++) proot->pt[i] = root;
	root->pre=proot;
	head=0,tail=1;
	bfs[0]=root;//��ʼbfs
	while (head<tail) {
		for (int i = 0; i<mch; i++) {
			if (bfs[head]->pt[i]!=NULL) { //��չbfs
				DFA* p = bfs[head]->pt[i];
				bfs[tail++] = p;//�����½ڵ�
				for (p->pre=bfs[head]->pre;(p->pre)->pt[i]==NULL;p->pre=(p->pre)->pre);//�����ýڵ��ǰ��ָ��
				p->pre=(p->pre)->pt[i];
			}
			else {
				bfs[head]->pt[i]=bfs[head]->pre->pt[i];//���� ���ָ������ָ��,�����ת
			}
		}
		bfs[head]->term+=bfs[head]->pre->term;//ע��!�ս��Ǵ���
		head++;
	}
}
///////////////////////////////////
int s[100];
char ch[100];
char dic[100];

int n,m,p;
BigInt f[maxn],g[maxn];
void work() {
	int i,j,k;

	DFA *root=new DFA;
	int nDFA=1;
	gets(dic);

	root->id=0;

	while (p--) {
		gets(ch);
		k=strlen(ch);
		for (i=0;i<k;i++) {
			char* p=strchr(dic,ch[i]);
			if (p==NULL) break;
			s[i]=p-dic;
		}

		if (i>=k&&k>0) addDFA(s,k,root,nDFA);
	}
	makeDFA(root,m);
	nDFA=tail;

	for (i=0;i<nDFA;i++) f[i]=0;
	f[0]=1;
	for (k=0;k<n;k++) {
/*		BigInt ret;
		for (j=0;j<nDFA;j++) ret=ret+f[j];
		if (ret.ss==0) printf("0\n");
		else
		{
			for (i=ret.ss-1;i>=0;i--) printf("%d",ret[i]);
			puts("");
		}
*/
		for (j=0;j<nDFA;j++) g[j]=0;

		for (i=0;i<nDFA;i++) {
			if (bfs[i]->term==0&&bfs[i]->pre->term==0)
			for (j=0;j<m;j++) if (bfs[i]->pt[j]->term==0&&bfs[i]->pt[j]->pre->term==0)
				 g[bfs[i]->pt[j]->id]=g[bfs[i]->pt[j]->id]+f[bfs[i]->id];
		}

		for (j=0;j<nDFA;j++) f[j]=g[j];
	}

	BigInt tot;
	for (i=0;i<nDFA;i++) tot=tot+f[i];
	tot.printBt();

}
int main() {
	#ifdef _DEBUG
	freopen("in.in", "r", stdin);
	#endif

	while (	scanf("%d%d%d\n",&m,&n,&p)!=EOF)
		work();
	return 0;
}
