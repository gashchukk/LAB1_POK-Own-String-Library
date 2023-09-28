// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "mystring.hpp"

int main(int argc, char* argv[]) {
    my_str_t str1(10, 'A');
    my_str_t str2("Hello");
    my_str_t str3(std::string("World"));
    my_str_t str4(str1);

//    my_str_t str5;
//    str5 = str2;

    char ch1 = str1[3];
    const char ch2 = str2[1];

    str1[0] = 'B';
    str2.at(2) = 'X';

    str3.reserve(50);
    str4.shrink_to_fit();
//    str5.resize(15, 'Z');
//    str5.clear();

    str1.insert(2, str2);
    str2.insert(0, 'H');
    str3.insert(5, " ");
    str4.append(str1);
//    str5.append("New Text");

    str4.erase(3, 4);

    size_t size1 = str1.size();
    size_t capacity2 = str2.capacity();
    const char* cstr3 = str3.c_str();

    size_t foundIdx1 = str1.find('A');
    size_t foundIdx2 = str2.find("lo");

    my_str_t subStr1 = str1.substr(2, 5);
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
    return 0;
}
