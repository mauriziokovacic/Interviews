# Server grid

There is a non-empty 2D grid of servers that needs to be updated, and the team would like to know the minimum number of days needed for every server to be up to date.

A server needing to be updated is marked with a 0, while an up to date one is marked with a 1.

If a server is updated, it can pass in one day the update to its above, below, left, and right neighbors.

Write a function that given a servers grid, returns the minimum number of days for it to be up to date. If the update it is not possible, return -1.


> Example:\
\
    Server grid:\
        0 0 1 0 0\
        0 0 0 1 0\
        1 0 0 0 0\
\
    After 1 day\
        0 1 1 1 0\
        1 0 1 1 1\
        1 1 0 1 0\
\
    After 2 days\
        1 1 1 1 1\
        1 1 1 1 1\
        1 1 1 1 1\
\
    Answer is 2
