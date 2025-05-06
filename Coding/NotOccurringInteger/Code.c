#include <stdlib.h>


int compare(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}


int solution(int A[], int N)
{
    qsort(A, N, sizeof(int), compare);
    int n = 1;
    int i;
    
    for (i = 0; i < N; ++i)
    {
        if (A[i] > 0)
        {
            break;
        }
    }

    for (; i < N; ++i)
    {
        if (A[i] > n)
        {
            break;
        }

        if (A[i] == n)
        {
            ++n;
        }
    }
    return n;
}
