#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include "array.h"
#include "list.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "complete_tree.h"

using namespace std;

map<string, Array> arrays;
map<string, SinglyList> flists;
map<string, DoublyList> llists;
map<string, Stack> stacks;
map<string, Queue> queues;
map<string, CompleteBinaryTree> trees;

void saveToFile(const string& path) {
    ofstream f(path);
    if (!f.is_open()) return;
    
    for (auto& p : arrays) {
        f << "ARRAY " << p.first;
        for (const string& x : p.second.all()) f << " " << x;
        f << "\n";
    }
    for (auto& p : flists) {
        f << "FLIST " << p.first;
        for (const string& x : p.second.all()) f << " " << x;
        f << "\n";
    }
    for (auto& p : llists) {
        f << "LLIST " << p.first;
        for (const string& x : p.second.all()) f << " " << x;
        f << "\n";
    }
    for (auto& p : stacks) {
        f << "STACK " << p.first;
        for (const string& x : p.second.all()) f << " " << x;
        f << "\n";
    }
    for (auto& p : queues) {
        f << "QUEUE " << p.first;
        for (const string& x : p.second.all()) f << " " << x;
        f << "\n";
    }
    for (auto& p : trees) {
        f << "TREE " << p.first;
        for (const string& x : p.second.all()) f << " " << x;
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
        vector<string> v;
        string x;
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

void processCommand(const string& query) {
    istringstream iss(query);
    string cmd, name;
    if (!(iss >> cmd >> name)) { cout << "-> ERROR: empty command\n"; return; }

    if (cmd == "MCREATE") {
        if (arrays.count(name)) { cout << "-> ERROR: array exists\n"; return; }
        arrays[name] = Array(); cout << "-> OK\n"; return;
    }
    if (cmd == "FCREATE") {
        if (flists.count(name)) { cout << "-> ERROR: list exists\n"; return; }
        flists[name] = SinglyList(); cout << "-> OK\n"; return;
    }
    if (cmd == "LCREATE") {
        if (llists.count(name)) { cout << "-> ERROR: list exists\n"; return; }
        llists[name] = DoublyList(); cout << "-> OK\n"; return;
    }
    if (cmd == "SCREATE") {
        if (stacks.count(name)) { cout << "-> ERROR: stack exists\n"; return; }
        stacks[name] = Stack(); cout << "-> OK\n"; return;
    }
    if (cmd == "QCREATE") {
        if (queues.count(name)) { cout << "-> ERROR: queue exists\n"; return; }
        queues[name] = Queue(); cout << "-> OK\n"; return;
    }
    if (cmd == "TCREATE") {
        if (trees.count(name)) { cout << "-> ERROR: tree exists\n"; return; }
        trees[name] = CompleteBinaryTree(); cout << "-> OK\n"; return;
    }

    vector<string> rest;
    string tok;
    while (iss >> tok) rest.push_back(tok);

    if (cmd == "MPUSH") {
        if (rest.size() == 1) { arrays[name].push_back(rest[0]); cout << "-> " << rest[0] << "\n"; }
        else if (rest.size() == 2) { arrays[name].push_at(stoi(rest[0]), rest[1]); cout << "-> " << rest[1] << "\n"; }
        else cout << "-> ERROR: format\n";
        return;
    }
    if (cmd == "MGET") {
        if (rest.size() == 1) cout << "-> " << arrays[name].get(stoi(rest[0])) << "\n";
        else cout << "-> ERROR: format\n";
        return;
    }
    if (cmd == "MDEL") {
        if (rest.size() == 1) { arrays[name].del(stoi(rest[0])); cout << "-> OK\n"; }
        else cout << "-> ERROR: format\n";
        return;
    }
    if (cmd == "MSET") {
        if (rest.size() == 2) { arrays[name].set(stoi(rest[0]), rest[1]); cout << "-> OK\n"; }
        else cout << "-> ERROR: format\n";
        return;
    }
    if (cmd == "MSIZE") { cout << "-> " << arrays[name].size() << "\n"; return; }

    if (cmd == "FPUSHHEAD") {
        if (rest.size() == 1) { flists[name].push_front(rest[0]); cout << "-> " << rest[0] << "\n"; }
        else cout << "-> Ошибка: неверное количество аргументов для FPUSHHEAD\n";
        return;
    }
    if (cmd == "FPUSHTAIL") {
        if (rest.size() == 1) { flists[name].push_back(rest[0]); cout << "-> " << rest[0] << "\n"; }
        else cout << "-> Ошибка: неверное количество аргументов для FPUSHTAIL\n";
        return;
    }
    if (cmd == "FPUSHBEFORE") {
        if (rest.size() == 2) { flists[name].push_before(rest[0], rest[1]); cout << "-> " << rest[1] << "\n"; }
        else cout << "-> Ошибка: неверное количество аргументов для FPUSHBEFORE\n";
        return;
    }
    if (cmd == "FPUSHAFTER") {
        if (rest.size() == 2) { flists[name].push_after(rest[0], rest[1]); cout << "-> " << rest[1] << "\n"; }
        else cout << "-> Ошибка: неверное количество аргументов для FPUSHAFTER\n";
        return;
    }
    if (cmd == "FDELHEAD") { flists[name].del_front(); cout << "-> OK\n"; return; }
    if (cmd == "FDELTAIL") { flists[name].del_back(); cout << "-> OK\n"; return; }
    if (cmd == "FDELVAL") {
        if (rest.size() == 1) { flists[name].del_value(rest[0]); cout << "-> OK\n"; }
        else cout << "-> ERROR: format\n";
        return;
    }
    if (cmd == "FGET") {
        if (rest.size() == 1) {
            bool found = flists[name].find(rest[0]);
            cout << "-> " << (found ? "TRUE" : "FALSE") << "\n";
        }
        else cout << "-> ERROR: format\n";
        return;
    }
    if (cmd == "FSIZE") { cout << "-> " << flists[name].size() << "\n"; return; }

    if (cmd == "LPUSHHEAD") {
        if (rest.size() == 1) { llists[name].push_front(rest[0]); cout << "-> " << rest[0] << "\n"; }
        else cout << "-> Ошибка: неверное количество аргументов для LPUSHHEAD\n";
        return;
    }
    if (cmd == "LPUSHTAIL") {
        if (rest.size() == 1) { llists[name].push_back(rest[0]); cout << "-> " << rest[0] << "\n"; }
        else cout << "-> Ошибка: неверное количество аргументов для LPUSHTAIL\n";
        return;
    }
    if (cmd == "LPUSHBEFORE") {
        if (rest.size() == 2) { llists[name].push_before(rest[0], rest[1]); cout << "-> " << rest[1] << "\n"; }
        else cout << "-> Ошибка: неверное количество аргументов для LPUSHBEFORE\n";
        return;
    }
    if (cmd == "LPUSHAFTER") {
        if (rest.size() == 2) { llists[name].push_after(rest[0], rest[1]); cout << "-> " << rest[1] << "\n"; }
        else cout << "-> Ошибка: неверное количество аргументов для LPUSHAFTER\n";
        return;
    }
    if (cmd == "LDELHEAD") { llists[name].del_front(); cout << "-> OK\n"; return; }
    if (cmd == "LDELTAIL") { llists[name].del_back(); cout << "-> OK\n"; return; }
    if (cmd == "LDELVAL") {
        if (rest.size() == 1) { llists[name].del_value(rest[0]); cout << "-> OK\n"; }
        else cout << "-> ERROR: format\n";
        return;
    }
    if (cmd == "LGET") {
        if (rest.size() == 1) {
            bool found = llists[name].find(rest[0]);
            cout << "-> " << (found ? "TRUE" : "FALSE") << "\n";
        }
        else cout << "-> ERROR: format\n";
        return;
    }
    if (cmd == "LSIZE") { cout << "-> " << llists[name].size() << "\n"; return; }

    if (cmd == "SPUSH") {
        if (rest.size() == 1) { stacks[name].push(rest[0]); cout << "-> " << rest[0] << "\n"; }
        else cout << "-> ERROR: format\n";
        return;
    }
    if (cmd == "SPOP") { stacks[name].pop(); return; }
    if (cmd == "SPEEK") { stacks[name].peek(); return; }
    if (cmd == "SSIZE") { cout << "-> " << stacks[name].size() << "\n"; return; }

    if (cmd == "QPUSH") {
        if (rest.size() == 1) { queues[name].push(rest[0]); cout << "-> " << rest[0] << "\n"; }
        else cout << "-> ERROR: format\n";
        return;
    }
    if (cmd == "QPOP") { queues[name].pop(); return; }
    if (cmd == "QPEEK") { queues[name].peek(); return; }
    if (cmd == "QSIZE") { cout << "-> " << queues[name].size() << "\n"; return; }

    if (cmd == "TINSERT") {
        if (rest.size() == 1) { trees[name].insert(rest[0]); cout << "-> OK\n"; }
        else cout << "-> ERROR: format\n";
        return;
    }
    if (cmd == "TGET" || cmd == "ISMEMBER") {
        if (rest.size() == 1) {
            bool found = trees[name].find(rest[0]);
            cout << "-> " << (found ? "TRUE" : "FALSE") << "\n";
        }
        else cout << "-> ERROR: format\n";
        return;
    }
    if (cmd == "TCHECK" || cmd == "TISCOMPLETE") {
        bool ok = trees[name].isComplete();
        cout << "-> " << (ok ? "TRUE" : "FALSE") << "\n";
        return;
    }
    if (cmd == "TSIZE") { cout << "-> " << trees[name].size() << "\n"; return; }

    if (cmd == "PRINT") {
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

int main(int argc, char* argv[]) {
    string filePath, query;

    for (int i = 1; i < argc; i++) {
        string a = argv[i];
        if (a == "--file" && i + 1 < argc) filePath = argv[++i];
        else if (a == "--query" && i + 1 < argc) query = argv[++i];
    }

    if (filePath.empty() || query.empty()) {
        cout << "Usage: ./LR1 --file <file> --query '<command>'\n";
        return 1;
    }

    loadFromFile(filePath);
    processCommand(query);
    saveToFile(filePath);

    return 0;
}
