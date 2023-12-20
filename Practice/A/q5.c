#include <stdio.h>
#include <omp.h>

int isPrime(int n)
{
    if(n < 2)
        return 0;

    for(int i = 2; i <= n/2; i++)
    {
        if(n % i == 0)
            return 0;
    }

    return 1;
}

int main()
{
    int n;
    double start, end;

    scanf("%d", &n);

    //serial
    start = omp_get_wtime();

    for(int i = 1; i <= n; i++)
    {
        if(isPrime(i))
            printf("%d", i);
    }

    end = omp_get_wtime();
    printf("Time: %d", (end - start));

    //parallel
    start = omp_get_wtime();

    #pragma omp parallel for
    for(int i = 1; i <= n; i++)
    {
        if(isPrime(i))
            printf("%d", i);
    }

    end = omp_get_wtime();
    printf("Time: %d", (end - start));
}