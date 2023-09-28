//
// Created by Shuma on 22.09.2023.
//

#include "mystring.hpp"

my_str_t::my_str_t(size_t size, char initial) {
    size_m = size + 1;
    capacity_m = size + (16 - (size%16));
    data_m = new char[capacity_m];

    memset(data_m, initial, size);
    data_m[size - 1] = '\0';
}

my_str_t::my_str_t(const char* cstr) {
    size_t string_length = strlen(cstr);
    size_m = string_length + 1;
    capacity_m = string_length + (16 - (string_length%16));
    data_m = new char[capacity_m];

    for (size_t i = 0; i < size_m - 1; ++i) {
        data_m[i] = cstr[i];
    }

    data_m[size_m] = '\0';
}

my_str_t::my_str_t(const std::string& str) {
    size_t string_length = str.size();
    capacity_m = string_length + (16 - (string_length%16));
    size_m = string_length + 1;
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
    data_m[size_m] = '\0';
}

my_str_t& my_str_t::operator=(const my_str_t& mystr) {
    if (this == &mystr) {
        return *this;
    }

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
    // взагалі легально???
    std::swap(data_m, other.data_m);
    std::swap(size_m, other.size_m);
    std::swap(capacity_m, other.capacity_m);
}

char& my_str_t::operator[](size_t idx) {
     return data_m[idx];
}

const char& my_str_t::operator[](size_t idx) const {
    return data_m[idx];
}

char& my_str_t::at(size_t idx) {
    if (idx >= size_m) {
        throw std::out_of_range("Index out of range");
    }
    return data_m[idx];
}

const char& my_str_t::at(size_t idx) const {
    if (idx >= size_m) {
        throw std::out_of_range("Index out of range");
    }
    return data_m[idx];
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
    capacity_m = size_m + (16 - (size_m % 16));

    char* new_data = new char[capacity_m];

    for (size_t i = 0; i < size_m; ++i) {
        new_data[i] = data_m[i];
    }
    delete[] data_m;

    data_m = new_data;
}

