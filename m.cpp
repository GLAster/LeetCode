#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<int> indegree(numCourses,0);
        vector<vector<int>> v(numCourses);
        for(auto &x:prerequisites){
            indegree[x.first]++;
            v[x.second].push_back(x.first);
        }
        queue<int> q;
        for(int i=0;i<numCourses;++i){
            if(indegree[i]==0) q.push(i);
        }
        int cnt=0;
        while(!q.empty()){
            int w=q.front();
            q.pop();
            ++cnt;
            for(int u:v[w]){
                indegree[u]--;
                if(indegree[u]==0) q.push(u);
            }
        }
        return cnt==numCourses;
    }
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<int> indegree(numCourses,0),res;
        vector<vector<int>> v(numCourses);
        for(auto &x:prerequisites){
            indegree[x.first]++;
            v[x.second].push_back(x.first);
        }
        queue<int> q;
        for(int i=0;i<numCourses;++i){
            if(indegree[i]==0) q.push(i);
        }
        while(!q.empty()){
            int w=q.front();
            q.pop();
            res.push_back(w);
            for(int u:v[w]){
                indegree[u]--;
                if(indegree[u]==0) q.push(u);
            }
        }
        if(res.size()!=numCourses) res.clear();
        return res;
    }
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n=edges.size();
        vector<int> parents(n+1);
        for(int i=1;i<=n;++i){
            parents[i]=i;
        }
        for(auto e:edges){
            int x=e[0],y=e[1];
            int l1=find(x,parents),l2=find(y,parents);
            if(l1==l2)
                return e;
            parents[l1]=l2;
        }
        return {-1,-1};
    }
    int find(int x,vector<int> &parents){
        return x==parents[x]?x:parents[x]=find(parents[x],parents);
    }
    int majorityElement(vector<int>& nums) {
        map<int,int> mp;
        for(int x:nums) mp[x]++;
        for(auto x:mp)
            if(x.second>nums.size()/2) return x.first;
        return -1;
    }
    int majorityElement2(vector<int>& nums) {
    	int major=0,counts=0;
        for(int x:nums){
        	if(counts==0){
        		major=x;
        		counts=1;
        	}else if(major==x) ++counts;
        	else --counts;
        }
        return counts;
    }
};
void disv(vector<int> &v){
	for(auto x:v){
		cout<<x<<" ";
	}
	cout<<endl;
}
void disvv(vector<vector<int>> &v){
	for(auto &vx:v){
		for(auto x:vx){
			cout<<x<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
int main()
{
	Solution x;
	// vector<vector<char>> v={{'1','1','1','1','0'},{'1','1','0','1','0'},{'1','1','0','0','0'},{'0','0','0','0','0'}};
	vector<pair<int,int>> v={{0,1}};
	// v.push_back(make_pair(0,1));
	auto res=x.findOrder(2,v);
	disv(res);
	// cout<<res<<endl;
	return 0;
}
