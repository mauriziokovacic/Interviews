#include <array>
#include <vector>
#include <cmath>

using namespace std;

// Point in 3D space, defined as 3 floats
using Vec3 = array<float, 3>;

// Triangle defined as 3 indices, referring to 3D points
using Tri  = array<size_t, 3>;


float dot(const Vec3& a, const Vec3& b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}


float length(const Vec3& a)
{
	return sqrt(dot(a, a));
}


void normalize(Vec3& a)
{
	float len = length(a);
	if (len > 0.0f)
	{
		a[0] /= len;
		a[1] /= len;
		a[2] /= len;
	}
	return len;
}


Vec3 cross(const Vec3& a, const Vec3& b)
{
    return Vec3() { a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0] };
}


float angle(const Vec3& a, const Vec3& b)
{
    return std::acos(dot(a, b));
}


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

	inline Vec3 face_normal(const size_t i) const
	{
		Vec3 p0 = point(m_face[i][0]);
		Vec3 p1 = point(m_face[i][1]);
		Vec3 p2 = point(m_face[i][2]);
        Vec3 e0 = { p1[0] - p0[0], p1[1] - p0[1], p1[2] - p0[2] };
        Vec3 e1 = { p2[0] - p0[0], p2[1] - p0[1], p2[2] - p0[2] };
        Vec3 n = cross(e0, e1);
        normalize(n);
		return n;
	}

    /// Returns the faces adjacent to face i
    vector<size_t> adjacent(const size_t i) const
    {
        return vector<size_t>();
    }

protected:
    vector<Vec3> m_point;   // points list
    vector<Vec3> m_normal;  // point normals list
    vector<Tri>  m_face;    // faces list
};


vector<size_t> flat_region(const Model& M, const size_t f0, const float threshold)
{
    std::vector<size_t> result = { f0 };
	std::map<size_t, bool> visited;
	std::stack<size_t> stack;
	
    const Vec3 n0 = M.face_normal(f0);
    visited[f0] = true;
    for (const auto& fi : M.adjacent(f0))
    {
        stack.push(fi);
    }
    
    while (!stack.empty())
    {
		const size_t fi = stack.top();
		stack.pop();
        
        if (visited[fi])
        {
            continue;
        }

		visited[fi] = true;

        const Vec3 ni = M.face_normal(fi);
        if (angle(n0, ni) < threshold)
        {
            result.push_back(fi);
        }

		for (const auto& fj : M.adjacent(fi))
		{
			stack.push(fj);
		}
    }

    return result;
}
