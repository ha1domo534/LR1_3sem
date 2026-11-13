#include "dlist.h"

//Конструктор
DoublyList::DoublyList() : head(nullptr), tail(nullptr), cnt(0) {}

//Деструктор
DoublyList::~DoublyList() {
    while (head) { Node* t = head; head = head->next; delete t; }
}

//Добавление в начало
void DoublyList::push_front(const std::string& x) {
    Node* n = new Node(x); n->next = head;
    if (head) head->prev = n; else tail = n;
    head = n; cnt++;
}

//Добавление в конец
void DoublyList::push_back(const std::string& x) {
    Node* n = new Node(x); n->prev = tail;
    if (tail) tail->next = n; else head = n;
    tail = n; cnt++;
}

//Вставка перед
void DoublyList::push_before(const std::string& target, const std::string& x) {
    Node* p = head;
    while (p && p->val != target) p = p->next;
    if (!p) return;
    Node* n = new Node(x); n->next = p; n->prev = p->prev;
    if (p->prev) p->prev->next = n; else head = n;
    p->prev = n; cnt++;
}

//Вставка после
void DoublyList::push_after(const std::string& target, const std::string& x) {
    Node* p = head;
    while (p && p->val != target) p = p->next;
    if (!p) return;
    Node* n = new Node(x); n->prev = p; n->next = p->next;
    if (p->next) p->next->prev = n; else tail = n;
    p->next = n; cnt++;
}

//Удаление из начала
void DoublyList::del_front() {
    if (!head) return;
    Node* t = head; head = head->next;
    if (head) head->prev = nullptr; else tail = nullptr;
    delete t; cnt--;
}

//Удаление из конца
void DoublyList::del_back() {
    if (!tail) return;
    Node* t = tail; tail = tail->prev;
    if (tail) tail->next = nullptr; else head = nullptr;
    delete t; cnt--;
}

//Удаление перед 
void DoublyList::del_before(const std::string& target) {
    Node* p = head;
    while (p && p->val != target) p = p->next;
    if (!p || !p->prev) return;
    Node* t = p->prev; p->prev = t->prev;
    if (t->prev) t->prev->next = p; else head = p;
    delete t; cnt--;
}

//Удаление после 
void DoublyList::del_after(const std::string& target) {
    Node* p = head;
    while (p && p->val != target) p = p->next;
    if (!p || !p->next) return;
    Node* t = p->next; p->next = t->next;
    if (t->next) t->next->prev = p; else tail = p;
    delete t; cnt--;
}

//Удаление по значению
void DoublyList::del_value(const std::string& x) {
    Node* p = head;
    while (p && p->val != x) p = p->next;
    if (!p) return;
    if (p == head) del_front();
    else if (p == tail) del_back();
    else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p; cnt--;
    }
}

//Поиск
bool DoublyList::find(const std::string& x) {
    Node* p = head;
    while (p) { if (p->val == x) return true; p = p->next; }
    return false;
}

//Получение по индексу
std::string DoublyList::get_at(int index) {
    if (index < 0) return "";
    Node* p = head;
    for (int i = 0; i < index && p; i++) p = p->next;
    return p ? p->val : "";
}

//Размер
int DoublyList::size() { return cnt; }

//Вывод
void DoublyList::print() {
    Node* p = head;
    while (p) { std::cout << p->val; if (p->next) std::cout << " <-> "; p = p->next; }
    std::cout << "\n";
}

//Получение элементов
std::vector<std::string> DoublyList::all() {
    std::vector<std::string> v; Node* p = head;
    while (p) { v.push_back(p->val); p = p->next; }
    return v;
}

//Запись элементов
void DoublyList::setAll(const std::vector<std::string>& v) {
    while (head) { Node* t = head; head = head->next; delete t; }
    tail = nullptr; cnt = 0;
    for (const std::string& x : v) push_back(x);
}
