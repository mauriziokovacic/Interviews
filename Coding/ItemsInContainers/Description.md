# Items in Containers

A warehouse would like to know how much inventory exists in their closed inventory compartments.

Given a string `s` consisting of items represented as `*` and closed compartments as an open and close `|`, an array of starting indices `startIndices`, and an array of ending indices`endIndices`, determine the number of items in closed compartments within the substring between the two indices, inclusive.

Implement the function
```
std::vector<int> numberOfItems(const std::string& s, const std::vector<int>& startIndices, const std::vector<int>& endIndices)
```
returning an integer array containing the results for each of the `startIndices[i]` and `endIndices[i]` pairs.


## Constraints
- $1 \leq m$
- $n \leq 10^5$
- $1 \leq startIndices[i] \leq endIndices[i] \leq n$
- Each character of `s` is either `*` or `|`
- A compartment is represented as a pair of pipes that may or may not have items between them.


## Example 1
```
s = "|**|*|*"
startIndices = [1, 1]
endIndices = [5, 6]
```

### Expected output
`[2, 3]`

### Explanation
The string has a total of $2$ closed compartments, one with $2$ item ad one with $1$ item.

For the first pair of indices, $(1, 5)$, the substring is `"|**|*"`. There are $2$ items in a compartment.
For the second pair of indices, $(1, 6)$, the substring is `"|**|*|"` and there are $2 + 1 = 3$ items in compartments.


## Example 2
```
s = "*|*|"
startIndices = [1]
endIndices = [3]
```

### Expected output
`[0]`

### Explanation
The string has only closed compartments, with $1$ item.

For the pair of indices $(1, 3)$ though, the substring is `"*|*"`, which does not contain any closed compartments, so the output is $0$.


## Example 3
```
s = "*|*|*|"
startIndices = [1]
endIndices = [6]
```

### Expected output
`[2]`

### Explanation
The string has a total of $2$ closed compartments, both containing one item.

For the pair of indices $(1, 6)$, the substring is `"*|*|*|"`, which contains $2$ items in closed compartments.
