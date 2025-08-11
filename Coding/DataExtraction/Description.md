# Points extraction

Write a function:
```
std::vector<Vec3> extract_points(const std::vector<Vec3>& points)
```
that given a list of points, returns a list of all the points $P$ such that $P_Z > 0$.

## Follow up
Can you achieve the same result by using some STL function? If yes, modify you code.

## Initial code
```
#include <vector>

using namespace std;

struct Vec3
{
    float x, y, z;
};

vector<Vec3> extract_points(const vector<Vec3>& points)
{
    // ...
}

```
