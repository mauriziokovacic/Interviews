#include <vector>

using color_t = unsigned int;


struct Vec3 
{
	Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
		: x(x), y(y), z(z)
	{ }


	float distance(const Vec3& other) const
	{
		return ((x - other.x) * (x - other.x) +
			(y - other.y) * (y - other.y) +
			(z - other.z) * (z - other.z));
	}


	float x, y, z;
};


struct Point
{
	Point(Vec3 p = Vec3(), color_t c = 0xFFFFFFFF)
		: position(p), color(c)
	{ }

	Vec3 position;
	color_t color;
};



class PointCloud
{
public:
	// ... other methods ...

	std::size_t FindClosestPoint(const Vec3& P) const
	{
		std::size_t output = std::numeric_limits<std::size_t>::max();

		float minDistance = std::numeric_limits<float>::max();
		for (std::size_t i = 0; i < points.size(); ++i)
		{
			const float d = points[i].position.distance(P);
			if (d < minDistance)
			{
				minDistance = d;
				output = i;
			}
		}

		return output;
	}


	PointCloud transform(const std::function<Point(const Point&)>& t) const
	{
		PointCloud transformed;

		transformed.points.reserve(points.size());
		for (std::size_t i = 0; i < size(); ++i)
		{
			transformed.points.push_back(t(points[i]));
		}

		return transformed;
	}

protected:
	std::vector<Point> points;
};
