# List sort

Given a single connected list, write the function to sort it.

Each entry is composed as follows:

```
struct DataEntry
{
	char name[32];
	int value;
	DataEntry* next;
}
```

The list must be sorted in alphabetical order. In case of equality, entries should be sorted by value. Assumes the input is always non null.
