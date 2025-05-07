# Point cloud class

> Disclaimer:\
    _There is no right or wrong answer for this task_


You have to implement a simple class for a Point Cloud. A point cloud is nothing else than a container of 3D points.

You can assume you have a struct/class for the points and/or any suitable functionality over them, but you can write code if you want. Just don't waste too much time over it.


Follow up...
- Assume the needs have changed and now you need a color for each point. How would you modify the class and why?

- Implement a function:

        size_t FindClosestPoint(const Vec3& P) const

    that for a given point P, finds the closest points within the point cloud and returns its index.

- Implement a function that given a point cloud, return a new version of it, where each point is transformed by an unknown user-defined function.

- Where would you place this new function and why.
