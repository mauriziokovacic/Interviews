#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


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

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    fizzBuzz(n);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
