#include<stdio.h>

struct process
{
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

void completion_time(process p[], int size)
{
    int i;
    p[0].ct = p[0].bt +p[0].at;
    for(i=1; i<size; i++)
    {
        if(p[i-1].ct < p[i].at)
            p[i].ct = p[i].bt +p[i].at;
        else
            p[i].ct = p[i].bt +p[i-1].ct;
    }
}


void turn_around_time(process p[], int size)
{
    int i;
    float avg, temp=0.0;
    for(i=0; i<size; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        temp += p[i].tat;
    }
    avg = temp/size;
    printf("\nAverage Turn around time = %f", avg);
}
void avg_waiting_time(process p[], int size)
{
    int i;
    float avg, temp = 0.0;
    for(i=0; i<size; i++)
    {
        p[i].wt = p[i].tat - p[i].bt;
        temp += p[i].wt;
    }
    avg = temp/size;
    printf("\nAverage Waiting time = %f",avg);
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
    }

    sort(p ,n);
    completion_time(p,n);
    turn_around_time(p,n);
    avg_waiting_time(p,n);
    printf("\n Process No.    Arrival Time    Burst Time    Completion Time    Turn Around Time    Waiting Time\n");
    for(i=0; i<n; i++ )
        printf("\n\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    return 0;
}
