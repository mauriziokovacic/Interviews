#include <vector>
#include <algorithm>


using namespace std;


struct Vec3
{
    float x, y, z;
};


vector<Vec3> extract_points(const vector<Vec3>& points)
{
	vector<Vec3> result;
	result.reserve(points.size());

	for (size_t i = 0; i < points.size(); ++i)
	{
		if (points[i].z > 0)
		{
			result.push_back(points[i]);
		}
	}
	result.shrink_to_fit();
	return result;
}


vector<Vec3> extract_points_STL(const vector<Vec3>& points)
{
	vector<Vec3> result;
	copy_if(points.begin(), points.end(), std::back_inserter(result), [&](const Vec3& p) { return p.z > 0.0f; });
	return result;
}
