# Word split

Write a function:
```
bool space_separated(const std::set<std::string>& wordDict, const std::string& s)
```
that for a given dictionary `wordDict` containing a list of non-empty words, and a non-empty string `s`, determine if `s` can be segmented into a space-separated sequence of one or more dictionary words.

## Example 
```
wordDict = {"face", "book", "facebook"}
s = "macehook"
```

### Expected output
_false_

### Explanation
No correspondencies.

## Example 
```
wordDict = {"face", "book", "facebook"}
s = "facehook"
```

### Expected output
_false_

### Explanation
"face" is in the dictionary, but "hook" is not.


## Example 
```
wordDict = {"face", "book", "facebook"}
s = "facebook"
```

### Expected output
_true_

### Explanation
"face", "book" and "facebook" are in the dictionary.


## Initial code
```
#include <set>

using namespace std;

bool space_separated(const set<string>& wordDict, const string& s)
{
    // ...
}
```

## Follow up
Can you change the function such that it returns the list of dictionary words found?
