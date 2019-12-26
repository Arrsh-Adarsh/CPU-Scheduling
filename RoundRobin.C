#include<stdio.h>

int tq ,gt=0;       // tq- time quantum and gt-executed time of cpu
int q[100],front=-1,rear=-1;
struct process
{
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rbt;        // remaining burst time
    int key;        //determines whether process is present in queue or not
};
void enQ(int ele)
{
    if(front== -1 && rear==-1)
        front =rear =0;
    else
        rear++;
    q[rear]=ele;
}
int deQ()
{
    int e= q[front];
    if(front== rear)
        front = rear = -1;
    else
        front++;
    return e;
}

int isQEmpty()
{
    if(front==-1 && rear == -1)
        return 1;
    else
        return 0;
}

void completion_time(process p[], int size)
{
    enQ(p[0].id -1);
    p[0].key =1;
    gt = p[0].at;
    while(!isQEmpty())
    {
        int i;
        int id =deQ();
        if(p[id].rbt <= tq)
        {
            gt =gt + p[id].rbt;
            p[id].rbt = 0;
            p[id].ct = gt;
        }
        else
        {
            p[id].rbt -= tq;
            gt += tq;
        }
        for(i=0; i<size; i++)
        {
            if(p[i].rbt > 0 && p[i].at <= gt && p[i].key == 0)
             {
                 enQ(p[i].id -1);
                 p[i].key = 1;
             }
        }
        if(p[id].rbt != 0)          //adding currently processed process in queue at end
            enQ(p[id].id-1);

    }
}

void sort(process p[], int size)
{
    int i,j,pos;
    process temp;
    for(i=0; i<size-1; i++)
    {
        pos=i;
        for(j=i; j<size; j++)
        {
            if(p[j].at < p[pos].at)
                pos = j;
        }
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }
}

int main()
{
    int n,i;
    printf("Enter total no. of process: ");
    scanf("%d",&n);
    process p[n];
    for(i=0; i<n; i++)
    {
        p[i].id = i+1;
        printf("\nEnter Arrival Time and Burst Time for process %d : ",i+1);
        scanf("%d%d",&p[i].at, &p[i].bt );
        p[i].rbt = p[i].bt ;
        p[i].key = 0;
    }

    printf("Enter Time quantum : ");
    scanf("%d", &tq);

    sort(p,n);
    completion_time(p,n);

    float avg, temp1=0.0,temp2=0.0;
    for(i=0; i<n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        temp1 += p[i].tat;
        p[i].wt = p[i].tat - p[i].bt;
        temp2 += p[i].wt;
    }
    avg = temp1/n;
    printf("\nAverage Turn around time = %f", avg);
    avg = temp2/n;
    printf("\nAverage Waiting time = %f", avg);
    //turn_around_time(p,n);
    //avg_waiting_time(p,n);
    printf("\n Process No.    Arrival Time    Burst Time    Completion Time    Turn Around Time    Waiting Time\n");
    for(i=0; i<n; i++ )
        printf("\n\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    return 0;
}
