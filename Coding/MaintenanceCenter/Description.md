# Maintenance Center

In the maintenance center, there exist $n$ machines, each equipped with $m$ ($m \geq 2$) power units.
The power of the _j_-th power unit in the _i_-th machine is denoted as `machine_powers[i][j]`.
The strength of a machine is defined as the minimum power among all its power units.

We want to maximize the sum of strengths of all the machines.

For this, we can perform the following 3 step operation multiple times (possibly 0):
- Select a machine that has not yet been marked.
- Transfer any one power unit from the selected machine to **any** other machine.
- Mark the selected machine and it cannot be chosen for further operations. However, marked machines can still receive power units from other machines.

Implement the function 
```
long getStrength(const std::vector<std::vector<long>>& machine_powers)
```
that finds the maximum sum of strengths of all machines.

> Note:
- Each machine can transfer at most one power unit during the entire process, only when it is unmarked.
- A machine can receive power units from multiple other machines, even after it has been marked.
- The operation can be performed multiple times, but only unmarked machines can be selected during each operation.


## Constraints
- $1 \leq n \leq 2 \cdot 10^5$
- $2 \leq m \leq 2 \cdot 10^5$
- $1 \leq machine_powers[i][j] \leq 10^9$
- It is guaranteed that $m \cdot n \leq 2 \cdot 10^5$


## Example 1
$machine_powers = [[1, 5], [4, 3], [2, 10]]$

### Expected output
$16$

### Explanation
The operations can be performed as follows:
1. Select machine $1$ and transfer the unit with power $1$ to machine $2$. Now $machine_powers = [[5], [1, 4, 3], [2, 10]]$.
2. Select machine $3$ and transfer the unit with power $2$ to machine $2$. Now $machine_powers = [[5], [1, 2, 4, 3], [10]]$.

The sum of strengths is $min(5) + min(1, 2, 4, 3) + min(10) = 5 + 1 + 10 = 16$, which is the maximum possible.


## Example 2
$machine_powers = [[2, 7, 4], [2, 4, 3]]$

### Expected output
$6$

### Exaplaination
We can move the power unit with power $2$ from the first machine to the second machine.
Then the strength is $min(7, 4) + min(2, 4, 3, 2) = 6$, so the answer is $6$.


## Example 3
$machine_powers = [[2, 2, 2, 2], [2, 4, 3, 2], [2, 5, 3, 3]]$

### Output
$7$

### Exaplaination
We can move the power unit with power $2$ from the third machine to the second machine.
Then the strength is $min(2, 2, 2, 2) + min(2, 4, 3, 2, 2) + min(5, 3, 3) = 7$.

So the answer is $7$.


