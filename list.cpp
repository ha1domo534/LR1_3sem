#include "list.h"

SinglyList::~SinglyList() { clear(); }

void SinglyList::clear() {
    while (head) { Node* t = head; head = head->next; delete t; }
    cnt = 0;
}

void SinglyList::push_front(const std::string& x) { 
    Node* n = new Node(x); n->next = head; head = n; cnt++; 
}

void SinglyList::push_back(const std::string& x) {
    Node* n = new Node(x);
    if (!head) { head = n; }
    else { Node* p = head; while (p->next) p = p->next; p->next = n; }
    cnt++;
}

void SinglyList::push_before(const std::string& target, const std::string& x) {
    if (!head) { std::cout << "-> ERROR: empty\n"; return; }
    if (head->val == target) { push_front(x); return; }
    Node* p = head;
    while (p->next && p->next->val != target) p = p->next;
    if (!p->next) { std::cout << "-> ERROR: not found\n"; return; }
    Node* n = new Node(x); n->next = p->next; p->next = n; cnt++;
}

void SinglyList::push_after(const std::string& target, const std::string& x) {
    Node* p = head;
    while (p && p->val != target) p = p->next;
    if (!p) { std::cout << "-> ERROR: not found\n"; return; }
    Node* n = new Node(x); n->next = p->next; p->next = n; cnt++;
}

void SinglyList::del_front() {
    if (!head) { std::cout << "-> ERROR: empty\n"; return; }
    Node* t = head; head = head->next; delete t; cnt--;
}

void SinglyList::del_back() {
    if (!head) { std::cout << "-> ERROR: empty\n"; return; }
    if (!head->next) { delete head; head = nullptr; cnt--; return; }
    Node* p = head;
    while (p->next->next) p = p->next;
    delete p->next; p->next = nullptr; cnt--;
}

void SinglyList::del_value(const std::string& x) {
    if (!head) { std::cout << "-> ERROR: empty\n"; return; }
    if (head->val == x) { del_front(); return; }
    Node* p = head;
    while (p->next && p->next->val != x) p = p->next;
    if (!p->next) { std::cout << "-> ERROR: not found\n"; return; }
    Node* t = p->next; p->next = t->next; delete t; cnt--;
}

bool SinglyList::find(const std::string& x) {
    Node* p = head;
    while (p) { if (p->val == x) return true; p = p->next; }
    return false;
}

int SinglyList::size() { return cnt; }

void SinglyList::print() {
    Node* p = head;
    while (p) { std::cout << p->val << " "; p = p->next; }
    std::cout << "\n";
}

std::vector<std::string> SinglyList::all() {
    std::vector<std::string> v; Node* p = head;
    while (p) { v.push_back(p->val); p = p->next; }
    return v;
}

void SinglyList::setAll(const std::vector<std::string>& v) {
    clear();
    for (const std::string& x : v) push_back(x);
}