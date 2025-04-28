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
