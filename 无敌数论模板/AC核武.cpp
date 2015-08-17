#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<ctime>
#include<map>
#include<string.h>
#include<cmath>
#include<cstring>
using namespace std;
typedef __int64 LL;

/*
 *Last Updated: 2009-12-31
*����(NumberTheory)��
 *����: AekdyCoin
 *����: 2009-12
 *����: chenh1989@gmail.com
 */


const int Plimit = 1000010;//�������޴�С...
const int MatSize = 2;//�������С...
template<class T> class Matrix//������...
    {
        private:
            int size;
            int Moudle;
        public:
            T mat[MatSize][MatSize];
            Matrix():size(MatSize){memset(mat,0,sizeof(mat));}
            Matrix(int _size):size(_size){memset(mat,0,sizeof(mat));}
            Matrix(int _size,int _Moudle):size(_size),Moudle(_Moudle){memset(mat,0,sizeof(mat));}
            inline void MatOut()
            {
                int i,j;
                for(i=0;i<size;++i,cout<<endl)
                    for(j=0;j<size;++j)
                        cout<<mat[i][j]<<' ';
            }
            inline Matrix operator*(const Matrix&M)
            {
                Matrix<T> ret(size,Moudle);
                int i,j,k;
                for(i=0;i<size;++i)
                    for(j=0;j<size;++j)
                        for(k=0;k<size;++k)
                        ret.mat[i][j]+=mat[i][k]*M.mat[k][j]%Moudle,ret.mat[i][j]%=Moudle;
                return ret;
            }
            template<class TT>inline Matrix operator^(TT k)
            {
                Matrix<T> ret=*this,x=*this;
                if(k==0)
                {
                    int i;
                    for(i=0;i<size;++i)ret.mat[i][i]=1%Moudle;
                    return ret;
                }
                if(k==1)return *this;
                --k;
                while(k)
                {
                    if(k&0x1)ret=ret*x;
                    x=x*x;
                    k>>=1;
                }
                return ret;
            }
    };
class NumberTheory 
{
private:
    int MaxPrime;//���������������...
    bool IsPlistCreated;//�Ƿ��Ѿ�����������...
    bool IsP[Plimit>>1];//������̬��...
    int Plist[Plimit>>1];
    int Plen;//�������С...
    LL buf_p[105];//Ϊ�˱�֤��ȫ,��ʹ��λ...
    int i_buf_p[105],buf_cnt[105],buf_len;//����ֽ����������...
    template<class T> inline T Phi_Process(T n,T p[],int len)
    {
        T ret = n;
        int i;
        for(i=0;i<len;++i)ret-=ret/p[i];
        return ret;
    }
    template<class T>inline T Pollard_rho(T c, T num)
    {
        int i(1), k(2);
        T x = rand() % num;
        T y = x, comDiv;
        do
        {
            ++i;
            if ((x=MulMod(x,x,num)-c)<0)x+=num;
            if (x==y)break;
            comDiv=GCD((y-x+num)%num,num);
            if (comDiv>1&&comDiv<num )return comDiv;
            if (i==k)
            {
                y=x;
                k<<=1;
            }
        }while(1);
        return num;
    }
    template<class T> void RanGetFac(T num)
    {
        if (IsPrime(num))
        {
            buf_p[buf_len++] = num; 
            return;
        }
        T factor;
        do
        {
            factor=Pollard_rho(rand()%(num-1) + 1, num);
        }while (factor>=num);
        RanGetFac(factor);
        RanGetFac(num/factor);
    }
    LL lrand(){return LL(rand())*rand();}
    template<class T>inline T ABS(T n){return n<0?n:-n;}
    template<class T>inline T DIV(T a,T b){if(a>0||(ABS(a)%ABS(b)==0))return a/b;return a/b+1;}
    template<class T>inline void SWAP(T &A,T &B){T C=A;A=B;B=C;}
    template<class T>inline void SwapVec(T a[],int len){int i;for(i=0;i<len/2;++i)SWAP(a[i],a[len-1-i]);}
    inline int Inval(int a,int b,int n){
        int x,y,e;
        EXT_GCD(a,n,x,y);
        e=(LL)x*b%n;
        return e<0?e+n:e;
    }
public:
    NumberTheory()
    {
        MaxPrime=0;
        IsPlistCreated=false;
        memset(IsP,false,sizeof(IsP));
        Plen=0;
    }
    inline int GetMaxPrime(){return MaxPrime;}//��ȡ�������...
    inline int GetPlen(){return Plen;}//��ȡ�������С...
 
