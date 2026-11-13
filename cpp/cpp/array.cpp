#include "array.h"

//Конструктор
Array::Array() {
    capacity = 4;
    count = 0;
    data = new std::string[capacity];
}

//Деструктор
Array::~Array() {
    delete[] data;
}

//Добавление в конец
void Array::push_back(const std::string& x) { 
    if (count == capacity) {
        capacity *= 2;
        std::string* nd = new std::string[capacity];
        for (int i = 0; i < count; i++) nd[i] = data[i];
        delete[] data; data = nd;
    }
    data[count++] = x; 
}

//Добавление по индексу
void Array::push_at(int i, const std::string& x) {
    if (i < 0 || i > count) { std::cout << "-> ERROR: index\n"; return; }
    if (count == capacity) {
        capacity *= 2;
        std::string* nd = new std::string[capacity];
        for (int j = 0; j < count; j++) nd[j] = data[j];
        delete[] data; data = nd;
    }
    for (int j = count; j > i; j--) data[j] = data[j - 1];
    data[i] = x; count++;
}

//Получение элемента
std::string Array::get(int i) {
    if (i < 0 || i >= count) { std::cout << "-> ERROR: index\n"; return ""; }
    return data[i];
}

//Удаление
void Array::del(int i) {
    if (i < 0 || i >= count) { std::cout << "-> ERROR: index\n"; return; }
    for (int j = i; j < count - 1; j++) data[j] = data[j + 1];
    count--;
}

//Замена
void Array::set(int i, const std::string& x) {
    if (i < 0 || i >= count) { std::cout << "-> ERROR: index\n"; return; }
    data[i] = x;
}

//Размер
int Array::size() { 
    return count; 
}

//Вывод
void Array::print() {
    for (int i = 0; i < count; i++) {
        std::cout << data[i];
        if (i != count - 1) std::cout << " ";
    }
    std::cout << "\n";
}

//Получение элементов
std::string* Array::all() { 
    return data; 
}

//Запись элементов
void Array::setAll(const std::string* v, int n) { 
    delete[] data;
    capacity = (n == 0) ? 4 : n * 2;
    count = n;
    data = new std::string[capacity];
    for (int i = 0; i < n; i++) data[i] = v[i];
}
