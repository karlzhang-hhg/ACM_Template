#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long lld;
class Splaytree {
public:
	struct Node {
		lld key;
		int data;
		Node *left,*right,*father;
		Node(Node* fa){key = 0; father = fa; left = right = NULL;}
		Node(){key = 0; father = left = right = NULL;}
	};
	Node* root;
	Splaytree(){root = NULL;}	//ע������&root����ȫ����ʵ��ָ�� ��������ʱָ��
	void splay(Node* &root,Node* x);//��x�ᵽ��
	Node* splayfind(lld keyf);//���ҵ�һ��key��С��keyf�Ľڵ�
	void splayzig(Node* &root,Node* x);//����
	void splayzag(Node* &root,Node* x);//����
	void splaydelete(Node* &root,Node* x);//��xת��root �ɵ�
	Node* splayMax(Node* &root);//������ת����
	Node* splayinsert(lld key);//����key �����Ǹ��� �Ѿ����ھ�ֱ�ӷ���
};
	void Splaytree::splayzig(Node* &root,Node* x) { //��x������ ��x����ȥ x�������������
		if (x == NULL) return ;
		Node* fa = x->father;//����x�ĸ���
		Node* y = x->left;	//x�������
		if (y == NULL) return ;//���y�ǿ� û����
		x->left = y->right;	//y���Ҹ�x����
		if (y->right != NULL) y->right->father = x;//�޸�y�ҵĸ���
		y->right = x;	//x�ӵ�y��
		x->father = y;//�޸�x����
		if (x == root) root = y; else//�жϸ��Ƿ�ı�
		if (fa->left == x) fa->left = y; else fa->right = y;//�޸ĸ���ָ��
		y->father = fa;//�޸�y����
	}
	void Splaytree::splayzag(Node* &root,Node* x) {
		if (x == NULL) return;
		Node* fa = x->father;
		Node* y = x->right;
		if (y == NULL) return ;
		x->right = y->left;
		if (y->left != NULL) y->left->father = x;
		y->left = x;
		x->father = y;
		if (x == root) root = y; else
		if (fa->left == x) fa->left = y; else fa->right = y;
		y->father = fa;
	}
	void Splaytree::splay(Node* &root,Node* x) { //��x������
		if (x == NULL) return ;
		while (1) {
			if (x == root) return ;//���x���Ǹ� ͣ��
			if (x->father == root) {	//���x�ĸ����Ǹ�
				if (root->left == x) splayzig(root,root);
				else splayzag(root,root);
				return ;
			}
			Node *fa = x->father;//����
			Node* fa2 = fa->father;//���׵ĸ���
			if (fa2->left == fa&&fa->left == x) { //һ���� ��תfa2
				splayzig(root,fa2);
				splayzig(root,fa);
			}
			else if (fa2->right == fa&&fa->right == x) {
				splayzag(root,fa2);
				splayzag(root,fa);
			}
			else if (fa2->left == fa&&fa->right == x) { //�� ��תfa
				splayzag(root,fa);
				splayzig(root,fa2);
			}
			else {
				splayzig(root,fa);
				splayzag(root,fa2);
			}
		}
	}
	Splaytree::Node* Splaytree::splayfind(lld keyf) { //���Ҳ�С��keyf�ĵ�һ��
		Node *x = root,*last = NULL;//�������x�Ҳ�С��x��
		while (x != NULL) {
			if (keyf == x->key) { last = x; break;}//�պ��ҵ�
			if (keyf<x->key) {	//����������� ��ôx���ܳ�Ϊ��� ��last����
				last = x;
				x = x->left;
			}
			else {
				x = x->right;	//�������� xû�� ���ñ���
			}
		}
		x = last;
		splay(root,x);		//��xת����
		return x;
	}
	Splaytree::Node* Splaytree::splayinsert(lld key) {//����key�Ľڵ�
		if (root == NULL)	{		//����ֱ�ӽ�
			root = new Node;
			root->key = key;
			return root;
		}
		Node* cut = splayfind(key);	//���ҵ���key���
		if (cut == NULL) { //���ȫС��key
			Node* p = new Node;
			p->key = key;
			p->left = root;			//root��p��
			root->father = p;			//�޸ĸ�ָ��
			root = p;
			return root;
		}else	{ //cut�ж��� ��ʱ��cut�൱��root
			if (cut->key == key) return cut;	//�Ѿ����ڵĻ� �����뷵��ָ��
			else	{  //�� cut����=p�� cut=p��
				Node* p = new Node;
				p->key = key;
				p->left = cut->left;		//p��=cut��
				if (cut->left != NULL) cut->left->father = p;	//�޸�cut��ָ��
				p->right = cut;			//p��=cut
				cut->father = p;			//�޸�cut��ָ��
				cut->left = NULL;			//�Ͽ�cut��(����Ѿ���p����)
				root = p;					//p��Ϊ�¸�
				return p;
			}
		}
	}
	Splaytree::Node* Splaytree::splayMax(Node* &root) { //��root��������������root
		Node* p = root;
		if (p == NULL) return NULL;
		while (p->right != NULL) {
			p = p->right;//���Ҷ����ҵ���
		}
		splay(root,p);//��֮
		return p;
	}
	void Splaytree::splaydelete(Node* &root,Node* x) { //ɾ��x
		if (x == NULL) return ;
		splay(root,x);			//��������
		if (x->left == NULL) { //���x������Ϊ�� ֱ�Ӹ�
			root = x->right;		//x���Ҷ��ӱ�ɸ�
			if (root != NULL)	{	//�Ͽ�
				root->father = x->father;//����rootfather
			}
		}
		else {		//������� ��ô������ӵ������ᵽ�� ��ʱ��������Ȼû�������� ��root���ҽ���ȥ
			Node* p = splayMax(x->left);	//������ӵ����
			p->right = x->right;			//��������
			if (x->right != NULL) x->right->father = p;		//�޸ĸ�ָ��
			p->father = x->father;				//p��Ϊ�¸�
			root = p;
		}
		delete x;
	}