    /*
     *����: ����[1,n]�ڵľ�̬������
     *ע��: ʹ����ѹ���Ż���ʱ��Ч�ʾ�����ͨɸ���ı�
     *����: n --����Ҫ��������������Ͻ�(ע�ⲻ�ܳ���Plimit)
     *����: ��
     */

    inline void CreatPlist(int n)
    {
        if(IsPlistCreated)return;
        int i,j,buf(1),M(1),L((n-1)>>1);
        while(buf<n)++M,buf=(M-1)<<1|1,buf*=buf;--M;
        Plist[Plen++]=2;
        for(i=1;i<M;++i)
            if(!IsP[i])
                for(buf=i<<1|1,j=i+buf;j<L;IsP[j]=true,j+=buf);
        for(i=1;i<L;++i)if(!IsP[i])Plist[Plen++]=i<<1|1;
        IsPlistCreated=true;
    }

    /*
     *����: ��ȡ���������±�Ϊx��Ԫ�ص�ֵ
     *ע��: ��ʹ��ʹ����ʹ��CreatPlist,���Ĭ��ִ��CreatPlist(Plimit)
     *����: x --����Ҫ���ص��������±�(x>=0)
     *����: �±�Ϊx��Ԫ�ص�ֵ,-1��ʾ������
     */

    inline int operator[](const int x){if(!IsPlistCreated)CreatPlist(Plimit);return x<0||x>=Plen?-1:Plist[x];}

    template<class T>inline T MOD(T a,T b){if(a>=b)a%=b;return a<0?a+b:a;}//����a%b,֧��a<=0

    /*
     *����: ���ּ���a^b mod c
     *ע��: �޷�����c*c�������c+c����������
     *����: a,b,c(a,b����С��,����c����С�ڵ���,���򷵻��޽�)
     *����: a^b mod c��ֵ,-1��ʾ������
     */

    template<class T,class Tb> inline T PowMod(Tb a,T b,T c)
    {
        if(c==1)return 0;
        if(c<=0)return -1;
        a=MOD(a,(Tb)c);
        Tb ret(1L%c);
        while(b){if(b&0x1)ret=ret*a%c;a=a*a%c;b>>=1;}
        return (T)ret;
    }

    /*
     *����: ���ּ���a*b mod c
     *ע��: ���Դ���c+c����������
     *����: a,b,c(a,b����С��,����c����С�ڵ���,���򷵻��޽�)
     *����: a*b mod c��ֵ,-1��ʾ������
     */

    template<class T>inline T MulMod(T a,T b,T c)
    {
        if(c==1)return 0;
        if(c<=0)return -1;
        T ret=0,tmp;
        tmp=a=MOD(a,c);
        b=MOD(b,c);
        while(b)
        {
            if(b&0x1)if((ret+=tmp)>=c)ret-=c;
            if((tmp<<=1)>=c)tmp-=c;
            b>>=1;
        }
        return ret;
    }

    /*
     *����: ���ּ���a^b mod c
     *ע��: ���Դ���c*c�������c+c����������(Ч�����PowMod��,ע��ȡ��)
     *����: a,b,c(a,b����С��,����c����С�ڵ���,���򷵻��޽�)
     *����: a^b mod c��ֵ,-1��ʾ������
     */

    template<class T> inline T HPowMod(T a,T b,T c)
    {
        if(c==1)return 0;
        if(c<=0)return -1;
        a=MOD(a,c);
        T ret(1L%c);
        while(b){if(b&0x1)ret=MulMod(ret,a,c);a=MulMod(a,a,c);b>>=1;}
        return ret;
    }

    /*
     *����: �ж�����
     *ע��: ������<Plimit��Ѹ�ٲ�ѯ������ʹ�����ղ���
     *����: n
     *����: n�Ƿ�Ϊ����
     */

    template<class T> inline bool IsPrime(T n)
    {
        if(n<2)return false;
        if(n==2)return true;
        if(!(n&0x1))return false;
        if(n==3||n==5||n==7||n==11||n==13||n==17||n==19||n==23)return true;
        if(n%3==0||n%5==0||n%7==0||n%11==0||n%13==0||n%17==0||n%19==0||n%23==0)return false;
        if(n<Plimit)
        {
            if(!IsPlistCreated)CreatPlist(Plimit);
            return !IsP[(n-1)>>1];
        }
        T x,m;
        int k,i,t=2;
        while(t--)
        {
            k=0;
            for(m=n-1;!(m&0x1);m>>=1,++k);
            x=HPowMod((T)lrand()%(n-2)+2,m,n);
            if(x!=1)
            {
                for(i=0;i<k&&x!=n-1;++i)x=MulMod(x,x,n);
                if(i==k)return false;
            }
        }
        return true;
    }

