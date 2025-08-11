#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>


std::vector<std::string> processLogs(const std::vector<std::string>& logs, int threshold)
{
	std::vector<std::string> result;

	std::map<std::string, int> count;
	for (size_t i = 0; i < logs.size(); ++i)
	{
		const std::string& log = logs[i];
		std::stringstream stream(log);

		std::string sender;
		std::string recipient;

		log >> sender >> recipient;

		++count[sender];
		if (sender.compare(recipient) != 0)
		{
			++count[recipient];
		}
	}

	for (const auto& entry : count)
	{
		if (entry.second >= threshold)
		{
			result.push_back(entry.first);
		}
	}

	return result;
}
