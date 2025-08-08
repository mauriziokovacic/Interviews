#include <vector>
#include <limits>


long getStrength(const std::vector<std::vector<long>>& machine_powers)
{
	const size_t n = machine_powers.size();

	long global_min = std::numeric_limits<long>::max();
	long global_second_min = std::numeric_limits<long>::max();

	long strength = 0;

	for (size_t i = 0; i < n; ++i)
	{
		const size_t m = machine_powers[i].size();

		long local_min = std::numeric_limits<long>::max();
		long local_second_min = std::numeric_limits<long>::max();
		
		for (size_t j = 0; j < m; ++j)
		{
			const long unit = machine_powers[i][j];
			if (unit < local_min)
			{
				local_second_min = local_min;
				local_min = unit;
			}
			else
			{
				if (unit < local_second_min)
				{
					local_second_min = unit;
				}
			}
		}

		if (local_min < global_min)
		{
			global_min = local_min;
		}
		
		if (local_second_min < global_second_min)
		{
			global_second_min = local_second_min;
		}

		strength += local_second_min;
	}

	strength += global_min - global_second_min;
	return strength;
}
