int solution(int A[], int N)
{
    // Index for the list
    int i = 0;

    // Length counter
    int n = 0;

    // While the index is not -1
    while (i >= 0)
    {
        // Read the new index
        i = A[i];

        // Increment the counter
        ++n;
    }

    // Return the counter
    return n;
}
