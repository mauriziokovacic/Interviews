#include <string>
#include <vector>


struct Cache
{
	std::vector<int> lPipes;
	std::vector<int> rPipes;
	std::vector<int> items;

	Cache(size_t n)
		: lPipes(n, -1), rPipes(n, -1), items(n + 1, 0)
	{ }

	Cache(const std::string& s)
		: Cache(s.size())
	{ }

	
	void initialize(const std::string& s)
	{
		const size_t n = s.size();
		initialize(s.size());

		int last = -1;
		for (size_t i = 0; i < n; ++i)
		{
			const size_t j = i + 1;

			lPipes[i] = last;
			items[j] = items[i];

			if (s[i] == '|')
			{
				last = i;
			}
			else
			{
				if (last != -1)
				{
					++items[j];
				}
			}
		}

		last = -1;
		for (int i = n - 1; i >= 0; --i)
		{
			rPipes[i] = last;
			if (s[i] == '|')
			{
				last = i;
			}
		}
	}
};


std::vector<int> numberOfItems(const std::string& s, const std::vector<int>& startIndices, const std::vector<int>& endIndices)
{
	const size_t n = s.size();
	const Cache cache(s);

	std::vector<int> result(startIndices.size(), 0);

	for (size_t i = 0; i < n; ++i)
	{
		const int start = startIndices[i] - 1;
		const int end = endIndices[i] - 1;

		const int l = cache.rPipes[start] == -1 ? start : cache.rPipes[start];
		const int r = cache.lPipes[end] == -1 ? end : cache.lPipes[end];

		if (l < r)
		{
			result[i] = cache.items[r + 1] - cache.items[l + 1];
		}
	}

	return result;
}
