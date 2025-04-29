# Feature update

We have a set of possible features to update our system with. We would like to choose the N most wanted features from our customers requests.

A request is in the form of a spaces-separated sentence, like:
- 'I prefer foo rather than bar . FOo is THE BEST'
- 'in MY opinion FOO is overrated'

For each request all the features name must be extracted, and counted only once in case of repetitions.
For example:

> possible features = 'foo', 'bar'\
\
request = 'I prefer foo rather than bar . FOo is THE BEST'\
\
'foo': 1\
'bar': 1

The features must be returned from most wanted to least wanted. In case of a draw, alphabetical order should be used.

For example, if we are looking for the top 2 features in the following scenario:
>'d': 3\
'b': 5\
'a': 3

the function should return:
>'b', 'a'

Note:
- Features are unique lower case words.
- Requests are space-separated.



> Example:\
\
    top features     = 3\
    possible feature = 'alpha', 'beta', 'gamma', 'zeta'\
\
    requests:\
        'No alpha please'                               -> 'alpha'\
        'Beta is fantastic, but zeta is way better'     -> 'beta', 'zeta'\
        'GAMMA GAMMA GAMMA'                             -> 'gamma'\
        'If only zeta was good. Gamma was ok though'    -> 'zeta', 'gamma'\
        'ZEta is totally crap'                          -> 'zeta'\
\
    'alpha' : 1\
    'beta'  : 1\
    'gamma' : 2\
    'zeta'  : 3\
\
    result : 'zeta', 'gamma', 'alpha'
