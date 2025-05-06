#include <cstring>


struct DataEntry
{
	char name[32];
	int value;
	DataEntry* next;
};


// Helper function to split the list into two halves
void splitList(DataEntry* source, DataEntry** front, DataEntry** back)
{
	DataEntry* slow = source;
	DataEntry* fast = source->next;

	// Advance 'fast' two nodes, and 'slow' one node
	while (fast != nullptr)
	{
		fast = fast->next;
		if (fast != nullptr)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	// 'slow' is before the midpoint in the list
	*front = source;
	*back = slow->next;
	slow->next = nullptr;
}


// Helper function to merge two sorted lists
DataEntry* mergeLists(DataEntry* a, DataEntry* b)
{
	if (a == nullptr)
	{
		return b;
	}

	if (b == nullptr)
	{
		return a;
	}

	DataEntry* result = nullptr;

	// Compare by name first, then by value
	int compare = strcmp(a->name, b->name);
	if (compare < 0 || (compare == 0 && a->value <= b->value))
	{
		result = a;
		result->next = mergeLists(a->next, b);
	}
	else
	{
		result = b;
		result->next = mergeLists(a, b->next);
	}

	return result;
}


// Main function to sort the list
void sortList(DataEntry* head)
{
	if (head == nullptr || head->next == nullptr) 
	{
		return;
	}

	DataEntry* a = nullptr;
	DataEntry* b = nullptr;

	// Split the list into two halves
	splitList(head, &a, &b);

	// Recursively sort the two halves
	sortList(a);
	sortList(b);

	// Merge the sorted halves
	head = mergeLists(a, b);
}
