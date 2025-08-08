# Transaction service

Your team is responsible for maintaining a transaction service.
The transactions are provided as a string array where each entry represents a transaction to service.

Each transaction consists of:
- _sender_id_: Unique identifier for the user that initiated the transaction.
- _recipient_id_: Unique identifier for the user that is receiving the transaction.
- _amount_: The amount of the transaction.

The values are separated by a space. For example, `sender_id recipient_id amount`.

You have been tasked to implement the function
```
std::vector<std::string> processLogs(const std::vector<std::string>& logs, int threshold)
```
The function identifies the users that have a number of transactions over a given threshold, and returns list of user IDs ordered in ascending numeric value.


## Constraints
- $1 \leq n \leq 10^5$
- $1 \leq threshold \leq n$
- the _sender_id_, _recipiet_user_id_ and _amount_ contain only characters in the range ascii `['0'-'9']`
- the _sender_id_, _recipiet_user_id_ and _amount_ start with a non-zero digit.
- $0 < length of _sender_id_, _recipient_id_, _amount_ \leq 9$
- The result will contain at least on element.


## Example 1
```
["88 99 200", "88 99 300", "99 32 100", "12 12 15"]
threshold = 2
```

### Expected output
`["88", "99"]`

### Explanation
The transactions count for each user, regardless of role are:
```
ID	Transactions
--	------------
99	3
88	2
12	1
32	1
```

There are two users with at least $threshold = 2$ transactions: $99$ and $88$. In ascending order, the return array is `["88", "99"]`.

Note that in the last log entry, user $12$ was on both sides of the transaction. This counts as only $1$ transaction for user $12$.


## Example 2
```
logs = ["1 2 50", "1 7 70", "1 3 20", "2 2 17"]
threshold = 2
```

### Expected output
`["1", "2"]`

### Explanation
The transactions count for each user, regardless of role are:
```
ID	Transactions
--	------------
1	3
2	2
7	1
3	1
```

Only user $1$ and $2$ have at least $threshold = 2$ transactions.
The return array in numerically ascending order is `["1", "2"]`.
Note that in the last log entry, the user with ID $2$ performed both roles in the transaction.
This counted as one transaction for the user.
