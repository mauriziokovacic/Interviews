#include <string>


void string_split(const std::string& input, std::string& outPairs, std::string& outRemainder)
{
	static constexpr char offset = '0';

	outPairs = "";
	outRemainder = "";

	int digits[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < input.length(); ++i)
	{
		const char digit = input[i];
		const int index = digit - offset;
		++digits[index];
	}

	for (char i = 0; i < 5; ++i)
	{
		if (digits[i] == 0)
		{
			continue;
		}

		const char j = 9 - i;

		if (digits[j] == 0)
		{
			outRemainder += std::string(digits[i], i + offset);
		}
		else
		{
			const string pair = std::string(1, i + offset) + std::string(1, j + offset);
			const int count = std::min(digits[i], digits[j]);
			for (int k = 0; k < count; ++k)
			{
				outPairs += pair;
			}
			digits[i] -= count;
			if (digits[i] > 0)
			{
				outRemainder += std::string(digits[i], i + offset);
			}
			digits[j] -= count;
		}
		digits[i] = 0;
	}

	for (char i = 5; i < 10; ++i)
	{
		if (digits[i] != 0)
		{
			outRemainder += std::string(digits[i], i + offset);
		}
	}
}
