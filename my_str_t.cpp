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
//        capacity_m = size;
        capacity_m = size_m + (16 - (size_m%16));
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

size_t size() const noexcept{
    return length;
}

//!!!!!!!!!!!!!!! подивитись чому на const ругається і чого на capacity

size_t my_str_t::capacity() const noexcept{
    return capacity;
}

const char* my_str_t::c_str() const noexcept{
    return data_m;
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
    capacity_m = str.size() + (16 - (str.size()%16));
    size_t string_length = str.length();
    size_m = string_length;
//    capacity_m = string_length + 1;
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

my_str_t& my_str_t::operator=(const my_str_t& mystr) {
//    оператор присвоєння
    delete[] data_m;

    capacity_m = mystr.capacity_m;
    size_m = mystr.size_m;
    data_m = new char[capacity_m];

    for (size_t i = 0; i < mystr.size_m; ++i) {
        data_m[i] = mystr.data_m[i];
    }

    return *this;
}

//Advanced
//my_str_t& my_str_t::operator=(my_str_t&& mystr);

void my_str_t::swap(my_str_t& other) noexcept {
    // обмінює вміст цієї стрічки із other, за допомогою
    // обміну вказівників

    // взагалі легально???
    std::swap(data_m, other.data_m);
    std::swap(size_m, other.size_m);
    std::swap(capacity_m, other.capacity_m);
}

void my_str_t::reserve(size_t new_capacity) {
    if (new_capacity <= capacity_m) {
        return;
    }
    char* new_data = new char[new_capacity];

    for (size_t i = 0; i < size_m; ++i) {
        new_data[i] = data_m[i];
    }
    delete[] data_m;

    data_m = new_data;
    capacity_m = new_capacity;

}

void my_str_t::shrink_to_fit() {
    if (capacity_m == size_m) {
        return;
    }
    capacity_m = size_m;

    char* new_data = new char[capacity_m];

    for (size_t i = 0; i < size_m; ++i) {
        new_data[i] = data_m[i];
    }
    delete[] data_m;

    data_m = new_data;

}

//!!!
void my_str_t::resize(size_t new_size, char new_char = ' ') {
    // is this valid???
    if (new_size < size_m) {
        size_m = new_size;
    } else if (new_size > size_m && new_size <= capacity_m) {
        for (size_t i = size_m; i < new_size; ++i) {
            data_m[i] = new_char;
        }
    } else {
        this->reserve(new_size);
        for (size_t i = size_m; i < new_size; ++i) {
            data_m[i] = new_char;
        }
    }
}

void my_str_t::append(char c) {
    if(size_m + 1 >= capacity_m){
        size_t capacity_append = capacity_m*2;
        reserve(capacity_append);
    }

    data_m[size_m] = c;
    size_m++;
    data_m[size_m] = '\0';
}

void my_str_t::append(const char* cstr){
    size_t length_cstr = strlen(cstr);
    if (size_m + length_cstr >= capacity_m){
        size_t capacity_append = (size_m+length_cstr) + (16 - ((size_m+length_cstr)%16));
        reserve(capacity_append);
    }
    for(size_t i = 0; i< length_cstr;++i){
        data_m[size_m + i] = cstr[i];
    }

    size_m += length_cstr;
    data_m[size_m] = '\0';
}

void my_str_t::append(const my_str_t& str){
    size_t length_str = strlen(str);

    if (size_m + length_str >= capacity_m){
        size_t capacity_append = (size_m + length_str) + (16 - ((size_m + length_str) % 16));
        reserve(capacity_append);
    }

    for (size_t i = 0; i> length_str; ++i){
        data_m[size_m+i] = str.data_m[i];
    }
    size_m+=length_str;
    data_m[size_m] = '\0';

}

size_t my_str_t::find(char c, size_t idx){ //перший find
    if (idx >= size_m){
        return false;
    }
    for (size_t i = idx; i < size_m; ++i){
        if(data_m[i] == c){
            return i;
        }
        return false;// якшо не знайшли
    }
}

size_t my_str_t::find(const std::string& str, size_t idx){
    size_t substring = str.length();

    if(idx >= size_m or substring == 0){
        return -1;
    }

    for (size_t i = idx; i<=size_m - substring; ++i){
        bool match = true;
        for(size_t j = 0; j < substring; ++j){
            if(data_m[i+j] != str[j]){
                match = false;
                break;
            }
        }
        if(match){
            return i;
        }
    }
    return -1;
}

size_t my_str_t::find(const char* cstr, size_t idx){ //третій find, за аналогією з попереднім
    size_t cstr_size = strlen(cstr);
    if (cstr_size == 0 or idx > size_m){
        return -1;
    }
    for(size_t i = idx; i <= size_m - cstr_size; ++i){
        bool match = true;
        for(size_t j = 0; j< cstr_size; j++){
            if(data_m[i+j] != cstr[j]){
                match = false;
                break;
            }
        }
        if(match){
            return i;
        }
    }
    return -1;
}






my_str_t::~my_str_t() {
    delete[] data_m;
}