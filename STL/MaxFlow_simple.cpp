/*
�����ģ��
SAP�㷨 ��n���� m���� �ڽӾ���洢 �����洢��flow����
������Ϊc ��ε���ʱ �轫c���������ؽ� vh�����h����Ҳ������ vh[0]=n,����Ϊ0
ͼ��Ĭ�� 0�� Ϊ Դ�� n-1Ϊ ��� �����޸� 
*/
#include <iostream>
#include <cmath>
#define MAXN 300
#define MAXM 1100
using namespace std;

int n,m,c[MAXN][MAXN],h[MAXN],vh[MAXN],augc,flow;

void aug(const int m)
{
	int i,augco,minh;
	minh = n - 1;
	augco = augc;
	if ( m == n -1)
	{
		flow += augc;
		found = 1;
		return;
	}
	for( i=0;i<n;i++)if (c[m][i]>0){
		if (h[i]+1 == h[m]){
			if ( c[m][i] < augc ) augc = c[m][i];
			aug(i);
			if (h[0] >= n) return;
			if (found) break;
			augc = augco;
		}
		if ( minh > h[i] ) minh = h[i];
	}
	if (!found){
		vh[h[m]]--;
		if (vh[h[m]] == 0) h[0] = n;
		h[m] = minh + 1;
		vh[h[m]] ++ ;
	}
	else
	{
		c[m][i] -=augc;
		c[i][m] += augc;
	}
}


int main()
{
	int i,j,k;
	{}//input and build map;
	
	memset(h,0,sizeof(h));
	memset(vh,0,sizeof(vh));vh[0] = n;	 
	flow = 0;
	while ( h[0] < n )
	{
		augc = 0x7FFFFFFF;
		found = 0;
		aug(0);
	}
	
	
	return 0;
}
	
