#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <string>
#include <vector>

class DoublyList {
    struct Node { 
        std::string val; 
        Node* prev; 
        Node* next; 
        Node(const std::string& v): val(v), prev(nullptr), next(nullptr) {} 
    };
    Node* head;
    Node* tail;
    int cnt;

public:
    DoublyList();
    ~DoublyList();
    
    void push_front(const std::string& x);
    void push_back(const std::string& x);
    void push_before(const std::string& target, const std::string& x);
    void push_after(const std::string& target, const std::string& x);
    
    void del_front();
    void del_back();
    void del_before(const std::string& target); 
    void del_after(const std::string& target);  
    void del_value(const std::string& x);
    
    bool find(const std::string& x);
    std::string get_at(int index);            
    int size();
    void print();
    
    std::vector<std::string> all();
    void setAll(const std::vector<std::string>& v);
};

#endif
