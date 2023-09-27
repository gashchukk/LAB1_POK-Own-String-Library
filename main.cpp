// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "mystring.hpp"

int main(int argc, char* argv[]) {
    my_str_t s(1, 'A');

    //ліза
    my_str_t s1(5,'Hello');
    my_str_t s2(5,'world');
    s1.append(s2);
    s1.append('!');
    s1.append(".Sunny day");

    s1.erase(1,2);

    size_t search1 = s1.find('lo');
    size_t search2= s1.find("day");
    size_t search3 = s1.find("orld");

    my_str_t substr = s1.substr(3, 2);
    std::cout << "4568";
    return 0;
}
