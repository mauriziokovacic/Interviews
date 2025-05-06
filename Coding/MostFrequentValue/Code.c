#include <stdlib.h>


int solution(int M, int A[], int N) {
    int *count = malloc((M + 1) * sizeof(int));
    int i;
    for (i = 0; i <= M; ++i)
    {
        count[i] = 0;
    }
    int maxOccurence = 0; // <- 
    int index = -1;
    for (i = 0; i < N; ++i)
    {
        if (count[A[i]] > 0) 
        {
            int tmp = count[A[i]] + 1; // <-
            if (tmp > maxOccurence)
            {
                maxOccurence = tmp;
                index = i;
            }
			count[A[i]] = tmp; // <-
        } 
        else
        {
            count[A[i]] = 1;
        }
    }
    return A[index == -1 ? i : index]; // <-
}
