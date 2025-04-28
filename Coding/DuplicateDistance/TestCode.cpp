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

    // create a map with key = A[i] and value = (i,j),
    // with i and j being the index of the first and last occurrence respectively
    map_t map;

    // iterate over the vector
    for (uint i = 0; i < N; ++i)
    {
        int key = A[i];
        int index = static_cast<int>(i);
        // if it is the first time I see A[i]
        // add the the pair (i,i) to the map
        // otherwise update the second index of the pair
        if (map.find(key) == map.end())
        {
            map[key] = value_t({index, index});
        }
        else
        {
            map[key][1] = index;
        }
    }

    // iterate of the map
    value_t result = 0;
    for (const auto& item : map)
    {
        // store the maximum element
        result = std::max(result, std::abs(item.second[1] - item.second[0]));
    }

    // Return the correct result
    return result;
}
