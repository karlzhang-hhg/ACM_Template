/*
�����㷨RMQģ��
�������ּ�¼�� f���� �������0��ʼ ��СΪn
���ܺ��� maxrmq(x,y) minrmq(x,y)
�÷�Ϊ�������±�x,y,��������һ����ֵ�����Сֵ�����±� 
*/
#include <iostream>
#include <cstdio>
#include <math.h>
using namespace std;
int f[50010],rmax[50010][17],rmin[50010][17];
int n;
int maxrmq(int x, int y)
{
	int t,range;
	t=y-x+1;
	if (t==1) return rmax[x][0];
	range=floor(log(t+0.0)/log(2.0));
	t=y-(1<<range)+1;
	if(f[rmax[x][range]]>f[rmax[t][range]]) return rmax[x][range];//�޸ĺ����ֵ���¸ı� 
	else return rmax[t][range];
}	
int minrmq(int x, int y)
{
	int t,range;
	t=y-x+1;
	if (t==0) return rmin[x][0];
	range=floor(log(t+0.0)/log(2.0));
	t=y-(1<<range)+1;
	if(f[rmin[x][range]]<f[rmin[t][range]]) return rmin[x][range];//�޸ĺ����ֵ���¸ı� 
	else return rmin[t][range];
}

int main()
{
	int i , j , m ,range,k,t,max,q,x,y;
   
////////////////////////////////////////////////    
	   for(i=0;i<n;i++) {rmin[i][0]=i;	rmax[i][0]=i;}
    range = ceil(log(n+0.0)/log(2.0));
	
    for (k=1;k<=range;k++)
    {
       	t=n - (1 << k ) +1 ;			
       	for ( i = 0 ; i < t ; i ++ )
        { 
      		if ( f[rmax[i][k-1]] > f[rmax[i+(1<<(k-1))][k-1]]) rmax[i][k]= rmax[i][k-1];
      		else rmax[i][k]=rmax[i+(1<<(k-1))][k-1];
      
      		if ( f[rmin[i][k-1]] < f[rmin[i+(1<<(k-1))][k-1]]) rmin[i][k]= rmin[i][k-1];
      		else rmin[i][k]=rmin[i+(1<<(k-1))][k-1];
      	}
    }
///////////////////////////////////////////////////
	return 0;
}
