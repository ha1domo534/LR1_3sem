#include "array.h"

//Добавление в конец
void Array::push_back(const std::string& x) { 
    data.push_back(x); 
}

//Добавление по индексу
void Array::push_at(int i, const std::string& x) {
    if (i < 0 || i > (int)data.size()) { 
        std::cout << "-> ERROR: index\n"; 
        return; 
    }
    data.insert(data.begin() + i, x);
}

//Получение элемента
std::string Array::get(int i) {
    if (i < 0 || i >= (int)data.size()) { 
        std::cout << "-> ERROR: index\n"; 
        return ""; 
    }
    return data[i];
}

//Удаление 
void Array::del(int i) {
    if (i < 0 || i >= (int)data.size()) { 
        std::cout << "-> ERROR: index\n"; 
        return; 
    }
    data.erase(data.begin() + i);
}

//Замена 
void Array::set(int i, const std::string& x) {
    if (i < 0 || i >= (int)data.size()) { 
        std::cout << "-> ERROR: index\n"; 
        return; 
    }
    data[i] = x;
}

// размер
int Array::size() { 
    return data.size(); 
}

//Вывод 
void Array::print() {
    for (int i = 0; i < (int)data.size(); i++) {
        std::cout << data[i];
        if (i != (int)data.size() - 1) std::cout << " ";
    }
    std::cout << "\n";
}

//Получение элементов 
std::vector<std::string> Array::all() { 
    return data; 
}

//Запись элементов 
void Array::setAll(const std::vector<std::string>& v) { 
    data = v; 
}
