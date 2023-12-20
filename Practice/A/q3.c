#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void main()
{
    int n;
    scanf("%d", &n);

    #pragma omp schedule(static, 2) 
    {
        for(int i = 0; i < n; i++)
        {
            printf("Thread Number %d- Iteration Number %d", omp_get_thread_num(), i);
        }
    }
}