void my_str_t::resize(size_t new_size, char new_char) {
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

void my_str_t::clear() {
    size_m = 0;
    capacity_m = 16;
    data_m = new char[size_m];
}

void my_str_t::insert(size_t idx, const my_str_t& str) {
    if (idx > size_m) {
        throw std::out_of_range("Index out of range");
    }

    size_t new_size = size_m + str.size_m;

    if (new_size > capacity_m) {
        capacity_m = new_size;
    }

    char* new_data = new char[new_size + 1];

    // data before insert
    for (size_t i = 0; i < idx; ++i) {
        new_data[i] = data_m[i];
    }

    // insert data
    for (size_t i = 0; i < str.size_m; ++i) {
        new_data[idx + i] = str.data_m[i];
    }

    // after insert data
    for (size_t i = idx; i < size_m; ++i) {
        new_data[idx + str.size_m + i] = data_m[i];
    }

    new_data[new_size] = '\0';

    delete[] data_m;

    data_m = new_data;
    data_m = new_data;
    size_m = new_size;
}

// ?? чи буде це працювати чи треба один символ додати?
void my_str_t::insert(size_t idx, char c) {
    // ця функція служить для оптимізації, щоб не довелось
    // спочатку створювати із літери c стрічку my_str_t а
    // потім вставляти. Навіть якщо компілятор зробив би це
    // автоматично - це повільно

    if (idx > size_m) {
        throw std::out_of_range("Index out of range");
    }

    size_t new_size = size_m + 1;

    // Перевірка, чи не потрібно збільшити capacity_m
    if (new_size > capacity_m) {
        reserve(new_size);
    }

    // Переміщення даних на один елемент вправо
    for (size_t i = size_m; i > idx; --i) {
        data_m[i] = data_m[i - 1];
    }

    data_m[idx] = c;

    size_m = new_size;
    data_m[size_m] = '\0';
}

// Check if it works!!!
void my_str_t::insert(size_t idx, const char* cstr) {
    if (idx > size_m) {
        throw std::out_of_range("Index out of range");
    }

    size_t cstr_size = strlen(cstr);
    size_t new_size = size_m + cstr_size + 1;
    char *new_data = new char[new_size];

    // data before insert
    for (size_t i = 0; i < idx; ++i) {
        new_data[i] = data_m[i];
    }

    // insert data
    for (size_t i = 0; i < cstr_size; ++i) {
        new_data[idx + i] = cstr[i];
    }

    // after insert data
    for (size_t i = idx; i < size_m; ++i) {
        new_data[idx + cstr_size + i] = data_m[i];
    }

    new_data[new_size] = '\0';

    delete[] data_m;

    data_m = new_data;
    data_m = new_data;
    size_m = new_size;
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
    size_t length_str = str.size();

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

//erase

void my_str_t::erase(size_t begin, size_t size) {
    if(size + begin > size_m){
        size = size_m - begin;
    }

    for(size_t i = begin; i < size_m - size; ++i){
        data_m[i] = data_m[size + i];
    }

    size_m = size_m - size;
    data_m[size_m] = '\0';
}

size_t my_str_t::size() const noexcept{
    return size_m;
}

size_t my_str_t::capacity() const noexcept{
    return capacity_m;
}

const char* my_str_t::c_str() const noexcept{
    return data_m;
}

// оператори вводу та виводу
std::ostream& operator<<(std::ostream& stream, const my_str_t& str) {
    const char* str_data = str.c_str();

    for (size_t i = 0; i < str.size(); ++i) {
        stream << str_data[i];
    }

    return stream;
}

std::istream& operator>>(std::istream& stream, my_str_t& str) {
    for (size_t i = 0; i < str.size(); ++i) {
        if (!std::isspace(str[i])) {
            stream >> str[i];
        }
    }
    return stream;
}

//Bohdan's part
bool operator==(const my_str_t& str1, const my_str_t& str2){
    const char* CString1 = str1.c_str();
    const char* CString2 = str2.c_str();
    int i=0;
    while(CString1[i] !='\0' && CString2[i] !='\0'){
        if(CString1[i] != CString2[i]){
            return 0;
        }
        ++i;
    }
    return 1;

}
bool operator!=(const my_str_t& str1, const my_str_t& str2){
    const char* CString1 = str1.c_str();
    const char* CString2 = str2.c_str();
    int i=0;
    while(CString1[i] !='\0' && CString2[i] !='\0'){
        if(CString1[i] == CString2[i]){
            return 0;
        }
        ++i;
    }
    return 1;
}
bool operator> (const my_str_t& str1, const my_str_t& str2){
    const char* CString1 = str1.c_str();
    const char* CString2 = str2.c_str();
    if(strlen(CString1) > strlen(CString2)) {
        return 1;
    }else
        return 0;
}
bool operator>=(const my_str_t& str1, const my_str_t& str2){
    const char* CString1 = str1.c_str();
    const char* CString2 = str2.c_str();
    if(strlen(CString1) >= strlen(CString2)) {
        return 1;
    }else
        return 0;
}
bool operator< (const my_str_t& str1, const my_str_t& str2){
    const char* CString1 = str1.c_str();
    const char* CString2 = str2.c_str();
    if(strlen(CString1) < strlen(CString2)){
        return 1;
    }else
        return 0;
}
bool operator<=(const my_str_t& str1, const my_str_t& str2){
    const char* CString1 = str1.c_str();
    const char* CString2 = str2.c_str();
    if(strlen(CString1) <= strlen(CString2)){
        return 1;
    }else
        return 0;
}
// Now Goes str vs const str
bool operator==(const my_str_t& str1, const char* cstr2){
    const char* CString1 = str1.c_str();
    int i=0;
    while(CString1[i] !='\0' && cstr2[i] !='\0'){
        if(CString1[i] != cstr2[i]){
            return 0;
        }
        ++i;
    }
    return 1;
}
bool operator!=(const my_str_t& str1, const char* cstr2){
    const char* CString1 = str1.c_str();
    int i=0;
    while(CString1[i] !='\0' && cstr2[i] !='\0'){
        if(CString1[i] == cstr2[i]){
            return 0;
        }
        ++i;
    }
    return 1;
}
bool operator>(const my_str_t& str1, const char* cstr2){
    const char* CString1 = str1.c_str();
    if(strlen(CString1) > strlen(cstr2)){
        return 1;
    }else
        return 0;
}
bool operator>=(const my_str_t& str1, const char* cstr2){
    const char* CString1 = str1.c_str();
    if(strlen(CString1) >= strlen(cstr2)){
        return 1;
    }else
        return 0;
}
bool operator<(const my_str_t& str1, const char* cstr2){
    const char* CString1 = str1.c_str();
    if(strlen(CString1) < strlen(cstr2)){
        return 1;
    }else
        return 0;
}
bool operator<=(const my_str_t& str1, const char* cstr2){
    const char* CString1 = str1.c_str();
    if(strlen(CString1) <= strlen(cstr2)){
        return 1;
    }else
        return 0;
}
 //the next one goes const str vs str
 bool operator==(const char* cstr1, const my_str_t& str2){
     const char* CString2 = str2.c_str();
     int i=0;
     while(cstr1[i] !='\0' && CString2[i] !='\0'){
         if(cstr1[i] != CString2[i]){
             return 0;
         }
         ++i;
     }
     return 1;
 }
bool operator!=(const char* cstr1, const my_str_t& str2){
    const char* CString2 = str2.c_str();
    int i=0;
    while(cstr1[i] !='\0' && CString2[i] !='\0'){
        if(cstr1[i] == CString2[i]){
            return 0;
        }
        ++i;
    }
}

bool operator>(const char* cstr1, const my_str_t& str2){
    const char* CString2 = str2.c_str();
    if(strlen(cstr1) > strlen(CString2)){
        return 1;
    }else
        return 0;
}
bool operator>=(const char* cstr1, const my_str_t& str2){
    const char* CString2 = str2.c_str();
    if(strlen(cstr1) >= strlen(CString2)){
        return 1;
    }else
        return 0;
}
bool operator<(const char* cstr1, const my_str_t& str2){
    const char* CString2 = str2.c_str();
    if(strlen(cstr1) < strlen(CString2)){
        return 1;
    }else
        return 0;
}
bool operator<=(const char* cstr1, const my_str_t& str2){
    const char* CString2 = str2.c_str();
    if(strlen(cstr1) <= strlen(CString2)){
        return 1;
    }else
        return 0;
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

my_str_t my_str_t::substr(size_t begin, size_t size) {
    if (size + begin > size_m) {
        size = size_m - begin;
    }

    //створимо нову сабстрінгу
    char *new_str = new char[size + 1];

    //перекопіюємо в неї симовли
    for (size_t i = 0; i < size; ++i) {
        new_str[i] = data_m[begin + i];
    }

    new_str[size] = '\0';
    my_str_t result(new_str);
    delete[] new_str; // обов'язково звільняємо пам'ять

    return result;
}

std::istream& readline(std::istream& stream, my_str_t& str) {
    char character;
    while (stream.get(character)) {
        if  (character == '\n') {
            break;
        }
        str.append(str);
    }
    return stream;

}

my_str_t::~my_str_t() {
    delete[] data_m;
}