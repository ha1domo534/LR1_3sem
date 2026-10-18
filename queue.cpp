#include "queue.h"

void Queue::push(const std::string& x) { data.push_back(x); }

void Queue::pop() {
    if (data.empty()) { std::cout << "-> ERROR: empty\n"; return; }
    std::cout << data.front() << "\n";
    data.pop_front();
}

void Queue::peek() {
    if (data.empty()) { std::cout << "-> ERROR: empty\n"; return; }
    std::cout << "-> " << data.front() << "\n";
}

int Queue::size() { return data.size(); }

void Queue::print() {
    for (int i = 0; i < (int)data.size(); i++) {
        std::cout << data[i];
        if (i != (int)data.size() - 1) std::cout << " ";
    }
    std::cout << "\n";
}

std::vector<std::string> Queue::all() { return std::vector<std::string>(data.begin(), data.end()); }

void Queue::setAll(const std::vector<std::string>& v) { data = std::deque<std::string>(v.begin(), v.end()); }