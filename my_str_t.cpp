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

my_str_t::my_str_t(const char* cstr) {
    size_t string_length = strlen(cstr);
    size_m = string_length;
    capacity_m = string_length + 1;
    data_m = new char[capacity_m];

    // strcpy можна використовувати ???
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

// два варіанти оператора індексації
char& my_str_t::operator[](size_t idx) {
     return data_m[idx];
}

const char& my_str_t::operator[](size_t idx) const {
    // не треба це використовувати ???
//    if (idx >= size_m) {
//        throw std::out_of_range("Index out of range");
//    }
    return data_m[idx];
}

// те ж, що й оператори []
char& my_str_t::at(size_t idx) {

}

const char& my_str_t::at(size_t idx) const {

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
//redefinition of the standart element new_char???
void my_str_t::resize(size_t new_size, char new_char) {
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

// ???
void my_str_t::clear() {
    // is this legal???
    size_m = 0;
    // ??
    data_m[0] = '\0';
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

my_str_t::~my_str_t() {
    delete[] data_m;
}