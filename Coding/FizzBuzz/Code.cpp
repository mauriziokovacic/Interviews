void fizzBuzz(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        const char value = ((i % 3) == 0) | (((i % 5) == 0) << 1);
        if (value)
        {
            std::cout << ((value & 1) ? "Fizz" : "") << ((value & 2) ? "Buzz" : "") << std::endl;
        }
        else
        {
            std::cout << i << std::endl;
        }
    }
}
