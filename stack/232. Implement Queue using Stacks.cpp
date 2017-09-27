#include <iostream>
#include <vector>
#include <stack>
using namespace std;
class MyQueue 
{
    stack<int> in,out;
public:
    void push(int x)
    {
    	in.push(x);
    }
    int pop()
    {
    	if(empty())
    	{
    		cout<<"empty queue!\n";
    		return -1;
    	}
    	int x=peek();
    	out.pop();
    	return x;
    }
    int peek()
    {
    	if(empty())
    	{
    		cout<<"empty queue!\n";
    		return -1;
    	}
    	if(out.empty())
    	{
    		while(!in.empty())
    			out.push(in.top()),in.pop();
    	}
    	return out.top();
    }
    bool empty()
    {
    	return in.empty()&&out.empty();
    }
};
int main()
{
	MyQueue q;
	int x=0;
	while(true)
	{
		string com;
		cin>>com;
		if(com=="push")
		{
			cin>>x;
			q.push(x);
		}
		else if(com=="pop")
			cout<<q.pop()<<endl;
		else if(com=="peek")
			cout<<q.peek()<<endl;
		else if(com=="empty")
			q.empty()?cout<<"Y\n":cout<<"N\n";
		else cout<<"error command\n";
	}
	return 0;
}
