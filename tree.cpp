#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <stack>
using namespace std;
/*int ino[]={4,2,7,5,1,3,6};
int pre[]={1,2,4,5,7,3,6};*/
int pre[]={1,2,4,5,8,3,6,9,7};
int ino[]={4,2,5,8,1,9,6,3,7};
/*int ino[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
int pre[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};*/
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x):val(x),left(NULL),right(NULL){}
};
struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x):val(x),next(NULL){};
};
struct TreeNode * preAndino(int pre[],int preL,int preR,int ino[],int inoL,int inoR)
{
	if(preL>preR) return NULL;
	int e=pre[preL],idx=inoL,pdx=preL;
	while(idx<=inoR&&ino[idx]!=e)
	{
		++idx;++pdx;
	}
	struct TreeNode *r=new TreeNode(e);
	r->left=preAndino(pre,preL+1,pdx,ino,inoL,idx-1);
	r->right=preAndino(pre,pdx+1,preR,ino,idx+1,inoR);
	return r;
}
void inotra(struct TreeNode *r)
{
	if(r)
	{
		inotra(r->left);
		printf("%d ",r->val);
		inotra(r->right);
	}
}
void pretra(struct TreeNode *r)
{
	if(r)
	{
		printf("%d ",r->val);
		pretra(r->left);
		pretra(r->right);
	}
}
void postra(struct TreeNode *r)
{
	if(r)
	{
		postra(r->left);
		postra(r->right);
		printf("%d ",r->val);
	}
}
void pretra_ur(struct TreeNode *r)
{
	struct TreeNode *stack[100],*p=r;
	int top=0;
	while(p||top)
	{
		if(p)
		{
			stack[top++]=p;
			printf("%d ",p->val);
			p=p->left;
		}
		else
		{
			p=stack[--top];
			p=p->right;
		}
	}
}
void inotra_ur(struct TreeNode *r)
{
	struct TreeNode *stack[100],*p=r;
	int top=0;
	while(p||top)
	{
		if(p)
		{
			stack[top++]=p;
			p=p->left;
		}
		else
		{
			p=stack[--top];
			printf("%d ",p->val);
			p=p->right;
		}
	}
}
void postra_ur(struct TreeNode *r)
{
	struct TreeNode *stack[100],*p=r,*pre=NULL;
	int top=0;
	while(p||top)
	{
		if(p)
		{
			stack[top++]=p;
			p=p->left;
		}
		else
		{
			p=stack[top-1];
			if(p->right&&pre!=p->right)//右子树不空并且前一个访问的节点不是右节点
			{
				p=p->right;
				stack[top++]=p;
				p=p->left;
			}
			else//右子树为空或者前一个访问的节点为p的右节点，自然p就应该被访问
			{
				p=stack[--top];
				printf("%d ",p->val);
				pre=p;//记录前一个访问节点
				p=NULL;//p置空
			}
		}
	}
}
void insertListNode(ListNode *&L,int n)
{
	ListNode *p=new ListNode(n),*s;
	s=L->next;
	L->next=p;
	p->next=s;
	L->val++;
}
ListNode *CreatList()
{
	int n;
	printf("input n:\n");
	cin>>n;
	ListNode *L=new ListNode(0);
	while(n--)
	{
		insertListNode(L,n);
	}
	return L;
}
void ListTra(ListNode *L)
{
	printf("Total %d list nodes: ",L->val);
	ListNode *p=L->next;
	while(p)
	{
		printf("%d ",p->val);
		p=p->next;
	}
}
void insertListPos(ListNode *&L,int pos,int e)
{
	if(pos<=0||pos>L->val+1)
	{
		printf("pos err!\n");
		return;
	}
	int k=0;
	ListNode *p=L;
	while(p->next)
	{
		++k;
		if(k==pos) break;
		p=p->next;
	}
	ListNode *s=new ListNode(e),*q;
	q=p->next;
	p->next=s;
	s->next=q;
	L->val++;
}
void helpFR(TreeNode *&r,TreeNode *&pre)
{
	if(!r)return;
	helpFR(r->right,pre);
	helpFR(r->left,pre);
	r->right=pre;
	r->left=NULL;
	pre=r;
}
void flattenRight(TreeNode *&r)
{
	TreeNode *pre=NULL;
	helpFR(r,pre);
}
void helpFL(TreeNode *&r,TreeNode *&pre)
{
	if(!r)return;
	helpFL(r->left,pre);
	helpFL(r->right,pre);
	r->left=pre;
	r->right=NULL;
	pre=r;
}
void flattenLeft(TreeNode *&r)
{
	TreeNode *pre=NULL;
	helpFL(r,pre);
}
void trvall(TreeNode *r)
{
	printf("\npreTraverse: ");
	pretra(r);
	printf("\ninoTraverse: ");
	inotra(r);
	printf("\nposTraverse: ");
	postra(r);
}
void flattenLeft_ur(TreeNode *&r)
{
	TreeNode *stack[100],*p=r,*pre=NULL;
	int top=0;
	while(p||top)
	{
		if(p)
		{
			stack[top++]=p;
			p=p->left;
		}
		else
		{
			p=stack[top-1];
			if(p->right&&pre!=p->right)
			{
				p=p->right;
				stack[top++]=p;
				p=p->left;
			}
			else
			{
				p=stack[--top];
				if(pre)
				{
					p->left=pre;
					p->right=NULL;
				}
				pre=p;
				p=NULL;
			}
		}
	}
}
void trvall_ur(TreeNode *r)
{
	printf("\npreTraverse unrecursion: ");
	pretra_ur(r);
	printf("\ninoTraverse unrecursion: ");
	inotra_ur(r);
	printf("\nposTraverse unrecursion: ");
	postra_ur(r);
}
void help(TreeNode *r,string &s)
{
	if(r)
	{
		//s+=to_string(r->val);
		if(r->left) s+='(';
		help(r->left,s);
		if(r->left) s+=')';
		if(r->right)
		{
			if(!r->left) s+="()";
			s+='(';
		}
		help(r->right,s);
		if(r->right) s+=')';
	}
}
string tree2str(TreeNode *t)
{
	string s;
	help(t,s);
	return s;
}
void prpreandinoarr(int n)
{
	printf("preArray : ");
	for(int i=0;i<n;++i)
		printf("%d ",pre[i]);
	printf("\ninoArray : ");
	for(int i=0;i<n;++i)
		printf("%d ",ino[i]);
	printf("\n");
}
int help(TreeNode *r,int &ret)
{
	if(r==NULL) return 0;
	int m=max(max(help(r->left,ret)+r->val,help(r->right,ret)+r->val),help(r->left,ret)+help(r->right,ret)+r->val);
	ret=max(m,ret);
	return m;
}
int helplus(TreeNode *r)
{
	if(r==NULL) return 0;
	return max(max(helplus(r->left)+r->val,helplus(r->right)+r->val),max(helplus(r->left)+helplus(r->right)+r->val,r->val));
}
void acc(TreeNode *r,int &ret)
{
	if(r)
	{
		acc(r->left,ret);
		ret=max(ret,helplus(r));
		acc(r->right,ret);
	}
}
int dalao(TreeNode *r,int &ret)
{
	if(r==NULL) return 0;
	int leftmax=dalao(r->left,ret);
	int rightmax=dalao(r->right,ret);
	leftmax=leftmax<0?0:leftmax;
	rightmax=rightmax<0?0:rightmax;
	int curmax=max(leftmax+rightmax+r->val,r->val);
	ret=max(ret,curmax);
	return r->val+max(leftmax,rightmax);
}
int maxPathSum(TreeNode* r)
{
	int ret=0x80000000;
	dalao(r,ret);
	return ret;
}
void aveLevHelp(vector<double> &res,vector<int> &cnt,unsigned int lev,TreeNode *r)
{
	if(r==NULL) return;
	if(lev+1>res.size())
	{
		res.push_back(0);
		cnt.push_back(0);
	}
	res[lev]+=r->val;
	cnt[lev]++;
	aveLevHelp(res,cnt,lev+1,r->left);
	aveLevHelp(res,cnt,lev+1,r->right);
}
vector<double> averageOfLevels(TreeNode* r)
{
	vector<double> res;
	vector<int> cnt;
	aveLevHelp(res,cnt,0,r);
	for(unsigned int i=0;i<res.size();++i)
	{
		res[i]/=cnt[i];
	}
	return res;
}
bool isSubHelp(TreeNode *s,TreeNode *t)
{
	if(!s&&!t) return true;
	else if(!s||!t) return false;
	if(s->val==t->val) return isSubHelp(s->left,t->left)&&isSubHelp(s->right,t->right);
	else return false;
}
bool isSubtree(TreeNode* s, TreeNode* t)
{
	if(s==NULL) return false;
	if(isSubHelp(s,t)) return true;
	return isSubtree(s->left,t)||isSubtree(s->right,t);
}
int tiltHelp(TreeNode *r,int &res)
{
	if(r==NULL)return 0;
	int lv=tiltHelp(r->left,res);
	int rv=tiltHelp(r->right,res);
	res+=abs(lv-rv);
	return lv+rv+r->val;
}
int findTilt(TreeNode* r)
{
	int res=0;
	tiltHelp(r,res);
	return res;
}
int dbHelp(TreeNode *r,int &res)
{
	if(!r)return 0;
	int lh=dbHelp(r->left,res)+1;
	int rh=dbHelp(r->right,res)+1;
	res=max(res,lh+rh-2);
	return max(lh,rh);
}
int diameterOfBinaryTree(TreeNode* root)
{
	int res=0;
	dbHelp(root,res);
	return res;
}
void hpsHelp(TreeNode *r,int cur,bool &flag,const int &sum)
{
	if(r)
	{
		if(!r->left&&!r->right&&cur+r->val==sum) flag=true;
		hpsHelp(r->left,cur+r->val,flag,sum);
		hpsHelp(r->right,cur+r->val,flag,sum);
	}
}
bool hasPathSum(TreeNode* root, int sum)
{
	bool flag=false;
	hpsHelp(root,0,flag,sum);
	return flag;
}
void lobHelp(vector<vector<int>> &res,unsigned int lev,TreeNode *r)
{
	if(r==NULL) return;
	if(lev+1>res.size())
	{
		res.push_back(vector<int>());
	}
	res[lev].push_back(r->val);
	lobHelp(res,lev+1,r->left);
	lobHelp(res,lev+1,r->right);
}
vector<vector<int>> levelOrderBottom(TreeNode* root)
{
	vector<vector<int>> res;
	lobHelp(res,0,root);
	int n=res.size();
	for(int i=0;i<n/2;++i)
	{
		swap(res[i],res[n-1-i]);
	}
	return res;
}
void sbHelp(TreeNode *r,int &res,int &sum)
{
	if(r)
	{
		res=res*10+r->val;
		if(!r->left&&!r->right)
			sum+=res;
		sbHelp(r->left,res,sum);
		sbHelp(r->right,res,sum);
		res/=10;
	}
}
int sumNumbers(TreeNode* root)
{
	int res=0,sum=0;
	sbHelp(root,res,sum);
	return sum;
}
void wbtHelp(vector<int> &lf,int idx,unsigned int lev,int &maxwid,TreeNode *r)
{
	if(r==NULL) return;
	if(lev+1>lf.size()) lf.push_back(idx);
	else maxwid=max(maxwid,idx+1-lf[lev]);
	wbtHelp(lf,2*idx,lev+1,maxwid,r->left);
	wbtHelp(lf,2*idx+1,lev+1,maxwid,r->right);
}
int widthOfBinaryTree(TreeNode* root)
{
	vector<int> lf;
	int maxwid=1;
	wbtHelp(lf,1,0,maxwid,root);
	return maxwid;
}
void zzloHelp(vector<vector<int>> &res,unsigned int lev,TreeNode *r)
{
	if(!r)return;
	if(lev+1>res.size())
	{
		res.push_back(vector<int>());
	}
	res[lev].push_back(r->val);
	zzloHelp(res,lev+1,r->left);
	zzloHelp(res,lev+1,r->right);
}
vector<vector<int>> zigzagLevelOrder(TreeNode* root)
{
	vector<vector<int>> res;
	zzloHelp(res,0,root);
	for(unsigned int i=0;i<res.size();++i)
	{
		if(i%2==1)
		{
			int n=res[i].size();
			for(int k=0;k<n/2;++k)
				swap(res[i][k],res[i][n-1-k]);
		}
	}
	return res;
}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
	/*if(!root||root==p||root==q) return root;
	TreeNode *left=lowestCommonAncestor(root->left,p,q);
	TreeNode *right=lowestCommonAncestor(root->right,p,q);*/
	return NULL;
}
void CBSTHelp(TreeNode *r,int &sum)
{
	if(r==NULL) return;
	if(r->right)
		CBSTHelp(r->right,sum);
	sum+=r->val;
	r->val=sum;
	if(r->left)
		CBSTHelp(r->left,sum);
}
TreeNode* convertBST(TreeNode* root)
{
	if(root==NULL) return NULL;
	int sum=0;
	CBSTHelp(root,sum);
	return root;
}
void fsmhelp(TreeNode *r,int &fst,int &scd)
{
	if(r->left==NULL) return;
	int x=min(r->left->val,r->right->val);
	int y=max(r->left->val,r->right->val);
	fst=min(fst,x);
	if(fst>x) scd=min(scd,x);
	else if(x!=y) scd=min(scd,y);
	fsmhelp(r->left,fst,scd);
	fsmhelp(r->right,fst,scd);
}
int findSecondMinimumValue(TreeNode* root)
{
	int fst=0x7fffffff,scd=0x7fffffff;
	fsmhelp(root,fst,scd);
	return (scd==0x7fffffff)?-1:scd;
}
TreeNode *searchNode(int val,TreeNode *r)
{
	if(r==NULL) return NULL;
	if(r->val==val) return r;
	TreeNode *ret=searchNode(val,r->left);
	return ret?ret:searchNode(val,r->right);
}
void pathhelp(TreeNode *r,int n,vector<int> &path,vector<int> &recp)
{
	if(r)
	{
		pathhelp(r->left,n,path,recp);
		pathhelp(r->right,n,path,recp);
		if(r->val==n) path=recp;
	}
}
void hhh(TreeNode *r,int n)
{
	if(r)
	{
		if(r->val==0)
		{
			printf("%d -> ",r->val);
			return;
		}
		hhh(r->left,n);
		hhh(r->right,n);
		printf("%d -> ", r->val);
	}
}
void findPath(TreeNode *r,int m,int n)
{
	TreeNode *s=searchNode(m,r);
	hhh(s,n);
}
int main()
{
	/*ListNode *L=CreatList();
	ListTra(L);
	printf("\n");
	insertListPos(L,0,-100);
	insertListPos(L,1,-45);
	insertListPos(L,400,-22);
	ListTra(L);*/
	int n=sizeof(ino)/sizeof(int);
	//prpreandinoarr(n);
	struct TreeNode *r=preAndino(pre,0,n-1,ino,0,n-1);
	trvall(r);
	printf("\n");
	//printf("Total nodes: %d",n);
	//trvall(r);
	/*flattenLeft(r);
	trvall(r);
	flattenRight(r);
	trvall(r);
	flattenLeft_ur(r);
	trvall(r);*/
	//string str=tree2str(r);
	//cout<<endl<<str;
	//cout<<maxPathSum(r);
	/*vector<double> res=averageOfLevels(r);
	for(auto x:res)
	{
		cout<<x<<" ";
	}*/
	/*vector<vector<int>> res=levelOrderBottom(r);
	for(auto x:res)
	{
		for(auto y:x)
			cout<<y<<" ";
		cout<<endl;
	}*/
	//TreeNode *sr=convertBST(r);
	/*trvall(r);
	//cout<<findSecondMinimumValue(r);
	bool ret=0,gg=0;
	int s=1,e=8;
	printf("\n");
	searchPathpos(NULL,r,s,e,ret,gg);*/
	findPath(r,2,8);
	return 0;
}