////////////////////////////////////////////////////////////////////////////////////////
inline int Min(int a,int b){return a<b?a:b;}
inline int Abs(int a){return a>0?a:-a;}
const int maxn=60000,maxl=99999999;
struct Qujian {
	int l,r;
} a[maxn];
Splaytree tree;
int n,start;
void iin() {
	int i;
	scanf("%d%d",&n,&start);
	for (i=n-1;i>=0;i--) scanf("%d%d",&a[i].l,&a[i].r);
}
void dp() {
	int i,j,k;
//	a[n].l=-maxl;a[n].r=0;
//	a[n+1].l=0;a[n+1].r=maxl;
	tree.splayinsert(start);
	tree.root->data=0;
//	Splaytree::Node *q=tree.root;
	for (i=0;i<n;i++) {
		lld lmin=maxl,rmin=maxl;
		Splaytree::Node *p;
		while (1) {
			p=tree.splayfind(a[i].l);
			if (p == NULL||p->key>a[i].r) break;
			lmin=Min(lmin,Abs(p->key-a[i].l)+p->data);
			rmin=Min(rmin,Abs(a[i].r-p->key)+p->data);
			tree.splaydelete(tree.root,p);
		}
		p=tree.splayinsert(a[i].l);
		p->data=lmin;
		p=tree.splayinsert(a[i].r);
		p->data=rmin;
	}
	//tree.splayfind(0);
	//printf("%d\n",tree.root->data);
	lld res=maxl;
	int tot=0;
	while (tree.root != NULL) {
		tot++;
		res=Min(res,tree.root->data+Abs(tree.root->key));
		tree.splaydelete(tree.root,tree.root);
	}
	//cout<<tot<<endl;
	printf("%d\n",res);

}
int main() {
	string s("obstacle.7.in "),s2=s;s2[11]='o';s2[12]='u';s2[13]='t';
//	string s="in.in";
	freopen(s.c_str(),"r",stdin);
	iin();
	dp();
	system(s2.c_str());
	return 0;
}
