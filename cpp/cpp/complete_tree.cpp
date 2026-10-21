#include "complete_tree.h"
#include <queue>

//Oчистка памяти 
CompleteBinaryTree::~CompleteBinaryTree() {
    destroyTree(root);
}

// удаление дерева
void CompleteBinaryTree::destroyTree(Node* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

//Поиск указателя
CompleteBinaryTree::Node* CompleteBinaryTree::findNodePtr(Node* node, const std::string& x) {
    if (!node) return nullptr;
    if (node->val == x) return node;
    Node* leftRes = findNodePtr(node->left, x);
    if (leftRes) return leftRes;
    return findNodePtr(node->right, x);
}

//Добавление элемента 
void CompleteBinaryTree::insert(const std::string& x) {
    Node* newNode = new Node(x);
    
    if (!root) {
        root = newNode;
        cnt++;
        return;
    }

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (!current->left) {
            current->left = newNode;
            cnt++;
            break;
        } else {
            q.push(current->left);
        }

        if (!current->right) {
            current->right = newNode;
            cnt++;
            break;
        } else {
            q.push(current->right);
        }
    }
}

//TBREAK
bool CompleteBinaryTree::forceInsert(const std::string& parentVal, char side, const std::string& childVal) {
    Node* parent = findNodePtr(root, parentVal);
    if (!parent) return false;

    if (side == 'L' && !parent->left) {
        parent->left = new Node(childVal);
        cnt++;
        return true;
    } else if (side == 'R' && !parent->right) {
        parent->right = new Node(childVal);
        cnt++;
        return true;
    }
    return false;
}

//Поиск по значению
bool CompleteBinaryTree::find(const std::string& x) {
    return findNodePtr(root, x) != nullptr;
}

//Complete
bool CompleteBinaryTree::check() {
    if (!root) return true; 

    std::queue<Node*> q;
    q.push(root);
    bool seenEmpty = false;

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (current->left) {
            if (seenEmpty) return false; 
            q.push(current->left);
        } else {
            seenEmpty = true;
        }

        if (current->right) {
            if (seenEmpty) return false; 
            q.push(current->right);
        } else {
            seenEmpty = true;
        }
    }
    return true;
}

// размер
int CompleteBinaryTree::size() {
    return cnt;
}

//Вывод 
void CompleteBinaryTree::print() {
    if (!root) {
        std::cout << "Tree is empty\n";
        return;
    }

    std::queue<Node*> q;
    q.push(root);
    int level = 0;
    int nodesInCurrentLevel = 1;

    std::cout << "Levels:\n";
    while (!q.empty()) {
        std::cout << "  L" << level << ": ";
        int nodesInNextLevel = 0;
        
        for (int i = 0; i < nodesInCurrentLevel; i++) {
            Node* current = q.front();
            q.pop();
            std::cout << current->val << " ";

            if (current->left) {
                q.push(current->left);
                nodesInNextLevel++;
            }
            if (current->right) {
                q.push(current->right);
                nodesInNextLevel++;
            }
        }
        std::cout << "\n";
        nodesInCurrentLevel = nodesInNextLevel;
        level++;
    }
}

//Получение элементов 
std::vector<std::string> CompleteBinaryTree::all() {
    std::vector<std::string> result;
    if (!root) return result;

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();

        if (cur == nullptr) {
            result.push_back("N");
            continue;
        }
        result.push_back(cur->val);
        q.push(cur->left);
        q.push(cur->right);
    }

    while (result.size() >= 2 && result.back() == "N") {
        result.pop_back();
    }
    return result;
}

//Запись элементов 
void CompleteBinaryTree::setAll(const std::vector<std::string>& v) {
    destroyTree(root);
    root = nullptr;
    cnt = 0;
    if (v.empty()) return;

    root = new Node(v[0]);
    cnt = 1;

    std::queue<Node*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < (int)v.size()) {
        Node* cur = q.front();
        q.pop();

        if (i < (int)v.size() && v[i] != "N") {
            cur->left = new Node(v[i]);
            q.push(cur->left);
            cnt++;
        }
        i++;

        if (i < (int)v.size() && v[i] != "N") {
            cur->right = new Node(v[i]);
            q.push(cur->right);
            cnt++;
        }
        i++;
    }
}