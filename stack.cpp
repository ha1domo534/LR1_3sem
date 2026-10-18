#include "stack.h"

void Stack::push(const std::string& x) { data.push_back(x); }

void Stack::pop() {
    if (data.empty()) { std::cout << "-> ERROR: empty\n"; return; }
    std::cout << data.back() << "\n";
    data.pop_back();
}

void Stack::peek() {
    if (data.empty()) { std::cout << "-> ERROR: empty\n"; return; }
    std::cout << "-> " << data.back() << "\n";
}

int Stack::size() { return data.size(); }

void Stack::print() {
    for (int i = (int)data.size() - 1; i >= 0; i--) {
        std::cout << data[i] << "\n";
    }
}

std::vector<std::string> Stack::all() { return data; }

void Stack::setAll(const std::vector<std::string>& v) { data = v; }