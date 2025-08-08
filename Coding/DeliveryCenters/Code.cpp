#include <vector>
#include <limits>
#include <queue>


struct Cell
{
	int i;
	int j;
	int value;
};


void preProcessData(std::vector<std::vector<int>>& inGrid, std::queue<Cell>& outQueue)
{
	for (int i = 0; i < inGrid.size(); ++i)
	{
		for (int j = 0; j < inGrid[i].size(); ++j)
		{
			if (inGrid[i][j])
			{
				outQueue.push({i, j, 0});
			}
			inGrid[i][j] = std::numeric_limits<int>::max();
		}
	}
}


void processData(std::vector<std::vector<int>>& inGrid, std::queue<Cell>& inQueue)
{
	const int rows = inGrid.size();
	const int cols = inGrid[0].size();

	while (!inQueue.empty())
	{
		Cell current = inQueue.front();
		inQueue.pop();

		const int i = current.i;
		const int j = current.j;
		const int value = current.value;

		if ((i < 0) || (i >= rows) || (j < 0) || (j >= cols))
		{
			continue;
		}

		if (inGrid[i][j] <= value)
		{
			continue;
		}

		inGrid[i][j] = value;

		const int nextValue = value + 1;
		inQueue.push({ i + 1, j + 1, nextValue });
		inQueue.push({ i + 1, j    , nextValue });
		inQueue.push({ i + 1, j - 1, nextValue });
		inQueue.push({ i    , j + 1, nextValue });
		inQueue.push({ i    , j - 1, nextValue });
		inQueue.push({ i - 1, j + 1, nextValue });
		inQueue.push({ i - 1, j    , nextValue });
		inQueue.push({ i - 1, j - 1, nextValue });
	}	
}


Cell findMaxValue(const std::vector<std::vector<int>>& grid)
{
	Cell output = { -1, -1, std::numeric_limits<int>::min() };
	for (int i = 0; i < inGrid.size(); ++i)
	{
		for (int j = 0; j < inGrid[i].size(); ++j)
		{
			if (inGrid[i][j] > output.value)
			{
				output.i = i;
				output.j = j;
				output.value = inGrid[i][j];
			}
		}
	}
	return output;
}



int getMinInconvenience(std::vector<std::vector<int>> grid)
{
	Cell maxCell;
	std::queue<Cell> queue;
	
	preProcessData(grid, queue);

	if (queue.empty())
	{
		const int rows = inGrid.size();
		const int cols = inGrid[0].size();
		maxCell = { rows / 2, cols / 2, 0 };
	}
	else
	{
		processData(grid, queue);
		maxCell = findMaxValue(grid);
		queue = std::queue<Cell>();
		maxCell.value = 0;
	}

	queue.push(maxCell);
	processData(grid, queue);
	maxCell = findMaxValue(grid);

	return maxCell.value;
}
