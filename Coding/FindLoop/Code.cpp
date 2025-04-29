struct Node
{
    Node* next = nullptr;
};


bool is_looping(Node* root)
{
    // Create two iterators for the linked list
    Node* slow = root;
    Node* fast = root;

    // While the end is not reached
    while (slow)
    {
        // Advance the slow of one step
        slow = slow->next;

        // Advance the fast of one step
        fast = fast->next;

        // If it is not null
        if (fast)
        {
            // Advance another step
            fast = fast->next;
        }
        else
        {
            // End has been reached
            return false;
        }

        // If the two iterators are the same, there is a loop
        if (slow == fast)
        {
            return true;
        }
    }
    return false;
}
