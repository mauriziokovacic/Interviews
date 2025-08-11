# List length

A non-empty array $A$ consisting of $N$ integers is given.

Array $A$ represents a linked list. A list is constructed from this array as follows:
- the first node (the head) is located at index $0$
- the value of a node located at index $K$ is `A[K]`
- if the value of a node is $-1$ then it is the last node of the list
- otherwise, the successor of a node located at index $K$ is located at index `A[K]` (you can assume that `A[K]` is a valid index, that is $0 < A[K] < N$)

Write a function:
```
int solution(int A[], int N)
```
that, given a non-empty array $A$ consisting of $N$ integers, returns the length of the list constructed from $A$.

Assume that:
- $N$ is an integer within the range $[1, 200000]$
- each element of array $A$ is an integer within the range $[-1, N-1]$
- it will always be possible to construct the list and its length will be finite.

In your solution, focus on correctness. The performance of your solution will not be the focus of the assessment.

## Example
```
A = [1, 4, -1, 3, 2]
```

### Expected output
$4$

### Explanation
The list is constructed as:
- the first node (_the head_) is located at index $0$ and has a value of $1$
- the second node is located at index $1$ and has a value of $4$
- the third node is located at index $4$ and has a value of $2$
- the fourth node is located at index $2$ and has a value of $-1$

The function should return $4$.
