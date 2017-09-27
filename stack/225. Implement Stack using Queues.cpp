#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class MyStack {
	queue<int> q;
public:
    void push(int x)
    {
    	q.push(x);
    	for(size_t i=0;i<q.size()-1;++i)
    	{
    		q.push(q.front());
    		q.pop();
    	}
    }
    int pop()
    {
    	if(empty())
    	{
    		cout<<"empty stack\n";
    		return -1;
    	}
    	int x=top();
    	q.pop();
    	return x;
    }
    int top()
    {
    	if(empty())
    	{
    		cout<<"empty stack\n";
    		return -1;
    	}
    	return q.front();
    }
    bool empty()
    {
    	return q.empty();
    }
};
int main()
{
	MyStack stk;
	int x=0;
	while(true)
	{
		string com;
		cin>>com;
		if(com=="push")
		{
			cin>>x;
			stk.push(x);
		}
		else if(com=="pop")
			cout<<stk.pop()<<endl;
		else if(com=="top")
			cout<<stk.top()<<endl;
		else if(com=="empty")
			stk.empty()?cout<<"Y\n":cout<<"N\n";
		else cout<<"error command\n";
	}
	return 0;
}
