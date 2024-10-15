#include <stdio.h>

#define MAX_FRAMES 50

int n, m, frames[MAX_FRAMES], pages[100], page_faults = 0;

void display()
{
    int i;
    printf("Frames: ");
    for (i = 0; i < m; i++)
        printf("%d ", frames[i]);
}

int find_optimal_page(int time[])
{
    int i, max = -1, optimal_page = 0;
    for (i = 0; i < m; i++)
    {
        if (time[frames[i]] > max)
        {
            max = time[frames[i]];
            optimal_page = i;
        }
    }
    return optimal_page;
}

int check_page_fault(int page)
{
    int i;
    for (i = 0; i < m; i++)
        if (frames[i] == page)
            return 1;
    return 0;
}

void demand_paging(int pages[], int n, int m)
{
    int time[100], i, j, optimal_page, flag;
    for (i = 0; i < n; i++)
    {
        flag = 0;
        if (!check_page_fault(pages[i]))
        {
            if (i < m)
                frames[i] = pages[i];
            else
            {
                for (j = 0; j < m; j++)
                    time[frames[j]] = 0;
                for (j = i + 1; j < n; j++)
                {
                    time[pages[j]]++;
                    if (time[pages[j]] > time[frames[optimal_page]])
                        optimal_page = find_optimal_page(time);
                }
                frames[optimal_page] = pages[i];
                page_faults++;
            }
            flag = 1;
        }
        display();
        if (flag)
            printf("\tPage Fault: %d", pages[i]);
        printf("\n");
    }
    printf("Total Page Faults: %d", page_faults);
}

int main()
{
    int i;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &m);
    demand_paging(pages, n, m);
    return 0;
}
