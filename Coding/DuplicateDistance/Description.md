# Distance between duplicates

You are given an implementation of a function:

    int solution(std::vector<int>& A);

which accepts as input a non-empty zero-indexed array A consisting of N integers. It returns the maximum distance between the first and last occurrence of an entry.

The function works slowly on large input data and the goal is to optimize it so as to achieve better time and/or space complexity. The optimized function should return the same result as the given implementation for every input that satisfies the assumptions.

For example, given array A such that:
```
    A[0] = 4
    A[1] = 6
    A[2] = 2
    A[3] = 2
    A[4] = 6
    A[5] = 6
    A[6] = 1
```
the function returns 4, because the first occurence of 6 is at index 1, its last occurence at index 5.

Also, for given array A such that:
```
    A[0] = 2
    A[1] = 2
    ...
    A[49999] = 2
    A[50000] = 2
```
in other words, `A[K] = 2` for each K (0 <= K <= 50000), the given implementation works too slow, but the function would return 50000.

Write an efficient algorithm for the following assumptions:
    - N is an integer within the range [1,100000];
    - each element of array A is an integer within the range [1,N].

The original code is:

```
#include <algortihm>
#include <vector>

int solution(std::vector<int>& A) {
    int N = A.size();
    int result = 0;
    for(int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if(A[i] == A[j])
                result = std::max(result, std::abs(i-j));
    return result;
}
```
