#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <deque>
#include <vector>
#include <string>

class Queue {
    std::deque<std::string> data;
public:
    void push(const std::string& x);
    void pop();
    void peek();
    int size();
    void print();
    std::vector<std::string> all();
    void setAll(const std::vector<std::string>& v);
};

#endif