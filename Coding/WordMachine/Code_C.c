#include <stdlib.h>
#include <string.h>


#pragma region Stack

// Create a stack type
struct stack_t
{
    int top;      /// Current top index, -1 when the stack is empty
    int capacity; /// Max number of elements in the stack
    int* data;    /// Pointer to the stack data
};

// Alias its name in a C fashion
typedef struct stack_t stack_t;


// Given the max number of elements, create a stack
stack_t* create_stack(int capacity) 
{
    stack_t* stack  = (stack_t*) malloc(sizeof(stack_t));
    stack->top      = -1;
    stack->capacity = capacity;
    stack->data     = (int*) malloc(capacity * sizeof(int));
    return stack;
}


// Delete the stack allocated memory
void delete_stack(stack_t* stack) 
{
    free(stack->data);
    free(stack);
}


// Return the current stack size
int size(stack_t* stack)
{
    return stack->top+1;
}


// Return 1 if the stack is empty, 0 otherwise
int empty(stack_t* stack)
{
    return size(stack) == 0;
}


// Return 1 if the stack reached its capacity, 0 otherwise
int full(stack_t* stack)
{
    return size(stack) == stack->capacity;
}


// Return the element pointed by top index, -1 if the stack is empty
int top(stack_t* stack)
{
    if(empty(stack)) return -1;
    return stack->data[stack->top];
}

#pragma endregion


#pragma region Command

// Create a command type, useful to read the input string
struct command_t
{
    int index;   /// current character of the string
    char* data;  /// input string
    char* token; /// current/last token read
};

// Alias its name in a C fashion
typedef struct command_t command_t;


// Create a new command from a given string
command_t* create_command(char* S)
{
    command_t* command = (command_t*) malloc(sizeof(command_t));
    command->index = 0;
    command->data  = S;
    command->token = NULL;
}


// Delete the command allocated memory
void delete_command(command_t* command)
{
    free(command->token);
    free(command);
}


// Return the pointer to the current character
char* current(command_t* command)
{
    return &command->data[command->index];
}


// Return 1 if the string ending character has been reached, 0 otherwise
int end(command_t* command)
{
    return *current(command) == '\0';
}


// Return 1 if the delimiter character (' ') has been reached, 0 otherwise
int delimiter(command_t* command)
{
    return *current(command) == ' ';
}


// Read a token of n characters from the input string
void fetch_token(command_t* command, int n)
{
    if (command->token != NULL)
    {
        free(command->token);
    }
    command->token = (char*) malloc(n * sizeof(char));
    memcpy(command->token, &command->data[command->index], n);
}


// Read an operation from the input string
int read_operation(command_t* command)
{
    if (end(command))
    {
        return 0;
    }
    if (delimiter(command))
    {
        ++command->index;
    }
    int n = strcspn(current(command), " ") - command->index;
    fetch_token(command, n);
    return 1;
}


// Return -1 if underflow or overflow occurred, otherwise return the given number
int numeric_error(int num)
{
	const unsigned int mask = 0xFFF00000;
	return mask & num ? -1 : num;
}


// Push the given number in the stack and return it. If the stack is full return -1
int push(stack_t* stack, int num)
{
    if (full(stack))
    {
        return -1;
    }
	++stack->top;
	stack->data[stack->top] = num;
	return num;
}


// Take out the top element of the stack and return it. If the stack is empty return -1
int pop(stack_t* stack)
{
    if (empty(stack))
    {
        return -1;
    }
	int num = top(stack);
	--stack->top;
	return num;
}


// Duplicate the top element and return it. If the stack is empty return -1
int dup(stack_t* stack)
{
    if (empty(stack))
    {
        return -1;
    }
	int num = top(stack);
	return push(stack, num);
}


// Add the top two elements together and push the result in the stack.
// Return -1 if there are less than 2 elements in the stack
int plus(stack_t* stack)
{
    if (size(stack) <= 1)
    {
        return -1;
    }
	int a = pop(stack);
	int b = pop(stack);
	int c = numeric_error(a + b);
	return c < 0 ? -1 : push(stack, c);
}


// Subtract the top two elements together and push the result in the stack.
// Return -1 if there are less than 2 elements in the stack
int minus(stack_t* stack)
{
    if (size(stack) <= 1)
    {
        return -1;
    }
	int a = pop(stack);
	int b = pop(stack);
	int c = numeric_error(a - b);
	return c < 0 ? -1 : push(stack, c);
}


// Execute the current operation on the stack
// Since all operations start with a different character, we can just check the first one
// If something bad happened, return -1
int execute(command_t* command, stack_t* stack)
{
    int out = -1;
    if (command->token != NULL)
    {
        switch (command->token[0])
        {
		    case 'P':
		    {
			    out = pop(stack);
		    } break;

		    case 'D':
		    {
			    out = dup(stack);
		    } break;

		    case '+':
		    {
			    out = plus(stack);
		    } break;

		    case '-':
		    {
			    out = minus(stack);
		    } break;

		    case ' ': break;

		    case '\0': break;

		    default:
		    {
			    out = push(stack, atoi(command->token));
		    } break;
        }
    }
    return out;
}

#pragma endregion


#pragma region Algorithm

// Delete the command and stack allocated memory
void delete_data(command_t* command, stack_t* stack) 
{
    delete_stack(stack);
    delete_command(command);
}


int solution(char *S)
{
    // Create the command from S
    command_t* command = create_command(S);

    // Create a stack with a capacity of 2000
    stack_t* stack = create_stack(2000);

    // Error handler
    int out;

    // While we don't reach the final character
    while(!end(command))
    {
        // Read the operation. If it fails (returns 0), then we delete the allocated memory and return -1
        if(!read_operation(command))
        {
            delete_data(command, stack);
            return -1;
        }

        // Execute the command on the stack.
        out = execute(command, stack);

        // If an error has occurred (out=-1), then delete the allocated memory and return -1
        if(out == -1)
        {
            delete_data(command, stack);
            return -1;
        }
    }

    // Read the top element of the stack
    out = top(stack);

    // Delete the allocated memory
    delete_data(command, stack);

    // Return the result
    return out;
}

#pragma endregion