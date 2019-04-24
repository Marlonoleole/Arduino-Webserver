#include "String.h"

unsigned long Standard::string_length(const char *chars)
{
    unsigned long count{0};
    while (chars[count++])
        /**do nothing**/;
    return count - 1;
}
void Standard::string_copy(char *dest, const char *source, const int length)
{
    for (int i = 0; i <= length; ++i)
    {
        dest[i] = source[i];
    }
}
int Standard::string_compare(const char *first, const char *second)
{
    int loop_count{0};
    while (first[loop_count] && second[loop_count])
    {
	    int sum = first[loop_count] - second[loop_count];
	    if (sum != 0)
	    {
		    return sum;
	    }
	    ++loop_count;
    }
    if ((!first[loop_count]) && second[loop_count])
		return -1;
    else if (first[loop_count] && !second[loop_count])
	 return 1;
    return 0;
}
int Standard::string_find_first_of(const char *chars, const int length, const char symbol)
{
    for (int index = 0; index < length; ++index)
    {
        if (chars[index] == symbol)
        {
            return index;
        }
    }
    return -1;
}
int Standard::string_find_first_of(const char *chars, const int length, const char *symbols)
{
    int olength = string_length(symbols);
    int index2{0};
    int first_found_index = -1;
    for (int index = 0; index < length; ++index)
    {
        if (index2 == olength)
        {
            return first_found_index;
        }
        else if (chars[index] != symbols[index2])
        {
            index2 = 0;
            first_found_index = -1;
        }
        else if (chars[index] == symbols[index2])
        {
            if (first_found_index == -1)
                first_found_index = index;
            ++index2;
        }
    }
    if (index2 < olength )
    {
        return -1;
    }
    else
    {
        return first_found_index;
    }
}
int Standard::hash_code(const string &i)
{
    int code{0};
    int loop_counter{0};
    while (i[loop_counter])
    {
        code += i[loop_counter] + (loop_counter * 1000);
        ++loop_counter;
    }
    return code;
}
bool Standard::string_verify(const char *chars, const int length)
{
    if(chars[length]!='\0')
    {
        return false;
    }
    return true;
}