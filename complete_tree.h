#ifndef COMPLETE_TREE_H
#define COMPLETE_TREE_H

#include <iostream>
#include <vector>
#include <string>

class CompleteBinaryTree {
    std::vector<std::string> data;
public:
    void insert(const std::string& x);
    bool find(const std::string& x);
    bool isComplete();
    int size();
    void print();
    std::vector<std::string> all();
    void setAll(const std::vector<std::string>& v);
};

#endif