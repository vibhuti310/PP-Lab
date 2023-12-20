#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int n;
    double start, end;
    scanf("%d", &n);

    int a[100], b[100], res[100];

    #pragma omp parallel for
    for(int i = 0; i < n; i++)
    {
        a[i] = rand()%1000;
        b[i] = rand()%1000;
    }

    start = omp_get_wtime();
    for(int i = 0; i < n; i++)
        res[i] = a[i] + b[i];

    end = omp_get_wtime();

    printf("Resultant vector : ");
    for(int i = 0; i < n; i++)
        printf("%d", res[i]);

    printf("Time taken : %d", (end - start));
}