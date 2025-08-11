# Alternating slices

An array A consisting of N integers is given. A pair of integers (P, Q), such that 0 $\le$ P $\le$ Q < N, is called a slice of array A. A slice is called _alternating_ if the signs of its consecutive elements alternate. More precisely, slice (P, Q) is alternating if:
  - `A[P]` $\ge$ 0, `A[P+1]` $\le$, `A[P+2]` $\ge$ 0 
  - `A[P]` $\le$ 0, `A[P+1]` $\ge$ 0, `A[P+2]` $\le$ 0

and so on, up to `A[Q]`.

Note that 0 is treated as both positive and negative.

Write a function:

    int solution(std::vector<int>& A)
    {
        // ...
    }

that, given an array A consisting of N integers, returns the size of the largest alternating slice in A.
For example, given array A such that:
```
    A[0]  =  5
    A[1]  =  4
    A[2]  = -3
    A[3]  =  2
    A[4]  =  0
    A[5]  =  1
    A[6]  = -1
    A[7]  =  0
    A[8]  =  2
    A[9]  = -3
    A[10] =  4
    A[11] = -5
```
the function should return 7, because:
  - (1, 7) is an alternating slice of length 7,
  - (7,11) is an alternating slice of length 5, and
  - all other alternating slices in A are shorter.

Given array A such that:
```
    A[0] = 1
    A[1] = 2
    A[2] = 3
```
the function should return 1, because there are three alternating slices (0, 0), (1, 1) and (2, 2) and all of them are of length 1.

## Constraints
Write an efficient algorithm for the following assumptions:
- N is an integer within the range [1,100000];
- each element of array A is an integer within the range [-1000000000,1000000000].
