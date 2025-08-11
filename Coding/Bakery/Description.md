# The bakery

A bakery bakes breads in batches of BatchSize. The customers will line up in groups of N people and wait to be served.
- If a group of people get only freshly baked bread, it will be a happy group.
- If a group is given leftovers from a previous bread batch, it will not be happy.
**NOTE**: A group will be happy even if the people receives bread from different consecutive batches

Given the BatchSize and the groups line, count how many happy groups there will be.
```
int CountHappyGroups(int BatchSize, const std::vector<int>& Groups)
{
	// TO DO
}
```

## Example 1
```
BatchSize = 3
Groups = { 2, 3, 1 }
```

### Expected output
$1$

### Explanation
The first group is composed of two people and everyone gets a freshly baked bread.
The second group is composed of three people, but it gets one bread from a previous batch and two freshly baked ones.
The third group is composed of one person and it gets one bread from a previous batch.
Only the first group will be happy.

## Example 2
```
BatchSize = 3
Group = 5
```
### Expected output
$1$

### Explanation
This will be a happy group.
