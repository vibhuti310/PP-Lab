#include <stdio.h>
#include <omp.h>

int isPrime(int n)
{
    if(n < 2)
        return 1;
    
    for(int i = 2; i <= n/2; i++)
    {
        if(i % 2 == 0)
            return 1;
    }

    return 0;
}

int main()
{
    int n;
    scanf("%d", &n);

    //series
    for(int i = 1; i <= n; i++)
    {
        if(isPrime(i))
            printf("%d", i);
    }

    #pragma omp parallel for
    
}