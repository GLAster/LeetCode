#include <iostream>//array problem
#include <vector>
#include <array>
#include <unordered_map>
#include <deque>
#include <algorithm>
using namespace std;
vector<int> v={1,2,3,4,5,6,1};
int findMin(vector<int>& nums)
{
	int low=0,high=nums.size()-1;
	while(low<high)
	{
		if(nums[low]<nums[high]) return nums[low];
		int mid=(low+high)/2;
		if(nums[mid]>=nums[low])low=mid+1;
		else if(nums[mid]<nums[low]) high=mid;
	}
	return nums[low];
}
int subarraySum(vector<int>& nums, int k)
{
	int cnt=0,n=nums.size(),sum=0;
	vector<int> acc(n+1,0);
	acc[0]=0;
	for(int i=0;i<n;++i)
	{
		sum+=nums[i];
		acc[i+1]=sum;
	}
	for(int i=0;i<n;++i)
	{
		for(int j=i;j<n;++j)
		{
			if(acc[j+1]-acc[i]==k)cnt++;
		}
	}
	return cnt;
}
int subarraySum2(vector<int>& nums, int k)//use hash
{
	int sum=0,cnt=0;
	unordered_map<int,int> hash;
	hash[0]=1;
	for(int x:nums)
	{
		sum+=x;
		cnt+=hash[sum-k];
		++hash[sum];
	}
	return cnt;
}
void cbhelp(vector<vector<int>> &res,vector<int> &v,int target,int i,vector<int> recp)
{
	if(target<0) return;
	else if(target==0)
	{
		res.push_back(recp);
		return;
	}
	for(unsigned int k=i;k<v.size();++k)
	{
		recp.push_back(v[k]);
		cbhelp(res,v,target-v[k],k,recp);
		recp.pop_back();
		if(target-v[k]<0) return;
	}
}
vector<vector<int>> combinationSum(vector<int>& v, int target)
{
	sort(v.begin(),v.end());
	vector<vector<int>> res;
	vector<int> recp;
	cbhelp(res,v,target,0,recp);
	return res;
}
int findPoisonedDuration(vector<int>& timeSeries, int duration)
{
	if(timeSeries.size()==0) return 0;
	int cnt=0;
	for(unsigned int i=0;i<timeSeries.size()-1;++i)
	{
		int nt=timeSeries[i]+duration;
		if(nt<=timeSeries[i+1]) cnt+=duration;
		else
		{
			cnt+=timeSeries[i+1]-timeSeries[i];
		}
	}
	cnt+=duration;
	return cnt;
}
void cb2help(vector<vector<int>> &res,vector<int> &v,int target,unsigned int i,vector<int> recp)
{
	if(target<0) return;
	else if(target==0)
	{
		res.push_back(recp);
		return;
	}
	for(unsigned int k=i;k<v.size();++k)
	{
		if(k>i&&v[k]==v[k-1]) continue;
		recp.push_back(v[k]);
		cb2help(res,v,target-v[k],k+1,recp);
		recp.pop_back();
		if(target-v[k]<0) return;
	}
}
vector<vector<int>> combinationSum2(vector<int>& v, int target)
{
	sort(v.begin(),v.end());
	vector<vector<int>> res;
	vector<int> recp;
	cb2help(res,v,target,0,recp);
	return res;
}
vector<int> findDuplicates(vector<int>& nums)
{
	vector<int> res;
	for(unsigned int i=0;i<nums.size();++i)
	{
		nums[abs(nums[i])-1]=-nums[abs(nums[i])-1];
		if(nums[abs(nums[i])-1]>0) res.push_back(abs(nums[i]));
	}
	return res;
}
int maxArea(vector<int>& height)
{
	int i=0,j=height.size()-1;
	int maxA=0;
	while(i<j)
	{
		int h=min(height[i],height[j]);
		maxA=max(maxA,(j-i)*h);
		while(i<j&&height[i]<=h)++i;
		while(i<j&&height[j]<=h)--j;
	}
	return maxA;
}
void tshelp(vector<vector<int>> &res,vector<int> &ths,vector<int> &nums,int &cnt,int &sum,unsigned int cur)
{
	if(cnt==3&&sum==0)
	{
		res.push_back(ths);
		return;
	}
	else if(cnt>3||(cnt==3&&sum!=0))
		return;
	for(unsigned int i=cur;i<nums.size();++i)
	{
		if(i>cur&&nums[i]==nums[i-1]) continue;
		ths.push_back(nums[i]);
		sum+=nums[i];
		++cnt;
		tshelp(res,ths,nums,cnt,sum,i+1);
		sum-=nums[i];
		--cnt;
		ths.pop_back();
	}
}
vector<vector<int>> threeSum_gg(vector<int>& nums)
{
	sort(nums.begin(),nums.end());
	vector<vector<int>> res;
	vector<int> ths;
	int sum=0,cnt=0;
	tshelp(res,ths,nums,cnt,sum,0);
	return res;
}
vector<vector<int>> threeSum(vector<int>& nums)
{
	sort(nums.begin(),nums.end());
	vector<vector<int>> res;
	int n=nums.size();
	for(int i=0;i<n-2;++i)
	{
		if(i>0&&nums[i]==nums[i-1]) continue;
		int target=-nums[i];
		int low=i+1,high=n-1;
		while(low<high)
		{
			if(nums[low]+nums[high]==target)
			{
				res.push_back(vector<int>{nums[i],nums[low],nums[high]});
				++low;
				--high;
				while(low<high&&nums[low]==nums[low-1]) ++low;
				while(low<high&&nums[high]==nums[high+1]) --high;
			}
			else if(nums[low]+nums[high]>target) --high;
			else ++low;
		}
	}
	return res;
}
vector<int> twoSum(vector<int>& nums, int target)
{
	unordered_map<int,int> hash;
	int n=nums.size();
	for(int i=0;i<n;++i)
	{
		if(hash[target-nums[i]]) return {i,hash[target-nums[i]]-1};
		hash[nums[i]]=i+1;
	}
	return {0,0};
}
vector<int> twoSum2(vector<int>& nums, int target)
{
	unordered_map<int,int> hash;
    int n=nums.size();
	for(int i=0;i<n;++i)
	{
		if(hash.find(target-nums[i])!=hash.end()) return {i,hash[target-nums[i]]-1};
		hash[nums[i]]=i+1;
	}
	return {0,0};
}
void rhelp(vector<int> &nums,int L,int R)
{
	while(L<R)
	{
		swap(nums[L],nums[R]);
		++L,--R;
	}
}
void rotate(vector<int>& nums, int k)
{
	int n=nums.size();
	if(n==0||n==1) return;
	k=k%n;
	rhelp(nums,0,n-k-1);
	rhelp(nums,n-k,n-1);
	rhelp(nums,0,n-1);
}
int findDuplicate(vector<int>& nums)
{
	int n=nums.size()-1;
	int low=0;
	int high=n;
	while(low<high)
	{
		int mid=(low+high)/2;
		int cnt=0;
		for(auto x:nums)
		{
			if(x<=mid) ++cnt;
		}
		if(cnt>mid) high=mid;
		else low=mid+1;
		cout<<low<<":"<<high<<endl;
	}
	return low;
}
bool containsDuplicate(vector<int>& nums)
{
	unordered_map<int,int> ump;
	for(auto x:nums)
	{
		if(ump[x]==1) return true;
		else ump[x]=1;
	}
	return false;
}
bool containsNearbyDuplicate(vector<int>& nums, int k)
{
	unordered_map<int,int> ump,ump2;
	int n=nums.size(),i=0;
	while(i<n)
	{
		int j=i+1;
		while(j<n&)
	}
	return false;
}

int main()
{
	/*vector<vector<int>> res=threeSum(v);
	for(auto x:res)
	{
		for(auto y:x)
			cout<<y<<" ";
		cout<<endl;
	}*/
	//cout<<maxArea(v);
	//rotate(v,3);
	/*vector<int> res=v;
	for(auto x:res)
		cout<<x<<" ";*/
	cout<<containsDuplicate(v);
	return 0;
}