    /*
     *����: �ֽ�������
     *ע��: ��Plimit^2>=n,��ɨ������������ʹ��pollard_rho����ֽ�������
     *����: n,p[],cnt[],len,mode
     *(mode = 0-��ͨģʽ-ǿ��ʹ��ɨ��������(2+)-ǿ��ʹ��pollard_rho)
     *����: p[]-������ֵ,cnt[]-��������,len-������������
     */

    template<class T> inline void Split(T n,T p[],int cnt[],int &len,int mode)
    {
        len=0;
        int i,j;
        if(!IsPlistCreated)CreatPlist(Plimit);
        if(mode==1||(!mode&&n/Plimit<=Plimit))
        {
            for(i=0;i<Plen&&n>=Plist[i];++i)
                if(n%Plist[i]==0)
                {
                    p[len]=Plist[i];
                    cnt[len]=0;
                    while(n%p[len]==0)++cnt[len],n/=p[len];
                    ++len;
                }
            if(n!=1)p[len]=n,cnt[len]=1,++len;
            return;
        }
        buf_len=0;
        RanGetFac(n);
        len=0;
        sort(buf_p,buf_p+buf_len);
        for(i=0;i<buf_len;++i)
        {
            p[len++]=(T)buf_p[i];
            for(j=i+1;j<buf_len&&buf_p[j]==buf_p[i];++j);
            i=j-1;
        }
        for(i=0;i<len;++i)cnt[i]=0;
        for(i=0;i<len;++i)
            while(n%p[i]==0)
                n/=p[i],++cnt[i];
        return;
    }

    /*
     *����: ��ȡһ������������
     *ע��: n<=Plimit*Plimit
     *����: n
     *����: һ������������
     */

    template<class T> inline int FacCnt(T n)
    {
        int ret=1,i;
        Split(n,i_buf_p,buf_cnt,buf_len,0);
        for(i=0;i<buf_len;++i)ret*=(buf_cnt[i]+1);
        return ret;
    }

    /*
     *����: ��ȡһ���������Ӻ�
     *ע��: n<=Plimit*Plimit
     *����: n
     *����: һ���������Ӻ�
     */

    template<class T> inline int FacSum(T n)
    {
        int ret=1,i,j,tmp;
        Split(n,i_buf_p,buf_cnt,buf_len,0);
        for(i=0;i<buf_len;++i)
        {
            for(tmp=0,j=0;j<=buf_cnt[i];++j,tmp=tmp*i_buf_p[i]+1);
            ret*=tmp;
        }
        return ret;
    }
    /*
     *����: �õ�[1..Limit]����������������
     *ע��: Limit����Ϊ���򼶱�
     *����: cnt[]-��Ž��Limit-����ֵ
     *����: cnt[]
     */

    inline void SegFacCnt(int cnt[],int Limit)
    {
        memset(cnt,0,sizeof(cnt));
        int i,j;
        for(i=1;i<=Limit;++i)
            for(j=i;j<=Limit;j+=i)
                ++cnt[j];
    }

    /*
     *����: �õ�[1..Limit]�������������Ӻ�
     *ע��: Limit����Ϊ���򼶱�
     *����: cnt[]-��Ž��Limit-����ֵ
     *����: cnt[]
     */

    inline void SegFacSum(int cnt[],int Limit)
    {
        memset(cnt,0,sizeof(cnt));
        int i,j;
        for(i=1;i<=Limit;++i)
            for(j=i;j<=Limit;j+=i)
                cnt[j]+=i;
    }

    /*
     *����: �ж�һ�����Ƿ���SquareFree��
     *ע��: ���ܴ���Long Long
     *����: n
     *����: n�Ƿ���SquareFree��
     */

    inline bool IsSquareFree(int n)
    {
        Split(n,i_buf_p,buf_cnt,buf_len,1);
        int i;
        for(i=0;i<buf_len;++i)if(buf_cnt[i]!=1)return false;
        return true;
    }

    /*
     *����: ���ظ��������Լ��
     *ע��: A,B���ͱ���һ��
     *����: A,B
     *����: A,B�����Լ��
     */    

    template <class T>inline T GCD(T A,T B){T C;while(B!=0)C=B,B=A%B,A=C;return A;}

