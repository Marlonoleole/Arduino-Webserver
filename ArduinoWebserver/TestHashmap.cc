#include "Hashmap.h"
#include <iostream>
#include "string.h"
using Map::Hashmap;
using string = Standard::string;

int main()
{
    char a[] = "Test";
    char b[] = "Sucess";
    string a1{a};
    string b1{b};

#if 1
    Hashmap<int, int> h{};
    h.add(1, 2);
    h.add(2, 4);
    h.add(11, 3);
    h.add(21, 5);
    std::cout << *h.get(1) << std::endl;
    std::cout << *h.get(2) << std::endl;
    std::cout << *h.get(11) << std::endl;
    std::cout << *h.get(21) << std::endl;
    h.remove(11);
    std::cout << *h.get(1) << std::endl;
    std::cout << h.get(11) << std::endl;
    std::cout << *h.get(21) << std::endl;
#endif
#if 1
    Hashmap<string, string> h2{};
    h2.add("A", a1);
    h2.add("B", b1);
    std::cout << &(*h2.get("A")->c_str()) << std::endl;
    std::cout << &(*h2.get("B")->c_str()) << std::endl;
#endif
std::cout << "Ending Tests: " << std::endl;
}