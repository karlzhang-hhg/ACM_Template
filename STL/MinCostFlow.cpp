/***********************************************************************
2��ͼ���ƥ�䣬�õ���С������
SPFA������·��������׷�ٸ���������Edmonds_karp�㷨�Ļ������޸ġ�
��Ҫע����ı�ţ�man�Ǵ�1~n��house��n+1~2*n������Դ��ͻ�������
��Ȩֵ�ֱ�Ϊ1��0��
��Ҫע���ϸ�ںܶ�
***********************************************************************/
#include<iostream>
#include<queue>
using namespace std;
queue<int>q;
bool flag[220];//����Ƿ����
char m[220][220];//��ͼ
int r,c,s,t;
struct MAP
{
    int c,f,w;
}map[220][220];
int maxflow,mincost,nm,nh,man[101][2],house[101][2],v[220],pre[220],cost[220];
//cost[]----����,pre[]----���ڵ�
void Init()//����������
{
    int i,j;
    s=2*nh+2,t=2*nh+1;
    for(i=1;i<=nm;i++)
    {
        for(j=1;j<=nh;j++)
        {
            map[i][nm+j].c=1;
            map[i][nm+j].w=abs(man[i][0]-house[j][0])+abs(man[i][1]-house[j][1]);
        }
    }
    for(i=1;i<=nm;i++)
    {
        map[s][i].c=1;//nh+2Ϊ����Դ��,nh+1Ϊ���ӻ��
        map[s][i].w=0;
    }
    for(i=nh+1;i<=2*nh;i++)
    {
        map[i][t].c=1;
        map[i][t].w=0;
    }
    return ;
}
bool spfa()
{
    int i,j;
    memset(v,0,sizeof(v));
    memset(flag,0,sizeof(flag));
    memset(pre,0,sizeof(pre));
    for(i=1;i<=2*nh+2;i++)
    {
        cost[i]=INT_MAX;
    }
    while(!q.empty())
        q.pop();
    v[s]=INT_MAX;
    pre[s]=s;
    cost[s]=0;
    flag[s]=1;
    q.push(s);
    while(!q.empty())
    {
        i=q.front();
        for(j=1;j<=2*nh+2;j++)
        {
            if(map[i][j].f<map[i][j].c&&cost[i]+map[i][j].w<cost[j])
            {
                cost[j]=cost[i]+map[i][j].w;
                v[j]=min(v[i],map[i][j].c-map[i][j].f);
                pre[j]=i;
                if(!flag[j])
                {
                    flag[j]=1;
                    q.push(j);
                }
            }
            else if(map[j][i].f&&cost[i]-map[j][i].w<cost[j])
            {
                cost[j]=cost[i]-map[j][i].w;
                v[j]=min(v[i],map[j][i].f);
                pre[j]=-1*i;
                if(!flag[j])
                {
                    flag[j]=1;
                    q.push(j);
                }
            }
        }
        q.pop();
        flag[i]=0;
    }
    if(v[t]>0)
        return 1;
    else 
        return 0;
}
int mcmf()
{
    int i,j;
    maxflow=0,mincost=0;
    while(spfa())
    {
        j=t;
        maxflow+=v[t];
        while(j!=s)
        {
            i=abs(pre[j]);
            if(pre[j]>0)
            {
                map[i][j].f+=v[t];
                mincost+=v[t]*map[i][j].w;
            }
            else
            {
                map[j][i].f-=v[t];
                mincost-=v[t]*map[j][i].w;
            }
            j=i;
        }
    }
    return mincost;
}
int main()
{
    int i,j,k;
    while(scanf("%d%d",&r,&c)!=EOF&&r&&c)
    {
        memset(map,0,sizeof(map));
        memset(man,0,sizeof(man));
        memset(house,0,sizeof(house));
        nm=nh=0;
        getchar();
        for(i=1;i<=r;i++)
        {
            for(j=1;j<=c;j++)
            {
                scanf("%c",&m[i][j]);
                if(m[i][j]=='m')
                {
                    man[++nm][0]=i;
                    man[nm][1]=j;
                }
                else if(m[i][j]=='H')
                {
                    house[++nh][0]=i;
                    house[nh][1]=j;
                }
            }
            getchar();
        }
        Init();
        printf("%d\n",mcmf());
    }
    return 0;
}
