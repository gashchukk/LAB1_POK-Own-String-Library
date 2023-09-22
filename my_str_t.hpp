//
// Created by Shuma on 22.09.2023.
//

#ifndef LAB1_CSTRING_SHUMSKYI_HASHCHUK_MY_STR_T_H
#define LAB1_CSTRING_SHUMSKYI_HASHCHUK_MY_STR_T_H


class my_str_t {
private:
    char* data_m;
    size_t capacity_m;
    size_t size_m;
private:
    my_str_t(size_t size, char initial);
    my_str_t(const char* cstr);
    my_str_t(const std::string& str);
    my_str_t(const my_str_t& mystr); // конструктор копіювання

    // оператор присвоєння
    my_str_t& operator=(const my_str_t& mystr);

    // обмінює вміст стрічки з other за допомогою вказівників
    void swap(my_str_t& other) noexcept;

    // два варіанти оператора індексації
    char& operator[](size_t idx);
    const char& operator[](size_t idx) const;

    // те ж, що й оператори []
    char& at(size_t idx);
    const char& at(size_t idx) const;

    void reserve(size_t new_capacity);
    void shrink_to_fit();
    void resize(size_t new_size, char new_char = ' ');
    void clear();
    void insert(size_t idx, const my_str_t& str);
    void insert(size_t idx, char c);
    void insert(size_t idx, const char* cstr);
    void append(const my_str_t& str);
    void append(char c);
    void append(const char* cstr);
    void erase(size_t begin, size_t size);

    // повертають розмір стрічки та зарезервований блок пам'яті
    si z e_ t s i z e( )const noexcept;
    si z e_ t c a p a ci t y ( ) const noexcep t ;

    // повертає вказівник на С-стрічку
    const char* c_str() const noexcept;

    static constexpr size_t not_found = -1;
    size_t find(char c, size_t idx = 0);
    size_t find(const std::string& str, size_t idx = 0);
    size_t find(const char* cstr, size_t idx = 0);


    my_str_t s u b s t r ( si z e_ t begin , si z e_ t s i z e ) ;
    ~my_str_t ( ) ;
};

// оператори вводу та виводу
std::ostream& operator<<(std::ostream& stream, const my_str_t& str) {
    stream << str.c_str();
    return stream;
}

std::istream& operator>>(std::istream& stream, my_str_t& str) {
#error "Please implement the input, check every function, and remove this line!"
    return stream;
}

bool operator==(const my_str_t& str1, const my_str_t& str2);
bool operator!=(const my_str_t& str1, const my_str_t& str2);
bool operator>(const my_str_t& str1, const my_str_t& str2);
bool operator>=(const my_str_t& str1, const my_str_t& str2);
bool operator<(const my_str_t& str1, const my_str_t& str2);
bool operator<=(const my_str_t& str1, const my_str_t& str2);

bool operator==(const my_str_t& str1, const char* cstr2);
bool operator!=(const my_str_t& str1, const char* cstr2);
bool operator>(const my_str_t& str1, const char* cstr2);
bool operator>=(const my_str_t& str1, const char* cstr2);
bool operator<(const my_str_t& str1, const char* cstr2);
bool operator<=(const my_str_t& str1, const char* cstr2);

bool operator==(const char* cstr1, const my_str_t& str2);
bool operator!=(const char* cstr1, const my_str_t& str2);
bool operator>(const char* cstr1, const my_str_t& str2);
bool operator>=(const char* cstr1, const my_str_t& str2);
bool operator<(const char* cstr1, const my_str_t& str2);
bool operator<=(const char* cstr1, const my_str_t& str2);

std::istream& read_line(std::istream& stream, my_str_t& str);


#endif //LAB1_CSTRING_SHUMSKYI_HASHCHUK_MY_STR_T_H
