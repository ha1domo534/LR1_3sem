#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <algorithm>
using namespace std;

// ============================================================
// 1. МАССИВ
// ============================================================
class Array {
    vector<int> data;
public:
    void push_back(int x) { data.push_back(x); }
    void push_at(int i, int x) {
        if (i < 0 || i > (int)data.size()) { cout << "-> ERROR: index\n"; return; }
        data.insert(data.begin() + i, x);
    }
    int get(int i) {
        if (i < 0 || i >= (int)data.size()) { cout << "-> ERROR: index\n"; return 0; }
        return data[i];
    }
    void del(int i) {
        if (i < 0 || i >= (int)data.size()) { cout << "-> ERROR: index\n"; return; }
        data.erase(data.begin() + i);
    }
    void set(int i, int x) {
        if (i < 0 || i >= (int)data.size()) { cout << "-> ERROR: index\n"; return; }
        data[i] = x;
    }
    int size() { return data.size(); }
    void print() {
        cout << "[";
        for (int i = 0; i < (int)data.size(); i++) {
            cout << data[i];
            if (i != (int)data.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }
    vector<int> all() { return data; }
    void setAll(const vector<int>& v) { data = v; }
};

// ============================================================
// 2. ОДНОСВЯЗНЫЙ СПИСОК
// ============================================================
class SinglyList {
    struct Node { int val; Node* next; Node(int v): val(v), next(nullptr) {} };
    Node* head = nullptr;
    int cnt = 0;
public:
    ~SinglyList() { clear(); }
    void clear() {
        while (head) { Node* t = head; head = head->next; delete t; }
        cnt = 0;
    }
    void push_front(int x) { Node* n = new Node(x); n->next = head; head = n; cnt++; }
    void push_back(int x) {
        Node* n = new Node(x);
        if (!head) { head = n; }
        else { Node* p = head; while (p->next) p = p->next; p->next = n; }
        cnt++;
    }
    void push_after(int target, int x) {
        Node* p = head;
        while (p && p->val != target) p = p->next;
        if (!p) { cout << "-> ERROR: not found\n"; return; }
        Node* n = new Node(x); n->next = p->next; p->next = n; cnt++;
    }
    void del_front() {
        if (!head) { cout << "-> ERROR: empty\n"; return; }
        Node* t = head; head = head->next; delete t; cnt--;
    }
    void del_back() {
        if (!head) { cout << "-> ERROR: empty\n"; return; }
        if (!head->next) { delete head; head = nullptr; cnt--; return; }
        Node* p = head;
        while (p->next->next) p = p->next;
        delete p->next; p->next = nullptr; cnt--;
    }
    void del_value(int x) {
        if (!head) { cout << "-> ERROR: empty\n"; return; }
        if (head->val == x) { del_front(); return; }
        Node* p = head;
        while (p->next && p->next->val != x) p = p->next;
        if (!p->next) { cout << "-> ERROR: not found\n"; return; }
        Node* t = p->next; p->next = t->next; delete t; cnt--;
    }
    bool find(int x) {
        Node* p = head;
        while (p) { if (p->val == x) return true; p = p->next; }
        return false;
    }
    int size() { return cnt; }
    void print() {
        cout << "[";
        Node* p = head; bool first = true;
        while (p) { if (!first) cout << ", "; cout << p->val; first = false; p = p->next; }
        cout << "]\n";
    }
    vector<int> all() {
        vector<int> v; Node* p = head;
        while (p) { v.push_back(p->val); p = p->next; }
        return v;
    }
    void setAll(const vector<int>& v) {
        clear();
        for (int x : v) push_back(x);
    }
};

// ============================================================
// 3. ДВУСВЯЗНЫЙ СПИСОК
// ============================================================
class DoublyList {
    struct Node { int val; Node* prev; Node* next; Node(int v): val(v), prev(nullptr), next(nullptr) {} };
    Node* head = nullptr;
    Node* tail = nullptr;
    int cnt = 0;
public:
    ~DoublyList() { clear(); }
    void clear() {
        while (head) { Node* t = head; head = head->next; delete t; }
        tail = nullptr; cnt = 0;
    }
    void push_front(int x) {
        Node* n = new Node(x);
        n->next = head;
        if (head) head->prev = n;
        head = n;
        if (!tail) tail = n;
        cnt++;
    }
    void push_back(int x) {
        Node* n = new Node(x);
        n->prev = tail;
        if (tail) tail->next = n;
        tail = n;
        if (!head) head = n;
        cnt++;
    }
    void push_after(int target, int x) {
        Node* p = head;
        while (p && p->val != target) p = p->next;
        if (!p) { cout << "-> ERROR: not found\n"; return; }
        Node* n = new Node(x);
        n->next = p->next; n->prev = p;
        if (p->next) p->next->prev = n;
        p->next = n;
        if (tail == p) tail = n;
        cnt++;
    }
    void del_front() {
        if (!head) { cout << "-> ERROR: empty\n"; return; }
        Node* t = head;
        head = head->next;
        if (head) head->prev = nullptr; else tail = nullptr;
        delete t; cnt--;
    }
    void del_back() {
        if (!tail) { cout << "-> ERROR: empty\n"; return; }
        Node* t = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr; else head = nullptr;
        delete t; cnt--;
    }
    void del_value(int x) {
        Node* p = head;
        while (p && p->val != x) p = p->next;
        if (!p) { cout << "-> ERROR: not found\n"; return; }
        if (p == head) { del_front(); return; }
        if (p == tail) { del_back(); return; }
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p; cnt--;
    }
    bool find(int x) {
        Node* p = head;
        while (p) { if (p->val == x) return true; p = p->next; }
        return false;
    }
    int size() { return cnt; }
    void print() {
        cout << "[";
        Node* p = head; bool first = true;
        while (p) { if (!first) cout << ", "; cout << p->val; first = false; p = p->next; }
        cout << "]\n";
    }
    vector<int> all() {
        vector<int> v; Node* p = head;
        while (p) { v.push_back(p->val); p = p->next; }
        return v;
    }
    void setAll(const vector<int>& v) {
        clear();
        for (int x : v) push_back(x);
    }
};

// ============================================================
// 4. СТЕК
// ============================================================
class Stack {
    vector<int> data;
public:
    void push(int x) { data.push_back(x); }
    void pop() {
        if (data.empty()) { cout << "-> ERROR: empty\n"; return; }
        cout << "-> " << data.back() << "\n";
        data.pop_back();
    }
    void peek() {
        if (data.empty()) { cout << "-> ERROR: empty\n"; return; }
        cout << "-> " << data.back() << "\n";
    }
    int size() { return data.size(); }
    void print() {
        cout << "[";
        for (int i = (int)data.size() - 1; i >= 0; i--) {
            cout << data[i];
            if (i != 0) cout << ", ";
        }
        cout << "]\n";
    }
    vector<int> all() { return data; }
    void setAll(const vector<int>& v) { data = v; }
};

// ============================================================
// 5. ОЧЕРЕДЬ
// ============================================================
class Queue {
    deque<int> data;
public:
    void push(int x) { data.push_back(x); }
    void pop() {
        if (data.empty()) { cout << "-> ERROR: empty\n"; return; }
        cout << "-> " << data.front() << "\n";
        data.pop_front();
    }
    void peek() {
        if (data.empty()) { cout << "-> ERROR: empty\n"; return; }
        cout << "-> " << data.front() << "\n";
    }
    int size() { return data.size(); }
    void print() {
        cout << "[";
        for (int i = 0; i < (int)data.size(); i++) {
            cout << data[i];
            if (i != (int)data.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }
    vector<int> all() { return vector<int>(data.begin(), data.end()); }
    void setAll(const vector<int>& v) { data = deque<int>(v.begin(), v.end()); }
};

// ============================================================
// 6. COMPLETE BINARY TREE (вариант 3)
// ============================================================
class CompleteBinaryTree {
    vector<int> data;   // храним в массиве, -1 = пусто (для дырок)
public:
    void insert(int x) { data.push_back(x); }   // всегда в конец

    bool find(int x) {
        for (int v : data) if (v == x) return true;
        return false;
    }

    bool isComplete() {
        bool seenEmpty = false;
        for (int v : data) {
            if (v == -1) seenEmpty = true;
            else if (seenEmpty) return false;
        }
        return true;
    }

    int size() { return data.size(); }

    void print() {
        // печатаем как массив + в виде "уровней"
        cout << "Array: [";
        for (int i = 0; i < (int)data.size(); i++) {
            cout << data[i];
            if (i != (int)data.size() - 1) cout << ", ";
        }
        cout << "]\n";
        // уровни
        cout << "Levels:\n";
        int idx = 0, level = 0, levelSize = 1;
        while (idx < (int)data.size()) {
            cout << "  L" << level << ": ";
            for (int i = 0; i < levelSize && idx < (int)data.size(); i++, idx++) {
                cout << data[idx] << " ";
            }
            cout << "\n";
            level++; levelSize *= 2;
        }
    }

    vector<int> all() { return data; }
    void setAll(const vector<int>& v) { data = v; }
};

// ============================================================
// ГЛОБАЛЬНЫЕ СЛОВАРИ
// ============================================================
map<string, Array> arrays;
map<string, SinglyList> flists;
map<string, DoublyList> llists;
map<string, Stack> stacks;
map<string, Queue> queues;
map<string, CompleteBinaryTree> trees;

// ============================================================
// ФАЙЛ: СОХРАНЕНИЕ / ЗАГРУЗКА
// ============================================================
void saveToFile(const string& path) {
    ofstream f(path);
    if (!f.is_open()) { cout << "-> ERROR: cannot write file\n"; return; }

    for (auto& p : arrays) {
        f << "ARRAY " << p.first;
        for (int x : p.second.all()) f << " " << x;
        f << "\n";
    }
    for (auto& p : flists) {
        f << "FLIST " << p.first;
        for (int x : p.second.all()) f << " " << x;
        f << "\n";
    }
    for (auto& p : llists) {
        f << "LLIST " << p.first;
        for (int x : p.second.all()) f << " " << x;
        f << "\n";
    }
    for (auto& p : stacks) {
        f << "STACK " << p.first;
        for (int x : p.second.all()) f << " " << x;
        f << "\n";
    }
    for (auto& p : queues) {
        f << "QUEUE " << p.first;
        for (int x : p.second.all()) f << " " << x;
        f << "\n";
    }
    for (auto& p : trees) {
        f << "TREE " << p.first;
        for (int x : p.second.all()) f << " " << x;
        f << "\n";
    }
    f.close();
}

void loadFromFile(const string& path) {
    ifstream f(path);
    if (!f.is_open()) return;
    string line;
    while (getline(f, line)) {
        istringstream iss(line);
        string type, name;
        if (!(iss >> type >> name)) continue;
        vector<int> v;
        int x;
        while (iss >> x) v.push_back(x);

        if (type == "ARRAY") arrays[name].setAll(v);
        else if (type == "FLIST") flists[name].setAll(v);
        else if (type == "LLIST") llists[name].setAll(v);
        else if (type == "STACK") stacks[name].setAll(v);
        else if (type == "QUEUE") queues[name].setAll(v);
        else if (type == "TREE") trees[name].setAll(v);
    }
    f.close();
}

// ============================================================
// ОБРАБОТКА КОМАНД
// ============================================================
void processCommand(const string& query) {
    istringstream iss(query);
    string cmd, name;
    if (!(iss >> cmd >> name)) { cout << "-> ERROR: empty command\n"; return; }

    vector<string> rest;
    string tok;
    while (iss >> tok) rest.push_back(tok);

    // ---------- МАССИВ ----------
    if (cmd == "MPUSH") {
        if (rest.size() == 1) { arrays[name].push_back(stoi(rest[0])); cout << "-> OK\n"; }
        else if (rest.size() == 2) { arrays[name].push_at(stoi(rest[0]), stoi(rest[1])); cout << "-> OK\n"; }
        else cout << "-> ERROR: MPUSH <name> <value> | <name> <idx> <value>\n";
        return;
    }
    if (cmd == "MGET") {
        if (rest.size() == 1) cout << "-> " << arrays[name].get(stoi(rest[0])) << "\n";
        else cout << "-> ERROR: MGET <name> <idx>\n";
        return;
    }
    if (cmd == "MDEL") {
        if (rest.size() == 1) { arrays[name].del(stoi(rest[0])); cout << "-> OK\n"; }
        else cout << "-> ERROR: MDEL <name> <idx>\n";
        return;
    }
    if (cmd == "MSET") {
        if (rest.size() == 2) { arrays[name].set(stoi(rest[0]), stoi(rest[1])); cout << "-> OK\n"; }
        else cout << "-> ERROR: MSET <name> <idx> <value>\n";
        return;
    }
    if (cmd == "MSIZE") { cout << "-> " << arrays[name].size() << "\n"; return; }

    // ---------- ОДНОСВЯЗНЫЙ СПИСОК ----------
    if (cmd == "FPUSH") {
        if (rest.size() == 1) { flists[name].push_back(stoi(rest[0])); cout << "-> OK\n"; }
        else if (rest.size() == 2) {
            string where = rest[0];
            int v = stoi(rest[1]);
            if (where == "front" || where == "head") flists[name].push_front(v);
            else if (where == "back" || where == "tail") flists[name].push_back(v);
            else { flists[name].push_after(stoi(where), v); }
            cout << "-> OK\n";
        }
        else cout << "-> ERROR: FPUSH <name> <value> | <name> front|back|target <value>\n";
        return;
    }
    if (cmd == "FDEL") {
        if (rest.size() == 1) {
            string what = rest[0];
            if (what == "front" || what == "head") flists[name].del_front();
            else if (what == "back" || what == "tail") flists[name].del_back();
            else flists[name].del_value(stoi(what));
            cout << "-> OK\n";
        }
        else cout << "-> ERROR: FDEL <name> front|back|value\n";
        return;
    }
    if (cmd == "FGET") {
        // FGET <name> <value> — поиск
        if (rest.size() == 1) {
            bool found = flists[name].find(stoi(rest[0]));
            cout << "-> " << (found ? "TRUE" : "FALSE") << "\n";
        }
        else cout << "-> ERROR: FGET <name> <value>\n";
        return;
    }
    if (cmd == "FSIZE") { cout << "-> " << flists[name].size() << "\n"; return; }

    // ---------- ДВУСВЯЗНЫЙ СПИСОК ----------
    if (cmd == "LPUSH") {
        if (rest.size() == 1) { llists[name].push_back(stoi(rest[0])); cout << "-> OK\n"; }
        else if (rest.size() == 2) {
            string where = rest[0];
            int v = stoi(rest[1]);
            if (where == "front" || where == "head") llists[name].push_front(v);
            else if (where == "back" || where == "tail") llists[name].push_back(v);
            else { llists[name].push_after(stoi(where), v); }
            cout << "-> OK\n";
        }
        else cout << "-> ERROR: LPUSH <name> <value> | <name> front|back|target <value>\n";
        return;
    }
    if (cmd == "LDEL") {
        if (rest.size() == 1) {
            string what = rest[0];
            if (what == "front" || what == "head") llists[name].del_front();
            else if (what == "back" || what == "tail") llists[name].del_back();
            else llists[name].del_value(stoi(what));
            cout << "-> OK\n";
        }
        else cout << "-> ERROR: LDEL <name> front|back|value\n";
        return;
    }
    if (cmd == "LGET") {
        if (rest.size() == 1) {
            bool found = llists[name].find(stoi(rest[0]));
            cout << "-> " << (found ? "TRUE" : "FALSE") << "\n";
        }
        else cout << "-> ERROR: LGET <name> <value>\n";
        return;
    }
    if (cmd == "LSIZE") { cout << "-> " << llists[name].size() << "\n"; return; }

    // ---------- СТЕК ----------
    if (cmd == "SPUSH") {
        if (rest.size() == 1) { stacks[name].push(stoi(rest[0])); cout << "-> OK\n"; }
        else cout << "-> ERROR: SPUSH <name> <value>\n";
        return;
    }
    if (cmd == "SPOP") { stacks[name].pop(); return; }
    if (cmd == "SPEEK") { stacks[name].peek(); return; }
    if (cmd == "SSIZE") { cout << "-> " << stacks[name].size() << "\n"; return; }

    // ---------- ОЧЕРЕДЬ ----------
    if (cmd == "QPUSH") {
        if (rest.size() == 1) { queues[name].push(stoi(rest[0])); cout << "-> OK\n"; }
        else cout << "-> ERROR: QPUSH <name> <value>\n";
        return;
    }
    if (cmd == "QPOP") { queues[name].pop(); return; }
    if (cmd == "QPEEK") { queues[name].peek(); return; }
    if (cmd == "QSIZE") { cout << "-> " << queues[name].size() << "\n"; return; }

    // ---------- ДЕРЕВО (Complete Binary Tree) ----------
    if (cmd == "TINSERT") {
        if (rest.size() == 1) { trees[name].insert(stoi(rest[0])); cout << "-> OK\n"; }
        else cout << "-> ERROR: TINSERT <name> <value>\n";
        return;
    }
    if (cmd == "TGET" || cmd == "ISMEMBER") {
        if (rest.size() == 1) {
            bool found = trees[name].find(stoi(rest[0]));
            cout << "-> " << (found ? "TRUE" : "FALSE") << "\n";
        }
        else cout << "-> ERROR: TGET <name> <value>\n";
        return;
    }
    if (cmd == "TCHECK" || cmd == "TISCOMPLETE") {
        bool ok = trees[name].isComplete();
        cout << "-> " << (ok ? "TRUE" : "FALSE") << "\n";
        return;
    }
    if (cmd == "TSIZE") { cout << "-> " << trees[name].size() << "\n"; return; }

    // ---------- PRINT ----------
    if (cmd == "PRINT") {
        // ищем имя во всех словарях
        if (arrays.count(name))  { arrays[name].print();  return; }
        if (flists.count(name))  { flists[name].print();  return; }
        if (llists.count(name))  { llists[name].print();  return; }
        if (stacks.count(name))  { stacks[name].print();  return; }
        if (queues.count(name))  { queues[name].print();  return; }
        if (trees.count(name))   { trees[name].print();   return; }
        cout << "-> ERROR: '" << name << "' not found\n";
        return;
    }

    cout << "-> ERROR: unknown command '" << cmd << "'\n";
}

// ============================================================
// MAIN
// ============================================================
int main(int argc, char* argv[]) {
    string filePath, query;

    for (int i = 1; i < argc; i++) {
        string a = argv[i];
        if (a == "--file" && i + 1 < argc) filePath = argv[++i];
        else if (a == "--query" && i + 1 < argc) query = argv[++i];
    }

    if (filePath.empty() || query.empty()) {
        cout << "Usage: ./dbms --file <file> --query '<command>'\n";
        return 1;
    }

    loadFromFile(filePath);
    processCommand(query);
    saveToFile(filePath);

    return 0;
}
