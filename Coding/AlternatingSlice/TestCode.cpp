/*

An array A consisting of N integers is given. A pair of integers (P, Q), such that
0 <= P <= Q < N, is called a slice of array A. A slice is called 'alternating' if the
signs of its consecutive elements alternate. More precisely, slice (P, Q) is
alternating if:
    - A[P] >= 0, A[P+1] <= 0, A[P+2] >= 0, and so on, up to A[Q], or
    - A[P] <= 0, A[P+1] >= 0, A[P+2] <= 0, and so on, up to A[Q].

Note that 0 is treated as both positive and negative.

Write a function:

    int solution(std::vector<int>& A);

that, given an array A consisting of N integers, returns the size of the largest
alternating slice in A.

For example, given array A such that:
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
the function should return 7, because:
    - (1, 7) is an alternating slice of length 7,
    - (7,11) is an alternating slice of length 5, and
    - all other alternating slices in A are shorter.

Given array A such that:
    A[0] = 1
    A[1] = 2
    A[2] = 3
the function should return 1, because there are three alternating slices (0, 0),
(1, 1) and (2, 2) and all of them are of length 1.

Write an efficient algorithm for the following assumptions:
    - N is an integer within the range [1,100000];
    - each element of array A is an integer within the range [-1000000000,1000000000].

*/



#include <algorithm>
#include <vector>

// Typedef for readability
using uint = std::size_t;

int solution(std::vector<int>& A)
{
    // const is a bit more efficient than a non const
    const uint N = A.size();

    // length of the longest sequence encountered
    int l = 1; /// last element leads to a sequence of 1, so 1 is the minimum

    // counter for the current sequence length
    int c = 1; /// last element leads to a sequence of 1, so 1 is the minimum

    // if there are more than one integer
    if (N > 1)
    {
        // if the last pair is alternating
        if (A[N - 2] * A[N - 1] <= 0)
        {
            // increment c and update the longest sequence
            l = ++c;
        }
    }

    // iterate the vector in reverse
    for (uint i = N - 3; i < N; --i)
    {
        // analyze the triples (i,j,k)
        const uint j = i + 1;
        const uint k = i + 2;

        // check if the first and second numbers of the triplet have alternate signs
        const bool cond_1 = A[i] * A[j] <= 0;

        // check if the first and third numbers of the triplet have same signs
        const bool cond_2 = A[i] * A[k] >= 0;

        // if both conditions are true
        if (cond_1 && cond_2)
        {
            // increment c and update the longest sequence
            l = std::max(++c, l);
        }
        else
        {
            // otherwise reset the current counter to 1,
            // adding a 1 if the first condition is true
            c = 1 + cond_1;
        }
    }

    // return the correct result
    return l;
}