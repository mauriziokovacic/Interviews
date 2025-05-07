#include <vector>
#include <queue>
#include <algorithm>
#include <climits>


using cost_t = std::vector<std::vector<int>>;

struct index_t
{
public:
	index_t(int i = -1, int j = -1)
		: i(i), j(j)
	{
	}


	void set(int i, int j)
	{
		this->i = i;
		this->j = j;
	}


	void reset()
	{
		set(-1, -1);
	}


	int distance(const index_t& other) const
	{
		return std::abs(i - other.i) + std::abs(j - other.j);
	}

	int i;
	int j;
};



void fetch_data(const std::vector<std::string>& data, index_t& charlie, index_t& home, std::vector<index_t>& food)
{
	charlie.reset();
	home.reset();
	food.clear();
	for (std::size_t i = 0; i < data.size(); ++i)
	{
		for (std::size_t j = 0; j < data[i].size(); ++j)
		{
			const char& cell = data[i][j];
			switch (cell)
			{
			case 'C':
				charlie.set(i, j);
				break;
			case 'H':
				home.set(i, j);
				break;
			case 'F':
				food.push_back(index_t(i, j));
				break;
			default: break;
			}
		}
	}
}


cost_t compute_costs(const index_t& charlie, const index_t& home, const std::vector<index_t>& food)
{
	const int n = food.size() + 2;
	cost_t costs(n, std::vector<int>(n, 0));

	for (std::size_t i = 0; i < food.size(); ++i)
	{
		costs[0][i + 1] = charlie.distance(food[i]);
		costs[i + 1][n - 1] = home.distance(food[i]);
	}

	for (std::size_t i = 1; i < food.size(); ++i)
	{
		std::size_t j = i - 1;
		int distance = food[i].distance(food[i - 1]);
		costs[i][j] = distance;
		costs[j][i] = distance;
	}

	return costs;
}


int tsp(const cost_t& costs)
{
	int n = costs.size();

	std::vector<int> nodes;
	nodes.reserve(n - 2);
	for (int i = 1; i < n - 1; ++i)
	{
		nodes.push_back(i);
	}

	int output = std::numeric_limits<int>::max();

	do
	{
		int cost = 0;
		int current = 0;

		for (std::size_t i = 0; i < nodes.size(); ++i)
		{
			cost += costs[current][nodes[i]];
			current = nodes[i];
		}

		cost += costs[current][n - 1];

		output = std::min(output, cost);

	} while (std::next_permutation(nodes.begin(), nodes.end()));

	return output;
}


int CharlietheDog(const std::vector<std::string>& strArr)
{
	index_t charlie, home;
	std::vector<index_t> food;

	fetch_data(strArr, charlie, home, food);

	if (food.empty())
	{
		return charlie.distance(home);
	}

	return tsp(compute_costs(charlie, home, food));
}
