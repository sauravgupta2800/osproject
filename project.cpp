#include<stdio.h>
#include<iostream>
#include<queue>

using namespace std;

#define MAX_SIZE 1000
#define TIME_QUANTUM 4

int flag[MAX_SIZE],
arrivalTime[MAX_SIZE],//ARRIVAL TIME
burstTime[MAX_SIZE],//BURST TIME
pt[MAX_SIZE],//PRIORITY
rt[MAX_SIZE],//RESPONSE TIME
ft[MAX_SIZE],//FINISH TIME
fe[MAX_SIZE],
fe_flag[MAX_SIZE],
pid[MAX_SIZE],
tms,
qt[MAX_SIZE];

queue<int> q;  //RoundRobin queue


void RoundRobin()
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
    int i=0,n=0,smallest=0,last_smallest=-1,min,sum=0,large=0;
	printf("========NUM OF PROCESSES=========\n");
	printf("\nHow the number of processes : ");
    scanf("%d",&n);
	printf("\n============INPUT==========\n");
	printf("\n<PID>  <AT>    <BT>   <PRI>\n");
    for(i=0;i<n;i++)
    {
    		scanf("%d %d %d %d",&pid[i],&arrivalTime[i],&burstTime[i],&pt[i]);
    		if(arrivalTime[i]>large)
			{
				large=arrivalTime[i];
			}
    		sum+=burstTime[i];
    		rt[i]=burstTime[i];
    }
    min=MAX_SIZE;
    for(tms=0;!q.empty() || tms<=sum+large ;tms++)
    {
      min=MAX_SIZE;
      smallest=-1;
      for(i=0;i<n;i++)
      {
      	if(arrivalTime[i]<=tms && pt[i]< min && rt[i]>0 && !flag[i])
      	{
      		min=pt[i];
          	smallest=i;
        }
      }
      if(smallest==-1 && !q.empty())
      {
      	if(last_smallest !=-1 && rt[last_smallest]==0)
      	{
      		ft[last_smallest]=tms;
          	flag[last_smallest]=1;
        }
        last_smallest=-1;
        RoundRobin(); // calling of method RoundRobin Queue will implements from here
        continue;
      }
      else if(smallest!=-1 && !q.empty() && last_smallest==-1)
      {
      	if(qt[q.front()]<=4 && qt[q.front()]>0)
      	{
      		q.push(q.front());
      		q.pop();
        }
      }
      if(smallest!=-1 && !fe_flag[smallest])
      {
      	fe[smallest]=tms-arrivalTime[smallest];
      	fe_flag[smallest]=1;
      }
      if( smallest!=last_smallest && last_smallest!=-1 && !flag[last_smallest])
      {
      	q.push(last_smallest);
      	flag[last_smallest]=1;
      }
      if(smallest !=-1)
      	rt[smallest]--;
      
      if((smallest !=-1) && ((rt[smallest]==0) ||(burstTime[smallest]-rt[smallest])==TIME_QUANTUM))
      {
      	if((burstTime[smallest]-rt[smallest])==TIME_QUANTUM && rt[smallest]!=0)
      	{
      		flag[smallest]=1;
      		q.push(smallest);
        }
       	else if(smallest!=-1)
       	{
          		ft[smallest]=tms+1;
          		flag[smallest]=1;
        }
      }
      last_smallest=smallest;
    }
	printf("\n============OUTPUT==========\n");
	printf("\n<PID>   <RT>	<FT>	<WT>\n");
   for(int i=0;i<n;i++)
      cout<<pid[i]<<"	 "<<fe[i]<<"	 "<<ft[i]<<"	  "<<ft[i]-burstTime[i]-arrivalTime[i]<<endl;
    return 0;
}
