#include "list.h"

//Конструктор
SinglyList::SinglyList() : head(nullptr), cnt(0) {}

//Деструктор
SinglyList::~SinglyList() {
    while (head) { Node* t = head; head = head->next; delete t; }
}

//Добавление в начало
void SinglyList::push_front(const std::string& x) {
    Node* n = new Node(x); n->next = head; head = n; cnt++;
}

//Добавление в конец
void SinglyList::push_back(const std::string& x) {
    Node* n = new Node(x);
    if (!head) { head = n; }
    else { Node* p = head; while (p->next) p = p->next; p->next = n; }
    cnt++;
}

//Вставка перед
void SinglyList::push_before(const std::string& target, const std::string& x) {
    if (!head) return;
    if (head->val == target) { push_front(x); return; }
    Node* p = head;
    while (p->next && p->next->val != target) p = p->next;
    if (!p->next) return;
    Node* n = new Node(x); n->next = p->next; p->next = n; cnt++;
}

//Вставка после
void SinglyList::push_after(const std::string& target, const std::string& x) {
    Node* p = head;
    while (p && p->val != target) p = p->next;
    if (!p) return;
    Node* n = new Node(x); n->next = p->next; p->next = n; cnt++;
}

//Удаление из начала
void SinglyList::del_front() {
    if (!head) return;
    Node* t = head; head = head->next; delete t; cnt--;
}

//Удаление из конца
void SinglyList::del_back() {
    if (!head) return;
    if (!head->next) { delete head; head = nullptr; cnt--; return; }
    Node* p = head;
    while (p->next->next) p = p->next;
    delete p->next; p->next = nullptr; cnt--;
}

//Удаление перед 
void SinglyList::del_before(const std::string& target) {
    if (!head || head->val == target || !head->next) return;
    if (head->next->val == target) { del_front(); return; }
    Node* p = head;
    while (p->next->next && p->next->next->val != target) p = p->next;
    if (!p->next->next) return;
    Node* t = p->next; p->next = t->next; delete t; cnt--;
}

//Удаление после 
void SinglyList::del_after(const std::string& target) {
    Node* p = head;
    while (p && p->val != target) p = p->next;
    if (!p || !p->next) return;
    Node* t = p->next; p->next = t->next; delete t; cnt--;
}

//Удаление по значению
void SinglyList::del_value(const std::string& x) {
    if (!head) return;
    if (head->val == x) { del_front(); return; }
    Node* p = head;
    while (p->next && p->next->val != x) p = p->next;
    if (!p->next) return;
    Node* t = p->next; p->next = t->next; delete t; cnt--;
}

//Поиск
bool SinglyList::find(const std::string& x) {
    Node* p = head;
    while (p) { if (p->val == x) return true; p = p->next; }
    return false;
}

//Получение по индексу 
std::string SinglyList::get_at(int index) {
    if (index < 0) return "";
    Node* p = head;
    for (int i = 0; i < index && p; i++) p = p->next;
    return p ? p->val : "";
}

//Размер
int SinglyList::size() { return cnt; }

//Вывод
void SinglyList::print() {
    Node* p = head;
    while (p) { std::cout << p->val << " "; p = p->next; }
    std::cout << "\n";
}

//Получение элементов
std::vector<std::string> SinglyList::all() {
    std::vector<std::string> v; Node* p = head;
    while (p) { v.push_back(p->val); p = p->next; }
    return v;
}

//Запись элементов
void SinglyList::setAll(const std::vector<std::string>& v) {
    while (head) { Node* t = head; head = head->next; delete t; }
    cnt = 0;
    for (const std::string& x : v) push_back(x);
}
