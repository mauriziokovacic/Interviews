#include <algorithm>
#include <utility>
#include <stack>
#include <vector>
#include <array>

// Aliases
using grid_t = std::vector<bool>;
using index_t = int;
using stack_t = std::stack<index_t>;

using coord_t = std::pair<int, int>;
using next_t = std::array<coord_t, 4>;


// Checks if the server grid can actually be updated (if there is at least a server set to true)
bool can_update(const grid_t& server)
{
	return std::any_of(server.begin(), server.end(), [](bool item) { return item; });
}


// Initialize the stack
stack_t initialize(const grid_t& server, int rows, int cols)
{
	stack_t stack;
	for (index_t i = 0; i < rows * cols; ++i)
	{
		if (server[i])
		{
			stack.push(i);
		}
	}
	return stack;
}


// Update the server grid and return the number of days it took to update
int update_time(grid_t& server, int rows, int cols)
{
	static const next_t neigh = { coord_t(1, 0), coord_t(-1, 0), coord_t(0, 1), coord_t(0, -1) };

	int days = -1;
	if (can_update(server))
	{
		stack_t current = initialize(server, rows, cols);
		stack_t next;
		do
		{
			while (!current.empty())
			{
				const index_t index = current.top();
				current.pop();

				for (std::size_t n = 0; n < neigh.size(); ++n)
				{
					const int i = (index / cols) + neigh[n].first;
					const int j = (index % cols) + neigh[n].second;
					const int x = i * cols + j;

					if ((i < 0) || (j < 0) || (i >= rows) || (j >= cols))
					{
						continue;
					}

					if (server[x] == false)
					{
						next.push(x);
						server[x] = true;
					}
				}
			}
			std::swap(current, next);
			++days;
		} while (!current.empty());
	}
	return days;
}