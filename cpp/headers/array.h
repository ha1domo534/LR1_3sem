#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string>

class Array {
    std::string* data;
    int count;
    int capacity;

public:
    Array();
    ~Array();
    
    void push_back(const std::string& x);
    void push_at(int i, const std::string& x);
    std::string get(int i);
    void del(int i);
    void set(int i, const std::string& x);
    int size();
    void print();
    
    std::string* all();
    void setAll(const std::string* v, int n);
};

#endif
