#include <vector>

int CountHappyGroups(int BatchSize, const std::vector<int>& Groups)
{
	int count = 0;
	int r = 0;
	for (int n : Groups)
	{
		count += r == 0;
		r = ((r - n) % BatchSize + BatchSize) % BatchSize;
	}
	return count;
}