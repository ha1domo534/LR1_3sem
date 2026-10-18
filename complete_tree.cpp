#include "complete_tree.h"

void CompleteBinaryTree::insert(const std::string& x) { data.push_back(x); }

bool CompleteBinaryTree::find(const std::string& x) {
    for (const std::string& v : data) if (v == x) return true;
    return false;
}

bool CompleteBinaryTree::isComplete() {
    bool seenEmpty = false;
    for (const std::string& v : data) {
        if (v == "NULL") seenEmpty = true;
        else if (seenEmpty) return false;
    }
    return true;
}

int CompleteBinaryTree::size() { return data.size(); }

void CompleteBinaryTree::print() {
    std::cout << "Array: [";
    for (int i = 0; i < (int)data.size(); i++) {
        std::cout << data[i];
        if (i != (int)data.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    std::cout << "Levels:\n";
    int idx = 0, level = 0, levelSize = 1;
    while (idx < (int)data.size()) {
        std::cout << "  L" << level << ": ";
        for (int i = 0; i < levelSize && idx < (int)data.size(); i++, idx++) {
            std::cout << data[idx] << " ";
        }
        std::cout << "\n";
        level++; levelSize *= 2;
    }
}

std::vector<std::string> CompleteBinaryTree::all() { return data; }

void CompleteBinaryTree::setAll(const std::vector<std::string>& v) { data = v; }