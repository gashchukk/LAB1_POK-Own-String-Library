//
// Created by Shuma on 22.09.2023.
//

#include "my_str_t.hpp"

my_str_t::my_str_t(size_t size, char initial) {
    // Створює стрічку із size копій літери initial
    // capacity_m встановлюється рівним або більшим за size
    // Обробка помилок конструкторами:
    //  Не повинні заважати пропагуванню виключення
    //  std::bad_alloc


//    можливо варто так робити?
//    for(){
//        *(data_m + i) = initial
//    }

    try {
        size_m = size + 1;
        capacity_m = size;
        data_m = new char[size_m];

        memset(data_m, initial, size);
        data_m[size] = '\0';

    } catch (std::bad_alloc){
        data_m = nullptr;
        capacity_m = 0;
        size_m = 0;
        // throw
    }
}

my_str_t::my_str_t(const char* cstr) {
    size_t string_length = strlen(cstr);
    size_m = string_length;
    capacity_m = string_length + 1;
    data_m = new char[capacity_m];

    strcpy(data_m, cstr);

    data_m[size_m] = '\0';
}

my_str_t::my_str_t(const std::string& str) {
    // копіює стрічку c++, вимоги до capacity_m ті що й вище
//    capacity_m = str.size() + (16 - (str.size()%16));
    size_t string_length = str.length();
    size_m = string_length;
    capacity_m = string_length + 1;
    data_m = new char[capacity_m];

    for (size_t i = 0; i < size_m; ++i) {
        data_m[i] = str[i];
    }

    data_m[size_m] = '\0';

}

my_str_t::my_str_t(const my_str_t& mystr) {
    capacity_m = mystr.capacity_m;
    size_m = mystr.size_m;
    data_m = new char[capacity_m];
    for (size_t i = 0; i < size_m; ++i) {
        data_m[i] = mystr.data_m[i];
    }
}