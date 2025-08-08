# Delivery Centers

A city is represented in the form of a grid where the delivery centers are marked as $1$ and all other places are marked as $0$.

Distance between two cells is defined as the maximum absolute distance between x-coordinates and y-coordinates.
For example, distance between $(1, 2)$ and $(0, 4)$ is $max(|1 - 0|, |2 - 4|) = 2$.
The inconvenience of the grid is defined as the maximum distance of any place marked 0 from its nearest delivery center.

We are planning to open a new delivery center to reduce the inconvenience of the grid.

Implement the function 
```
int getMinInconvenience(std::vector<std::vector<int>> grid)
````
which returns the minimum inconvenience of the grid by converting at most one $0$ (_any place_) to $1$ (_a delivery center_).


## Constraints
- $1 \leq n$
- $m \leq 500$
- $grid_ij \in \{0, 1\}$


## Example 1
Given $grid = [[0, 0, 0, 1], [0, 0, 0, 1]]$, the situation is as follows:
```
0 0 0 1
0 0 0 1
```

### Expected output
$1$

### Explanation
The distances to the nearest delivery centers for each cell are:
```
3 2 1 0
3 2 1 0
```
The initial inconvenience of the grid is $3$.

To optimize the inconvenience value, we could convert the cell at $(0,0)$ to a delivery center, resulting in:
```
1 0 0 1
0 0 0 1
```

Now the inconvenience has decreased to $1$, as shown in the matrix below:
```
0 1 1 0
1 1 1 0
```


## Example 2
Given $grid = [[0, 0, 0, 0], [0, 0, 0 ,0], [0, 0, 0, 0]]$, the situation is as follows:
```
0 0 0 0
0 0 0 0
0 0 0 0
```

### Expected output
$2$

### Explanation
Is is optimal to convert $(1,1)$ to $1$ resulting in
```
0 0 0 0
0 1 0 0 
0 0 0 0
```

where the distance of each cell from its nearest $1$ is
```
1 1 1 2
1 0 1 2
1 1 1 2
```

## Example 3
Given $grid = [[0]]$, the situation is as follows:
```
0
```

### Expected output
$0$

### Explanation

It is optimal to convert the only $0$ to $1$

