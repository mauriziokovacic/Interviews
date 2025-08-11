# Most Frequent Value

You are given an implementation of a function:
```
int solution(int M, int A[], int N)
```
that, given an integer $M$ and an array $A$ consisting of $N$ non-negative integers, which are not greater than $M$, returns the value (or one of the values) that occurs most often in this array.

The attached code is still **INCORRECT** for some inputs. Despite the error(s), the code may produce a correct answer for the example test cases. The goal of the exercise is to find and fix the bug(s) in the implementation. You can modify at most **FOUR** lines.

Assume that:
- $N$ is an integer within the range $[1, 200000]$
- $M$ is an integer within the range $[1, 10000]$
- each element of array $A$ is an integer within the range $[0, M]$

In your solution, focus on correctness. The performance of your solution will not be the focus of the assessment.

## Example
```
M = 3
A = [1, 2, 3, 3, 1, 3, 1]
N = 7
```

### Expected output
$1$ or $3$


## Initial code
```
#include <stdlib.h>

int solution(int M, int A[], int N) {
    int *count = malloc((M + 1) * sizeof(int));
    int i;
    for (i = 0; i <= M; ++i)
    {
        count[i] = 0;
    }
    int maxOccurence = 1;
    int index = -1;
    for (i = 0; i < N; ++i)
    {
        if (count[A[i]] > 0) 
        {
            int tmp = count[A[i]];
            if (tmp > maxOccurence)
            {
                maxOccurence = tmp;
                index = i;
            }
            count[A[i]] = tmp + 1;
        } 
        else
        {
            count[A[i]] = 1;
        }
    }
    return A[index];
}
```
