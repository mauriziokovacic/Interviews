# Points extraction

Write a function:

    vector<Vec3> extract_points(const vector<Vec3>& points)

that given a list of points, returns a list of all the points such that:
    `p.z > 0`

Follow up:
- Can you achieve the same result by using some STL function? If yes, modify you code.

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
