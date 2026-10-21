#ifndef COMPLETE_TREE_H
#define COMPLETE_TREE_H

#include <iostream>
#include <vector>
#include <string>

class CompleteBinaryTree {
    struct Node {
        std::string val;
        Node* left;
        Node* right;
        Node(const std::string& v) : val(v), left(nullptr), right(nullptr) {}
    };
    
    Node* root = nullptr;
    int cnt = 0;

    void destroyTree(Node* node);
    Node* findNodePtr(Node* node, const std::string& x);

public:
    ~CompleteBinaryTree();

    void insert(const std::string& x);
    bool find(const std::string& x);
    bool check();
    int size();
    void print();
    std::vector<std::string> all();
    void setAll(const std::vector<std::string>& v);
    
    //Принудительная вставка (для демонстрации TBREAK)
    bool forceInsert(const std::string& parentVal, char side, const std::string& childVal);
};

#endif