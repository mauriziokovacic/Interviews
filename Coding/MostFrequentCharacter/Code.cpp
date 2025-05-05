char MostUsedCharacter(const std::string& message)
{
	int max = 0;
	char result;

	char table[256];
	std::memset(table, 0, sizeof table);
	for (char c in message)
	{
		table[c] += 1;
		if (table[c] > max)
		{
			result = c;
			max = table[c];
		}
	}
	return result;
}