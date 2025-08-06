# FizzBuzz

Given a number `n`, for each integer `i` in the range from 1 to `n` inclusive, print one value per line as follows:
- if `i` is a multiple of both 3 and 5, print _FizzBuzz_.
- if `i` is a multiple of 3 (but not 5), print _Fizz_.
- if `i` is a multiple of 5 (but not 3), print _Buzz_.
- if `i` is not a multiple of 3 or 5, print the value of `i`

## Function Description

The function has the following signature
```
    void fizzBuzz(int n)
```

where `n` is the upper limit of values to test (inclusive).
The function must print the appropriate response for each value `i` in the set `{1, 2, ..., n}` in ascending order, each on a separate line.

## Constraints
$0 < n < 2\cdot 10^5$

## Example
Given `n = 15`, the function `fizzBuzz` should print:
```
1
2
Fizz
4
Buzz
Fizz
7
8
Fizz
Buzz
11
Fizz
13
14
FizzBuzz
```
