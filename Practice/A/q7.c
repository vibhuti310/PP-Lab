#include <stdio.h>
#include <omp.h>

int main()
{
    int n = 100, sum = 0;
    double start, end;

    start = omp_get_wtime();
    #pragma omp parallel for
    for(int i = 1; i <= n; i++)
    {
        #pragma omp critical
        sum += i;
    }
    end = omp_get_wtime();

    printf("Time: %d", end-start);
}