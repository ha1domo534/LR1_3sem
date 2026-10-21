#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
#include <string>

class Stack {
    std::vector<std::string> data;
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