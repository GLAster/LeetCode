#include <iostream>//dp problem
#include <vector>
#include <algorithm>
using namespace std;
vector<int> v={227,99,328,299,42,322};
int coinChange(vector<int>& coins, int amount)
{
	if(amount<1) return 0;
	vector<int> dp(amount+1,amount+1);
	dp[0]=0;
	for(int i=1;i<=amount;++i)
	{
		for(int x:coins)
			if(x<=i)
				dp[i]=min(dp[i],dp[i-x]+1);
	}
	return dp[amount]>amount?-1:dp[amount];
}
int uniquePaths(int m, int n)
{
	vector<vector<int>> dp(m+1,vector<int>(n+1,1));
	for(int i=2;i<=m;++i)
	{
		for(int j=2;j<=n;++j)
		{
			dp[i][j]=dp[i-1][j]+dp[i][j-1];
		}
	}
	return dp[m][n];
}
int maximalSquare(vector<vector<char>>& matrix)
{
	int m=matrix.size(),n=matrix[0].size(),maxsize=-1;
	vector<vector<int>> dp(m,vector<int>(n,0));
	for(int i=0;i<n;++i)
	{
		dp[0][i]=matrix[0][i]-'0';
		maxsize=max(maxsize,dp[0][i]);
	}
	for(int i=0;i<m;++i)
	{
		dp[i][0]=matrix[i][0]-'0';
		maxsize=max(maxsize,dp[i][0]);
	}
	for(int i=1;i<m;++i)
	{
		for(int j=1;j<n;++j)
		{
			if(matrix[i][j]=='0') dp[i][j]=0;
			else dp[i][j]=min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]))+1;
			maxsize=max(maxsize,dp[i][j]);
		}
	}
	return maxsize*maxsize;
}
int help(vector<int> &nums,int s,int e)
{
	int a=0,b=0;
	for(int i=s;i<=e;++i)
	{
		int t=max(a+nums[i],b);
		a=b;
		b=t;
	}
	return max(a,b);

}
int rob(vector<int> &nums)
{
	int n=nums.size();
	if(n==0) return 0;
	else if(n==1) return nums[0];
	else return max(help(nums,0,n-2),help(nums,1,n-1));
}
int uniquePathsWithObstacles(vector<vector<int>>& v)
{
	if(v.size()==0) return 0;
	int m=v.size(),n=v[0].size();
	vector<vector<int>> dp(m,vector<int>(n,0));
	bool flag=true;
	for(int i=0;i<n;++i)
	{
		if(v[0][i]==1) flag=false;
		dp[0][i]=flag;
	}
	flag=true;
	for(int i=0;i<m;++i)
	{
		if(v[i][0]==1) flag=false;
		dp[i][0]=flag;
	}
	for(int i=1;i<m;++i)
	{
		for(int j=1;j<n;++j)
		{
			if(v[i][j]==0)
			{
				dp[i][j]=dp[i][j-1]+dp[i-1][j];
			}
		}
	}
	return dp[m-1][n-1];
}
int numSquares(int n)
{
	if(n<=0) return 0;
	vector<int> dp(n+1,0x7fffffff);
	dp[0]=0;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j*j<=i;++j)
			dp[i]=min(dp[i],dp[i-j*j]+1);
	}
	return dp[n];
}
int minSteps(int n)
{
	int dp[n+1];
	dp[1]=0;
	for(int i=2;i<=n;++i)
	{
		dp[i]=i;
		for(int k=1;k*k<=i;++k)
		{
			if(i%k==0)
				dp[i]=min(min(dp[k]+i/k,dp[i/k]+k),dp[i]);
		}
	}
	return dp[n];
}
int minSteps1(int n)
{
	vector<int> dp(n+1,1024);
	dp[1]=0;
	for(int i=2;i<=n;++i)
	{
		for(int k=1;k*k<=i;++k)
		{
			if(i%k==0)
				dp[i]=min(min(dp[k]+i/k,dp[i/k]+k),dp[i]);
		}
	}
	return dp[n];
}
void cchelp(vector<int> &v,int &res,int &bc,int amount,int i)
{
	if(amount<0) return;
	else if(amount==0)
	{
		if(bc<res) res=bc;
		return;
	}
	for(int k=i;k>=0;--k)
	{
		++bc;
		cchelp(v,res,bc,amount-v[k],k);
		--bc;
		if(amount-v[k]<0) return;
	}
}
int coinChange2(vector<int>& v, int amount)
{
	if(v.size()==0) return 0;
	int res=0x7fffffff,bc=0;
	sort(v.begin(),v.end(),greater<int>());
	cchelp(v,res,bc,amount,v.size()-1);
	return res==0x7fffffff?-1:res;
}
int main()
{
	//cout<<coinChange(v,4)<<endl;
	/*std::vector<std::vector<char>> vm;
	vm.push_back(std::vector<char> {'1','0','1','0','0'});
	vm.push_back(std::vector<char> {'1','0','1','1','1'});
	vm.push_back(std::vector<char> {'1','1','1','1','1'});
	vm.push_back(std::vector<char> {'1','0','0','1','0'});*/
	/*vector<vector<int>> vm;
	vm.push_back(vector<int>(3,0));
	vm.push_back(vector<int>{0,1,0});
	vm.push_back(vector<int>(3,0));*/
	cout<<coinChange2(v,9847);
	return 0;
}
