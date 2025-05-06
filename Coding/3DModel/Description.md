# 3D Model

Suppose you are working with 3D models.

A simple model can be defined as a collection of points in space, a unit normal associated to each point, and a series of triangles.

The triangles form the surface of the model, and are defined as 3 indices, each one referring to a point in the model.

```
Example:
    Suppose you have four points:
        0: {0.0, 0.0 ,0.0}
        1: {1.0, 0.0 ,0.0}
        2: {0.0, 1.0 ,0.0}
        3: {0.0, 0.0 ,1.0}

    and a triangle:
        0: {0, 2, 3}

    This means you have a triangle in 3D space composed by point 0, point 2 and point 3
```

The model class contains the getters for points, normals and triangles, as well as a method to access the neighboring faces of a specified triangle.
Even though the implementation is not present, consider the method as if was perfectly working.

You have to introduce a new functionality in the code:

    vector<size_t> flat_region(const Model& M, const size_t f0, const float threshold)

Given a model M, and the index of an initial face f0, and a threshold, we want to be able to list the indices of all the triangles fi, reachable from f0, such that the angle between the normal of f0 and fi is less than a given threshold.

Feel free to add any functionality that could be needed for this task.


```
#include <array>
#include <vector>

using namespace std;

// Point in 3D space, defined as 3 floats
using Vec3 = array<float,3>;

// Triangle defined as 3 indices, referring to 3D points
using Tri  = array<size_t, 3>;


class Model
{
public:
    // ... some other interface ...

    /// Returns the i-th point in the model
    inline Vec3 point(const size_t i) const
    {
        return m_point[i];
    }

    /// Return the normal of the i-th point in the model
    inline Vec3 normal(const size_t i) const
    {
        return m_normal[i];
    }

    /// Return the i-th triangle in the model
    inline Tri face(const size_t i) const
    {
        return m_face[i];
    }

    /// Returns the faces adjacent to face i
    vector<size_t> adjacent(const size_t i) const
    {
        // ...
    }

protected:
    vector<Vec3> m_point;   // points list
    vector<Vec3> m_normal;  // point normals list
    vector<Tri>  m_face;    // faces list
};
```
