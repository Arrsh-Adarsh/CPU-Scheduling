#include<stdio.h>
#include<limits.h>
struct process
{
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int key;
};

void completion_time(struct process p[], int size)
{
    int i,flag=1, temp = 0, pos = 0;

    while(flag)
    {
        int copy[2][20];
        int j=0;
        flag = 0;
        for(i=0; i<size; i++)
            if(p[i].key==0 && p[i].at<temp)
            {
                copy[0][j] = p[i].id;
                copy[1][j++] = p[i].bt;
            }
        if(j==0)
        {
            int temp1=INT_MAX;
            for(i=0; i<size; i++)
                if(p[i].at <temp1 && p[i].key==0 )
                 {
                     temp1 = p[i].at;
                     pos = i;
                 }
            temp = p[pos].ct = p[pos].at + p[pos].bt;
            p[pos].key = 1;
        }
        else
        {
            sort(copy , j);
            if(temp < p[copy[0][0]-1].at)
            {
                temp = p[copy[0][0]-1].ct = p[copy[0][0]-1].at; + p[copy[0][0]-1].bt;
            }
            else
            {
                temp = p[copy[0][0]-1].ct = temp + p[copy[0][0]-1].bt;
            }
            p[copy[0][0]-1].key = 1;
        }
        for(i=0; i<size; i++)
            if(p[i].key == 0)
                flag = 1;
    }
}

void turn_around_time(struct process p[], int size)
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

void avg_waiting_time(struct process p[], int size)
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
void sort(int p[2][20], int size)
{
    int i, j, pos, temp;
    for(i=0; i<size-1; i++)
    {
        pos=i;
        for(j=i; j<size; j++)
            if(p[1][j] < p[1][pos])
                pos = j;

        temp = p[1][i];
        p[1][i] = p[1][pos];
        p[1][pos] = temp;

        temp = p[0][i];
        p[0][i] = p[0][pos];
        p[0][pos] = temp;
    }
}

int main()
{
    int n,i;
    printf("Enter total no. of process: ");
    scanf("%d",&n);
    struct process p[n];
    for(i=0; i<n; i++)
    {
        p[i].id = i+1;
        p[i].key = 0;
        printf("\nEnter Arrival Time and Burst Time for process %d : ",i+1);
        scanf("%d%d",&p[i].at, &p[i].bt );
    }

    completion_time(p,n);
    turn_around_time(p,n);
    avg_waiting_time(p,n);
    printf("\n Process No.    Arrival Time    Burst Time    Completion Time    Turn Around Time    Waiting Time\n");
    for(i=0; i<n; i++ )
        printf("\n\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    return 0;
}
