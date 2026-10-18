#include "dlist.h"

DoublyList::~DoublyList() { clear(); }

void DoublyList::clear() {
    while (head) { Node* t = head; head = head->next; delete t; }
    tail = nullptr; cnt = 0;
}

void DoublyList::push_front(const std::string& x) {
    Node* n = new Node(x);
    n->next = head;
    if (head) head->prev = n;
    head = n;
    if (!tail) tail = n;
    cnt++;
}

void DoublyList::push_back(const std::string& x) {
    Node* n = new Node(x);
    n->prev = tail;
    if (tail) tail->next = n;
    tail = n;
    if (!head) head = n;
    cnt++;
}

void DoublyList::push_before(const std::string& target, const std::string& x) {
    if (!head) { std::cout << "-> ERROR: empty\n"; return; }
    if (head->val == target) { push_front(x); return; }
    Node* p = head;
    while (p && p->val != target) p = p->next;
    if (!p) { std::cout << "-> ERROR: not found\n"; return; }
    Node* n = new Node(x);
    n->next = p; n->prev = p->prev;
    p->prev->next = n;
    p->prev = n;
    cnt++;
}

void DoublyList::push_after(const std::string& target, const std::string& x) {
    Node* p = head;
    while (p && p->val != target) p = p->next;
    if (!p) { std::cout << "-> ERROR: not found\n"; return; }
    Node* n = new Node(x);
    n->next = p->next; n->prev = p;
    if (p->next) p->next->prev = n;
    p->next = n;
    if (tail == p) tail = n;
    cnt++;
}

void DoublyList::del_front() {
    if (!head) { std::cout << "-> ERROR: empty\n"; return; }
    Node* t = head;
    head = head->next;
    if (head) head->prev = nullptr; else tail = nullptr;
    delete t; cnt--;
}

void DoublyList::del_back() {
    if (!tail) { std::cout << "-> ERROR: empty\n"; return; }
    Node* t = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr; else head = nullptr;
    delete t; cnt--;
}

void DoublyList::del_value(const std::string& x) {
    Node* p = head;
    while (p && p->val != x) p = p->next;
    if (!p) { std::cout << "-> ERROR: not found\n"; return; }
    if (p == head) { del_front(); return; }
    if (p == tail) { del_back(); return; }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p; cnt--;
}

bool DoublyList::find(const std::string& x) {
    Node* p = head;
    while (p) { if (p->val == x) return true; p = p->next; }
    return false;
}

int DoublyList::size() { return cnt; }

void DoublyList::print() {
    Node* p = head; bool first = true;
    while (p) { 
        if (!first) std::cout << " <-> "; 
        std::cout << p->val; 
        first = false; 
        p = p->next; 
    }
    std::cout << "\n";
}

std::vector<std::string> DoublyList::all() {
    std::vector<std::string> v; Node* p = head;
    while (p) { v.push_back(p->val); p = p->next; }
    return v;
}

void DoublyList::setAll(const std::vector<std::string>& v) {
    clear();
    for (const std::string& x : v) push_back(x);
}