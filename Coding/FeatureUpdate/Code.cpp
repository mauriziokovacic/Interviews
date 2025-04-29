#include <vector>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <sstream>

// Aliases
using uint    = std::size_t;
using word_t  = std::set<std::string>;
using map_t   = std::map<std::string, uint>;


// Function for the less operator for comparing <int, string> pairs, where
// 'first' is the count of the feature, 'second' is the feature name.
struct compare
{
    map_t* m_map;

    compare(map_t& map)
        : m_map(&map)
    { }

    bool operator()(const std::string& a, const std::string& b) const
    {
        if (m_map->at(a) > m_map->at(b))
        {
            return true;
        }
        if (m_map->at(a) == m_map->at(b))
        {
            return a < b;
        }
        return false;
    }
};


// Convert a string to lower case
std::string to_lower(const std::string& str)
{
    std::locale loc;
    std::string res = str;
    for (auto& c : res)
    {
        c = std::tolower(c, loc);
    }
    return res;
}


// Given a string, extract all the unique words in it, in lower case.
word_t tokenize(const std::string& str)
{
    word_t word;
    std::stringstream ss(str);
    std::string tk;
    while (!ss.eof())
    {
        ss >> tk;
        word.insert(to_lower(tk));
    }
    return word;
}


// For a given vector of features, initialize a map with the counts to 0
map_t initialize_feature(const std::vector<std::string>& feature)
{
    map_t res;
    for (const auto& f : feature)
    {
        res[f] = 0;
    }
    return res;
}


// For a give request, iterates of its unique words and count the
// features occurrences in place
void count(map_t& feature, const std::string& request)
{
    const std::set<std::string> word = tokenize(request);
    for (const auto& w : word)
    {
        auto it = feature.find(w);
        if (it != feature.end())
        {
            it->second += 1;
        }
    }
}


// For a set of requests, iterates of its unique words and count the
// features occurrences in place
void count(map_t& feature, const std::vector<std::string>& request)
{
    for (const auto& str : request)
    {
        count(feature, str);
    }
}



std::vector<std::string> most_wanted_features(const uint N, const std::vector<std::string>& possibleFeature, const std::vector<std::string>& requestedFeature)
{
    // Initialize map
    map_t feature = initialize_feature(possibleFeature);

    // Populate map
    count(feature, requestedFeature);

    // Finalize
	std::vector<std::string> result = possibleFeature;
	std::sort(result.begin(), result.end(), compare(feature));
	result.resize(std::min(N, result.size()));
    
    return result;
}

