#include "queue.h"

//Добавление в конецe
void Queue::push(const std::string& x) { 
    data.push_back(x); 
}

//Удаление из начала
void Queue::pop() {
    if (data.empty()) { 
        std::cout << "-> ERROR: empty\n"; 
        return; 
    }
    std::cout << data.front() << "\n";
    data.pop_front();
}

//Просмотр начала 
void Queue::peek() {
    if (data.empty()) { 
        std::cout << "-> ERROR: empty\n"; 
        return; 
    }
    std::cout << "-> " << data.front() << "\n";
}

// размера
int Queue::size() { 
    return data.size(); 
}

//Вывод 
void Queue::print() {
    for (int i = 0; i < (int)data.size(); i++) {
        std::cout << data[i];
        if (i != (int)data.size() - 1) std::cout << " ";
    }
    std::cout << "\n";
}

//Получение элементов 
std::vector<std::string> Queue::all() { 
    return std::vector<std::string>(data.begin(), data.end()); 
}

//Запись элементов 
void Queue::setAll(const std::vector<std::string>& v) { 
    data = std::deque<std::string>(v.begin(), v.end()); 
}