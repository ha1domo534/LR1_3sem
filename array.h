#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <vector>
#include <string>

class Array {
    std::vector<std::string> data;
public:
    void push_back(const std::string& x);
    void push_at(int i, const std::string& x);
    std::string get(int i);
    void del(int i);
    void set(int i, const std::string& x);
    int size();
    void print();
    std::vector<std::string> all();
    void setAll(const std::vector<std::string>& v);
};

#endif
