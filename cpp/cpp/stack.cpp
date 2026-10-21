#include "stack.h"

//Добавление 
void Stack::push(const std::string& x) { 
    data.push_back(x); 
}

//Удаление 
void Stack::pop() {
    if (data.empty()) { 
        std::cout << "-> ERROR: empty\n"; 
        return; 
    }
    std::cout << data.back() << "\n";
    data.pop_back();
}

//Просмотр вершины 
void Stack::peek() {
    if (data.empty()) { 
        std::cout << "-> ERROR: empty\n"; 
        return; 
    }
    std::cout << "-> " << data.back() << "\n";
}

// размера
int Stack::size() { 
    return data.size(); 
}

//Вывод 
void Stack::print() {
    for (int i = (int)data.size() - 1; i >= 0; i--) {
        std::cout << data[i] << "\n";
    }
}

//Получение элементов 
std::vector<std::string> Stack::all() { 
    return data; 
}

//Запись элементов 
void Stack::setAll(const std::vector<std::string>& v) { 
    data = v; 
}