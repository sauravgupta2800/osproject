#include<stdio.h>
#include<iostream>
#include<queue>

using namespace std;
#define MAX 1000
#define QUANTA 4

int flag[MAX],at[MAX],bt[MAX],pt[MAX],rt[MAX],ft[MAX],fe[MAX],fe_flag[MAX],pid[MAX],tms,qt[MAX];

//at arrival time
//bt burst time
//rt Response Time
//pt priority
//pid process id

queue<int> q;  //RR queue

void RR()
{
      if(!q.empty())
      {
      	if(rt[q.front()]>0 && qt[q.front()]<4)
      	{
          		qt[q.front()]++;
          		rt[q.front()]--;
          		if(rt[q.front()]==0)
          		{
            	ft[q.front()]=tms+1;
            	q.pop();
          		}
          		if(rt[q.front()]!=0 && qt[q.front()]==4)
          		{
				qt[q.front()]=0;
				q.push(q.front());
				q.pop();
          		}
        	}
      }
}
int main()
{

}
