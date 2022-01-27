#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
struct Queue{
	int front,rear;
	int *array;
};
struct Queue* createQueue()
{
	struct Queue* queue=(struct Queue*)malloc(sizeof(struct Queue));
	queue->front=0;
	queue->rear=-1;
	queue->array=(int*)malloc(sizeof(int));
	return queue;
}

void enqueue(struct Queue* queue,int item)
{
     queue->rear+=1;
     queue->array[queue->rear]=item;
}

int dequeue(struct Queue* queue)
{
     int item;
     item=queue->array[queue->front];
     queue->front+=1;
     return item;
}

int main()
{
	struct Queue* queue=createQueue();
	int n,i,quant,at[10],bt[10],ct[10],temp[10],minatp,minat,total=0,first,count=0,ttt=0,twt=0;
	float avgtt,avgwt;
	printf("Enter the number of processes\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter arrival time and burst time of process %d\n",i+1);
		scanf("%d %d",&at[i],&bt[i]);
		temp[i]=bt[i];
	}
	printf("Entter the value of quantum\n");
	scanf("%d",&quant);
	minatp=at[n-1];
	for(i=0;i<n-1;i++)
	{
		if(at[i]<minatp)
			minatp=at[i];
	}
	for(i=0;i<n;i++)
	{
		if(at[i]<=minatp)
		{
			enqueue(queue,i);
		}
	}
	while(count!=n)
	{
		first=dequeue(queue);
		if(bt[first]<=quant)
		{
			total+=bt[first];
			bt[first]=0;
			ct[first]=total;
			count++;
		}
		else
		{
			total+=quant;
			bt[first]-=quant;
		}
		minat=total;
		for(i=0;i<n;i++)
                {
                     if((at[i]>minatp)&&(at[i]<=minat))
		     {
		             enqueue(queue,i);
		     }
                }
		if(bt[first]>0)
		{
			enqueue(queue,first);
		}
		minatp=minat;
	}
	printf("P\tAt\tBt\tTat\tct\twt\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],temp[i],ct[i]-at[i],ct[i],ct[i]-at[i]-temp[i]);
		ttt=ttt+ct[i]-at[i];
		twt=twt+ct[i]-at[i]-temp[i];
	}
	avgtt=(float)ttt/(float)n;
	avgwt=(float)twt/(float)n;
	printf("Avg TAT is %.3f\nAvg WT is %.3f\n",avgtt,avgwt);
        return 0;
	}