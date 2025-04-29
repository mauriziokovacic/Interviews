int solution(int A, int B)
{
	int n = 0;
	for (int C = A * B; C; C >>= 1)
	{
		n += C & 1;
	}
    return n;
}
