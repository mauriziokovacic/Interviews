#include <algorithm>
#include <type_traits>
#include <utility>
#include <vector>


// Naive count
std::size_t count(std::uint32_t data)
{
	constexpr std::size_t shifts = sizeof(std::uint32_t) * 8 - 1;
	constexpr std::uint32_t mask = 0x3;
	std::size_t n = 0;
	for (std::size_t i = 0; i < shifts; ++i)
	{
		n += ((data >> i) & mask) == mask;
	}
	return n;
}


// 1. Can you generalize the function such that it can receive any integral data?
// 2. Can you spot any issue with this implementation?
// Any non-integral type will fail to compile. Depending on the platform, shifting a signed integral will propagate the sign bit.
template <typename T>
std::size_t count(T data)
{
	constexpr std::size_t shifts = sizeof(T) * 8 - 1;
	constexpr T mask = 0x3;
	std::size_t n = 0;
	for (std::size_t i = 0; i < shifts; ++i)
	{
		n += ((data >> i) & mask) == mask;
	}
	return n;
}


// 3. Can you change the function such that it won't be compiled unless an unsigned integral is passed as input?
template <typename T,
	typename std::enable_if<std::is_integral<T>::value&& std::is_unsigned<T>::value, bool>::type = true>
std::size_t count(T data)
{
	constexpr std::size_t shifts = sizeof(T) * 8 - 1;
	constexpr T mask = 0x3;
	std::size_t n = 0;
	for (std::size_t i = 0; i < shifts; ++i)
	{
		n += ((data >> i) & mask) == mask;
	}
	return n;
}


// 4. Ascending order by the number of 1s pairs
void count_sort(std::vector<uint32_t>& data)
{
	struct
	{
		bool operator()(uint32_t a, uint32_t b) const
		{
			return count(a) < count(b);
		}
	} compare;

	std::sort(data.begin(), data.end(), compare);
}


// 5. Ascending order by the number of 1s pairs, natural ascending order in case of equal count
void count_sort_natural(std::vector<uint32_t>& data)
{
	struct
	{
		bool operator()(uint32_t a, uint32_t b) const
		{
			std::size_t ca = count(a);
			std::size_t cb = count(b);

			if (ca < cb)
			{
				return true;
			}

			if (ca == cb)
			{
				return a < b;
			}

			return false;
		}
	} compare;

	std::sort(data.begin(), data.end(), compare);
}