    /*
     *����: ���ظ�������С������
     *ע��: A,B���ͱ���һ��
     *����: A,B
     *����: A,B����С������
     */    

    template <class T>inline T LCM(T A,T B){return A*(B/GCD(A,B));}

    /*
     *����: ��չŷ�����
     *����: a,b,x,y
     *����: x,y����ax+by=gcd(a,b)��һ���
     */    

    template <class T>T EXT_GCD(T a,T b,T& x,T& y)
    {
        T t,ret;
        if (!b){
            x=1,y=0;
            return a;
        }
        ret=EXT_GCD(b,a%b,x,y);
        t=x,x=y,y=t-a/b*y;
        return ret;
    }

    /*
     *����: ����һ����a����n�ĳ˷���Ԫ
     *ע��: GCD(a,n)=1���н�
     *����: a,n (a����Ϊ��)
     *����: a����n�ĳ˷���Ԫ,�������򷵻�-1
     */

    template <class T>inline T InvMod(T a,T n){
        if(n<=0)return -1;
        T d,x,y;
        d=EXT_GCD(a,n,x,y);
        if(d!=1)return -1;
        return MOD(x,n);
    }

    /*
     *����: ����һ������ŷ������
     *ע��: ���ܴ���Long Long
     *����: n(n<=Plimit*Plimit)
     *����: n��ŷ������
     */

    int Phi(int n)
    {
        int ret(n),i;
        if(!IsPlistCreated)CreatPlist(Plimit);
        for(i=0;i<Plen&&n>=Plist[i];++i)
            if(n%Plist[i]==0)
            {
                ret-=ret/Plist[i];
                while(n%Plist[i]==0)n/=Plist[i];
            }
        if(n!=1)ret-=ret/n;
        return ret;
    }

    /*
     *����: ����һ������ŷ������
     *ע��: ���Դ���<2^63,�����ȷֽ�
     *����: n(n<2^63)
     *����: n��ŷ������
    */

    template<class T> inline T HPhi(T n)
    {
        T buf_p[105];
        int buf_cnt[105],buf_len;
        Split(n,buf_p,buf_cnt,buf_len,0);
        return Phi_Process(n,buf_p,buf_len);
    }

    /*
     *����: ��[1..Limit]������ŷ�������������
     *����: phi[]-��Ž��������Limit-����(��༸���򼶱�)
     *����: phi[]-�����ڵ�ŷ������
    */

    inline void SegPhi(int phi[],int Limit)
    {
        memset(phi,0,sizeof(phi));
        int i,j;
        for(phi[1]=1,i=2;i<=Limit;++i)
            if(!phi[i])
                for(j=i;j<=Limit;j+=i)
                {
                    if(!phi[j])phi[j]=j;
                    phi[j]-=phi[j]/i;
                }
    }

    /*
     *����: ��nת��Ϊb����
     *����: n,b (|b|>=2,b����Ϊ��)
     *����: Ans[] -��,Ans[0]�������λ,�Դ�����. len -��
    */

    template<class T> inline void ToBase(T n,int b,T Ans[],int &len)
    {
        if(n==0){Ans[0]=0;len=1;return;}
        len=0;
        if(b>0)
            while(n!=0)
            {
                Ans[len++]=n%b;
                n/=b;
            }
        else
            while(n!=0)
            {
                Ans[len]=n-DIV(n,b)*b;
                n=DIV(n,b);
                ++len;
            }
        SwapVec(Ans,len);
        return;
    }

    /*
     *����: ��nת��Ϊb����(��������СԪ��Ϊa,���Ϊa+b-1)
     *����: n,a,b
     *����: Ans[] -��,Ans[0]�������λ,�Դ�����. len -��
    */

    template<class T>inline void HToBase(T n,int a,int b,T Ans[],int &len)
    {
        int cnt,i;
        if(n==0){Ans[0]=0;len=1;return;}
        LL sum;
        cnt=len=sum=0;
        if(a)
        {
            while(sum<n)
            {
                sum=sum*b+a;
                ++cnt;
            }
        }
        if(sum>n)
            sum/=b,--cnt; 
        n-=sum;
        while(n)
        {
            Ans[len++]=n%b;
            n/=b;
        }
        for(i=0;i<cnt&&len-i-1>=0;++i)Ans[len-i-1]+=a;
        cnt=cnt>len?cnt:len;
        SwapVec(Ans,cnt);
        return;
    }

    /*
     *����: ��Ans[]������ת��Ϊ������
     *����: b -������,Ans[] -����,len-����
     *����: Ans[]�����ݵĽ�����
    */

