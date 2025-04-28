#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>

// Typedef for readability
using uint = std::size_t;
using key_t = int;
using value_t = std::array<int, 2>;
using map_t = std::unordered_map<key_t, value_t>;


int solution(std::vector<int>& A)
{
    // const is a bit more efficient than a non const
    const uint N = A.size();

    int result = 0;

    // create a map with key = A[i] and value = (i,j),
    // with i and j being the index of the first and last occurrence respectively
    map_t map;

    // iterate over the vector
    for (uint i = 0; i < N; ++i)
    {

        // if it is the first time I see A[i]
        if (map.find(A[i]) == map.end())
        {
            // Add the the pair (i,i) to the map
            map[A[i]] = value_t({ static_cast<int>(i), static_cast<int>(i) });
        }
        else
        {
            // else update the second index of the pair
            map[A[i]][1] = static_cast<int>(i);
        }
    }

    // iterate of the map
    for (const auto& item : map)
    {
        // store the maximum element
        result = std::max(result, std::abs(item.second[1] - item.second[0]));
    }

    // Return the correct result
    return result;
}
