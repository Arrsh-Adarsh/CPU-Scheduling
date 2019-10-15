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
    int rbt;
    int key;
};

void completion_time(struct process p[], int size)
{
    int i,flag=1, temp = 0, pos = 0;

    while(flag)
    {
        int arr[2][20], j=0;
        flag = 0;
        for(i=0; i<size; i++)
            if(p[i].rbt > 0 && p[i].at<temp)
            {
                arr[0][j] = p[i].id;
                arr[1][j++] = p[i].rbt;
            }
        if(j != 0)
        {
            sort(arr, j);
            int k = arr[0][0] - 1;
            p[k].ct = temp;
            p[k].key = 1;
            p[k].rbt --;
        }
        temp++;
        for(i =0; i<size; i++)
            if(p[i].key == 0)
                flag = 1;
    }
    int j =0, arr[2][20];
    for(i=0; i<size; i++)
        if(p[i].rbt > 0)
        {
            arr[0][j] = p[i].id;
            arr[1][j++] = p[i].rbt;
        }
    sort(arr , j);
    temp--;
    for(i=0; i<j; i++)
    {
        int k = arr[0][i] - 1;
        if(p[k].rbt >0)
        {
            temp = p[k].rbt = temp + p[k].rbt;
            p[k].rbt = 0;
            p[k].ct = temp;
        }
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
        p[i].rbt = p[i].bt;
    }

    completion_time(p,n);
    turn_around_time(p,n);
    avg_waiting_time(p,n);
    printf("\n Process No.    Arrival Time    Burst Time    Completion Time    Turn Around Time    Waiting Time\n");
    for(i=0; i<n; i++ )
        printf("\n\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    return 0;
}
