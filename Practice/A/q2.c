#include <stdio.h>
#include <omp.h>
#define num_threads 8

static long num_steps = 1000000;

void main()
{
    double x, pi, sum[num_threads] = {0};

    double step = 1 / (double) num_steps;

    double start, end;
    start = omp_get_wtime();
    for(int i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum[0] += 4 / (1 + x * x);
    }
    end = omp_get_wtime();

    pi = sum[0] / step;
    printf("");

    //parallel
    int i, id = 0;

    start = omp_get_wtime();

    #pragma omp parallel private(i, x)
    {
        id = omp_get_thread_num();

        for(i = id, sum[id] = 0; i < num_steps; i += num_threads)
        {
            x = (i + 0.5) * step;
            sum[id] = 4 / (1 + x * x);
        }
    }

    end = omp_get_wtime();
    
    for(int i = 1; i < num_threads; i++)
        sum[0] += sum[i];

    pi = sum[0] / step;
}