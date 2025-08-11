# Count bits pairs

Write a function:
```
size_t count(uint32_t data)
```
that counts the pairs of 1s set in the input data.

## Example
```
010101 -> 0
101100 -> 1
110011 -> 2
110111 -> 3
```

## Follow up
1. Can you generalize the function such that it can receive any integral data?
2. Can you spot any issue with this implementation?
3. Can you change the function such that it won't be compiled unless an unsigned integral is passed as input?
4. Write a function:

        void count_sort(vector<uint32_t>& data)

    sorting the input data in ascending order by the number of 1s pairs present in each entry. _Use any suitable STL function_.

5. Modify the function such that, in case of an equal count of 1s pairs, the numbers are sorted in natural ascending order
> Ex.: given {6, 3}, the output should be {3, 6}, because both have just one pair of 1s). _Use any suitable STL function_.

