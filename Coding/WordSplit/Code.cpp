#include <set>


std::string sub(const std::string& s, const std::size_t begin, const std::size_t end)
{
    return s.substr(begin, end-begin);
}


bool space_separated(const std::set<std::string>& wordDict, const std::string& s)
{
    const std::size_t n = s.length();
    std::vector<bool> can(n + 1, false);
    can[0] = true;
    for (std::size_t j = 1; j < (n + 1); ++j)
    {
        if (can[j])
        {
            continue;
        }
        for (std::size_t i = j - 1; i < j; --i)
        {
            const std::string str = sub(s, i, j);
            if (can[i])
            {
                if (wordDict.find(str) != wordDict.end())
                {
                    can[j] = true;
                }
            }
        }
    }
    return can[n];
}


std::vector<std::string> word_split(const std::set<std::string>& wordDict, const std::string& s)
{
    const std::size_t n = s.length();
    std::vector<bool> can(n + 1, false);
    can[0] = true;

    std::vector<std::string> split;
    split.reserve(n);

    for (std::size_t j = 1; j < (n + 1); ++j)
    {
        for (std::size_t i = j - 1; i < j; --i)
        {
            const std::string str = sub(s, i, j);
            if (can[i])
            {
                if (wordDict.find(str) != wordDict.end())
                {
                    can[j] = true;

                    split.push_back(str);
                }
            }
        }
    }
    if (can[n])
    {
        return split;
    }
    return std::vector<std::string>();
}
