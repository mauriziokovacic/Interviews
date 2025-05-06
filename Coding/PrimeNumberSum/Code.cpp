#include <cmath>


bool is_prime(int value)
{
	if (value <= 1)
	{
		return false;
	}

	if (value == 2)
	{
		return true;
	}

	if (value % 2 == 0)
	{
		return false;
	}

	for (int i = 3; i < std::sqrt(value); i += 2)
	{
		if (value % i == 0)
		{
			return false;
		}
	}
	return true;
}


int prime_sum(int begin, int end)
{
	int sum = 0;

	if (begin == 2)
	{
		sum = 2;
	}
	
	if (begin % 2 == 0)
	{
		++begin;
	}

	for (int i = begin; i < end + 1; i += 2)
	{
		sum += is_prime(i) ? i : 0;
	}
	return sum;
}
