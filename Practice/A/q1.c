# include <stdio.h>
# include <omp.h>

void merge(int A[], int low, int mid, int high)
{
    int n1 = mid - low + 1, n2 = high - mid;

    int L[100], R[100];

    for(int i = 0; i < n1; i++)
        L[i] = A[i];
    for(int j = 0; j < n2; j++)
        R[j] = A[j];

    int i = 0, j = 0, k = low;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
            k++;
        }

        else
        {
            A[k] = R[j];
            j++;
            k++;
        }
    }
    
    while(i < n1)
    {
        A[k] = L[i];
        i++;
        k++;
    }

    while(j < n2)
    {
        A[k] = R[j];
        j++;
        k++;
    }
}

void merge_seq(int A[], int low, int high)
{
    if(low >= high)
        return;

    int mid = (low + high) / 2;
    merge_seq(A, low, mid);
    merge_seq(A, mid + 1, high);

    merge(A, low, mid, high);
}

void merge_parallel(int A[], int low, int high)
{
    int mid;

    if(low < high)
    {
        mid = (low + high) / 2;

        #pragma omp parallel sections 
        {
            #pragma omp section
            merge_parallel(A, low, mid);
            #pragma omp section
            merge_parallel(A, mid + 1, high);
        }

        merge(A, low, mid, high);
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    int A[100], copy[100];
    for(int i = 0; i < n; i++)
    {
        A[i] = rand()%1000;
        copy[i] = A[i];
    }

    double start, end;
    start = omp_get_wtime();
    merge_seq(A, 0, n);
    end = omp_get_wtime();

    for(int i = 0; i < n; i++)
    {
        printf("\nSorted array:");
        printf("%d", A[i]);
    }

    printf("Time taken : ", (end - start));

    for(int i = 0; i < n; i++)
        A[i] = copy[i];

    start = omp_get_wtime();
    merge_parallel(A, 0, n);
    end = omp_get_wtime();

    for(int i = 0; i < n; i++)
    {
        printf("%d", A[i]);
    }

    printf("Time taken : %lf", (end - start));

}