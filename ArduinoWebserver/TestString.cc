#include "String.h"
#include <iostream>

using string = Standard::string;
using std::cout;
using std::endl;

Standard::string fill_third(const Standard::string other)
{
    char a[6] = "AABCC";
    string b = a;
    Standard::string new_str = b.substr(1, other.size()-1);
    return new_str;
}
int main()
{
    using Standard::string;
    using Standard::string_compare;
    char a[] = "ABC";
    char b[] = "ABCDE";
    Standard::string first{a};
    cout << first.size() << endl;
    cout << first.c_str()<<endl;
    Standard::string second{b};
    cout << second.size() << endl;
    cout << second.c_str() << endl;
    first+=second;
    cout << first.c_str()<<endl;
    cout <<first.size()<<endl;
    for(int i = 0; i < first.size(); ++i )
    {
        cout << (int)first[i]<<endl;
    }
    first = a;
    if ((first != second))
    {
        cout << "success != with" << endl;
    }
    else
    {
        cout << "fail != with" << endl;
    }

    if (first.find_first_of('C') == 2)
    {
        cout << "Success find with: char, it was: " << first.find_first_of('C') << endl;
    }
    else
    {
        cout << "fail find with, char, it was: " << first.find_first_of('C') << endl;
    }
     if (first.find_first_of("BC") == 1)
    {
        cout << "Success find with, str, it was: " << first.find_first_of("BC") << endl;
    }
    else
    {
        cout << "fail find with, st,r it was: " << first.find_first_of("BC") << endl;
    }

    if(first<second)
    {
        cout << "Success < " << endl;
    }
    else
    {
         cout << "Fail < " << endl;
    }
    if(second>first)
    {
        cout << "Success > " << endl;
    }
    else
    {
         cout << "Fail > " << endl;
    }
    string third = fill_third(first);
    if(first == third)
    {
        cout << "Success copy const " << endl;
    }
    else
    {
         cout << "Fail succes coppy ocnst " << endl;
    }

    return 0;
}
