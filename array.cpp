#include "array.h"

void Array::push_back(const std::string& x) { data.push_back(x); }

void Array::push_at(int i, const std::string& x) {
    if (i < 0 || i > (int)data.size()) { std::cout << "-> ERROR: index\n"; return; }
    data.insert(data.begin() + i, x);
}

std::string Array::get(int i) {
    if (i < 0 || i >= (int)data.size()) { std::cout << "-> ERROR: index\n"; return ""; }
    return data[i];
}

void Array::del(int i) {
    if (i < 0 || i >= (int)data.size()) { std::cout << "-> ERROR: index\n"; return; }
    data.erase(data.begin() + i);
}

void Array::set(int i, const std::string& x) {
    if (i < 0 || i >= (int)data.size()) { std::cout << "-> ERROR: index\n"; return; }
    data[i] = x;
}

int Array::size() { return data.size(); }

void Array::print() {
    for (int i = 0; i < (int)data.size(); i++) {
        std::cout << data[i];
        if (i != (int)data.size() - 1) std::cout << " ";
    }
    std::cout << "\n";
}

std::vector<std::string> Array::all() { return data; }

void Array::setAll(const std::vector<std::string>& v) { data = v; }
