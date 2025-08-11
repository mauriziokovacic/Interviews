# Feature update

We have a set of possible features to update our system with. We would like to choose the $N$ most wanted features from our customers requests.

A request is in the form of a spaces-separated sentence, like:
- '_I prefer foo rather than bar . FOo is THE BEST_'
- '_in MY opinion FOO is overrated_'

For each request all the features name must be extracted, and counted only once in case of repetitions.
The features must be returned from most wanted to least wanted. In case of a draw, alphabetical order should be used.

Implement the function:
```
vector<string> most_wanted_features(const uint N, const vector<string>& possibleFeature, const vector<string>& requestedFeature)
```

Note:
- Features are unique lower case words.
- Requests are space-separated.


## Example 1
```
N = 2
possibleFeature = ["foo", "bar"]
requestedFeature = ["I prefer foo rather than bar . FOo is THE BEST"]
```

### Expected output
```
["foo", "bar"]
```

### Explanation
The feature "foo" is mentioned twice. "bar" is mentioned only once.

## Example 2
```
N = 2
possibleFeature = ["a", "b", "d"]
requestedFeature = ["a", "B", "b b", "d A", "d", "A D", "b b"]
```

### Expected output
```
["b", "a"]
```

### Explanation
If we are looking for the top 2 features in the following scenario:
```
'd': 3
'b': 5
'a': 3
```
the function should return:
```
["b", "a"]
```

## Example 3
```
N = 3
possibleFeature = ["alpha", "beta", "gamma", "zeta"]
requestedFeature = [
        "No alpha please",
        "Beta is fantastic, but zeta is way better",
        "GAMMA GAMMA GAMMA",
        "If only zeta was good. Gamma was ok though",
        "ZEta is totally crap"
]
```

### Expected output
```
["zeta", "gamma", "alpha"]
```

### Explanation
Counting the features present in the requests we have the following situation:
```
"alpha" : 1
"beta"  : 1
"gamma" : 2
"zeta"  : 3
```
Since `"alpha"` and `"beta"` have the same count, the first is going to be returned because of alphabetical order.
Hence the output will be `["zeta", "gamma", "alpha"]`