    template<class T> inline T BaseVal(int b,T Ans[],int len)
    {
        T ret=0;
        int i;
        for(i=0;i<len;++i)ret=ret*b+Ans[i];
        return ret;
    }

    /*
    *����: ���x^2 - n* y^2 = 1����С������
    *ע��: ���nΪ��ȫƽ����,�򷵻�һ��ƽ����(x=0,y=1)
    *���򷵻�һ����С����x,y(x,y>0)
    *ע�����n�Ƚϴ�(����)��ôx,y������Ҫ�߾���
    *����: ��С������x,y
    */

    template<class T>inline int Pell(T n,T& x,T& y)
    {
        T aa=(T)sqrt((double)n),a=aa;
        x=1;
        y=0;
        if(aa*aa==n)return 0;
        T p1=1,p2=0,q1=0,q2=1,g=0,h=1;
        while(true)
        {
            g=-g+a*h;
            h=(n-g*g)/h;
            x=a*p1+p2;
            y=a*q1+q2;
            if(x*x-n*y*y==1)
                return 1;
            p2=p1;
            q2=q1;
            p1=x;
            q1=y;
            a=(g+aa)/h;
        }
        return 1;
    }    

    /*
    *����: ��Fibonacci���е�N��Mod K��ֵ
    *ע��: F[0]=F[1]=1;F[n]=F[n-1]+F[n-2] (n>=2)
    *ע�����n�Ƚ�С,���԰�Kȡ��һ��:(��������һ���-_-)
    */

    inline int Fibonacci(int N,int K)
    {
        if(N<=1)return 1%K;
        --N;
        Matrix<LL> X(2,K);
        X.mat[0][0]=X.mat[0][1]=X.mat[1][0]=1;
        X=X^N;
        return (X.mat[0][0]+X.mat[0][1])%K;
    }

    /*
    *����: ��Fibonacci����ǰN��(F[0]+F[1]+...+F[N])��Mod K��ֵ
    *ע��: F[0]=F[1]=1;F[n]=F[n-1]+F[n-2] (n>=2)
    *ע�����n�Ƚ�С,���԰�Kȡ��һ��:(��������һ���-_-)
    */

    inline int Fibonacci_Sum(int N,int K)
    {
        N+=2;
        return MOD(Fibonacci(N,K)-1,K);
    }

   /*
    *����: ���A^x = B (mod C)����Сx(x>=0)
    *ע��: ���Ӷȴ�ԼΪO(0.5*C^0.5*(logC)^2)��C������signed int��(������������,��΢�޸ľͿ���)
    *ʹ�� Hash���Ż����ԴﵽԼO(0.5C^0.5*logC)
    *����: -1��ʾ�޽�,���򷵻���С��x...
    */

    int BabyStep(int A,int B,int C)
    {
        map<int,int> Hash;
        LL buf=1%C,D=buf,K;
        int i,d=0,tmp;
        for(i=0;i<=100;buf=buf*A%C,++i)if(buf==B)return i;
        while((tmp=GCD(A,C))!=1)
        {
            if(B%tmp)return -1;
            ++d;
            C/=tmp;
            B/=tmp;
            D=D*A/tmp%C;
        }
        Hash.clear();
        int M=(int)sqrt(C+0.0);
        for(buf=1%C,i=0;i<=M;buf=buf*A%C,++i)if(Hash.find((int)buf)==Hash.end())Hash[(int)buf]=i;
        for(i=0,K=PowMod((LL)A,M,C);i<=M;D=D*K%C,++i)
        {
            tmp=Inval((int)D,B,C);
            if(tmp>0&&Hash.find(tmp)!=Hash.end())return i*M+Hash[tmp]+d;
        }
        return -1;
    }

};
NumberTheory T;
int main()
{
    T[-1];
    int k;
    LL x,y,n;
    while(scanf("%I64d%d",&n,&k)!=EOF)
    {
        if(n == 4 || n == 9 || n == 16 || n == 25)
        {
            puts("No answers can meet such conditions");
            continue;
        }
        T.Pell(n,x,y);
        x%=8191;
        y%=8191;
        Matrix<LL> res(2,8191);
        res.mat[0][0] = x;
        res.mat[0][1] = n*y;
        res.mat[1][0] = y;
        res.mat[1][1] = x;
        res=res^(k-1);
        LL ans = res.mat[0][0] * x + res.mat[0][1]*y;
        ans %= 8191;
        cout<<ans<<endl;
    }
    return 0;
}
