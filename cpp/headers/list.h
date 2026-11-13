#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include <vector>

class SinglyList {
    struct Node { 
        std::string val; 
        Node* next; 
        Node(const std::string& v): val(v), next(nullptr) {} 
    };
    Node* head;
    int cnt;

public:
    SinglyList();
    ~SinglyList();
    
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
