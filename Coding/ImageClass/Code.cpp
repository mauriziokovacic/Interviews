#include <vector>

union color_t = unsigned int;


class Image
{
public:
	Image(std::size_t width, std::size_t height, color_t defaultValue = 0)
	{
		m_width = width;
		m_height = height;
		m_pixels = std::vector<color_t>(width * height, defaultValue);
	}


	inline std::size_t width() const
	{
		return m_width;
	}


	inline std::size_t height() const
	{
		return m_height;
	}


	inline color_t pixel(std::size_t index) const
	{
		return m_pixels[index];
	}


	inline color_t pixel(std::size_t i, std::size_t j) const
	{
		return pixel(i * m_width + j);
	}

	
	inline void set_pixel(std::size_t index, color_t value)
	{
		m_pixels[index] = value;
	}


	inline void set_pixel(std::size_t i, std::size_t j, color_t value)
	{
		set_pixel(i * m_width + j, value);
	}


	static Image resize(const Image& image, const float factor)
	{
		Image output(image.m_width * factor, image.m_height * factor);

		for (int i = 0; i < output.height(); ++i)
		{
			for (int j = 0; j < output.width(); ++j)
			{
				const int src_i = static_cast<int>(i / factor);
				const int src_j = static_cast<int>(j / factor);
				output.set_pixel(i, j, image.pixel(src_i, src_j));
			}
		}
	}

protected:
	std::vector<color_t> m_pixels;
	std::size_t m_width;
	std::size_t m_height;
};
