#include <string>
#include <sstream>
#include <algorithm>
#include <stack>


// Utility function for overflow and underflow.
// Since we deal with 20-bit integers, the last 12 bits can
// be used to detect the numeric problems.
inline static int numeric_error(const int value)
{
	// build a mask for the last 12 bits.
	static constexpr int mask = static_cast<int>(0xFFF00000);

	// if any of the 12 bits is 1 then an error occurred.
	// if an error occurred return -1, otherwise the value
	return (mask & value) ? -1 : value;
}


int solution(std::string& S) {
    // create a stream from the input string
    std::stringstream stream(S);

    // create the stack
    std::stack<int> stack;

    // iterate the string until its end is reached
    while(!stream.eof())
    {
		if (stack.top() == -1)
		{
			break;
		}

        // create a token
        std::string token;

        // read the token from the string.
        // By default the stream interprets tokens as sequences separated by ' '.
        stream >> token;

        switch (token[0])
        {
            case 'P':
            {
			    // if the stack is empty report error
                if (stack.empty())
                {
                    stack.push(-1);
                }
                else
                {
                    // else pop the element and move on the next token
                    stack.pop();
                }
            }
            break;

		    case 'D':
		    {
			    // if the stack is empty report error
                if (stack.empty())
                {
					stack.push(-1);
                }
                else
                {
                    // duplicate the top element and move on the next token
                    stack.push(stack.top());
                }
		    }
            break;

		    case '+':
            {
			    // if the stack has less than two values report error
                if (stack.size() <= 1)
                {
                    stack.push(-1);
                }
                else
                {
                    // pop the last two values
                    const int a = stack.top();
                    stack.pop();

                    const int b = stack.top();
                    stack.pop();

                    // perform the operation
                    stack.push(numeric_error(a + b));
                }
            }
            break;

		    case '-':
		    {
			    // if the stack has less than two values report error
                if (stack.size() <= 1)
                {
                    stack.push(-1);
                }
                else
                {
                    // pop the last two values
                    const int a = stack.top();
                    stack.pop();

                    const int b = stack.top();
                    stack.pop();

                    // perform the operation
                    stack.push(numeric_error(a - b));
                }
		    }
		    break;

            default:
            {
			    // if the stack has reached max capacity report error
                if (stack.size() >= 2000)
                {
                    stack.push(-1);
                }
                else
                {
                    // convert the token into an integer
                    const int value = std::stoi(token);

                    // push the number in the stack
                    stack.push(value);
                }
            }
            break;
        }
    }

    // if the stack is empty report error, otherwise the result
    return stack.empty() ? -1 : stack.top();
}
