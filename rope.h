#include <iostream>
#include <string>
#include <memory>
using namespace std;
// https://www.geeksforgeeks.org/ropes-data-structure-fast-string-concatenation/
// https://iq.opengenus.org/rope-data-structure/
// https://www.geeksforgeeks.org/stl-ropes-in-c/
// https://www.boost.org/sgi/stl/Rope.html
// https://github.com/alaroldai/cpp-rope
// https://cplusplus.com/reference/memory/shared_ptr/
class Rope {
private:
    struct Node {
        shared_ptr<Node> left;
        shared_ptr<Node> right;
        int weight;
        string data;
        Node(const string& s) : data(s), weight(s.length()) {}
    };

    shared_ptr<Node> root;

    char access(shared_ptr<Node>& node, int i) {
        if (!node) {
            throw out_of_range("Index out of bounds");
        }

        int leftWeight = node->left ? node->left->weight : 0;

        if (i < leftWeight) {
            return access(node->left, i);
        } else if (i < leftWeight + node->data.length()) {
            return node->data[i - leftWeight];
        } else {
            return access(node->right, i - leftWeight - node->data.length());
        }
    }

    shared_ptr<Node> concat(shared_ptr<Node> leftNode, shared_ptr<Node> rightNode) {
        if (!leftNode) return rightNode;
        if (!rightNode) return leftNode;

        shared_ptr<Node> newNode = make_shared<Node>("");
        newNode->left = leftNode;
        newNode->right = rightNode;
        newNode->weight = leftNode->weight + rightNode->weight;
        return newNode;
    }

    pair<shared_ptr<Node>, shared_ptr<Node>> splitHelper(shared_ptr<Node> node, int splitIndex) {
        if (!node) {
            return {nullptr, nullptr};
        }

        int leftWeight = node->left ? node->left->weight : 0;

        if (splitIndex <= leftWeight) {
            auto splitResult = splitHelper(node->left, splitIndex);
            node->left = splitResult.second;
            return {splitResult.first, node};
        } else {
            auto splitResult = splitHelper(node->right, splitIndex - leftWeight - node->data.length());
            node->right = splitResult.first;
            return {node, splitResult.second};
        }
    }

public:
    Rope(const string& s) {
        root = make_shared<Node>(s);
    }

    int getLength() {
        return root->weight;
    }

    char access(int i) {
        return access(root, i);
    }

    shared_ptr<Node> deleteHelper(shared_ptr<Node> node, int start, int length) {
        if (!node) {
            return nullptr;
        }

        int leftWeight = node->left ? node->left->weight : 0;

        if (start < leftWeight) {
            node->left = deleteHelper(node->left, start, length);
        } else if (start >= leftWeight + node->data.length()) {
            node->right = deleteHelper(node->right, start - leftWeight - node->data.length(), length);
        } else {
            int startIdx = max(0, start - leftWeight);
            size_t removeLength = min(static_cast<size_t>(node->data.length() - startIdx), static_cast<size_t>(length));
            node->data.erase(startIdx, removeLength);
            node->weight -= removeLength;
        }

        return node;
    }

    void deleteRope(int start, int length) {
        if (start < 0 || start >= root->weight || length <= 0) {
            return;
        }
        root = deleteHelper(root, start, length);
    }

    void concat(const Rope& s2) {
        root = concat(root, s2.root);
    }

    void split(int i) {
        if (i < 0 || i > root->weight) {
            return;
        }

        auto splitResult = splitHelper(root, i);
        root = splitResult.first;
    }

    void insert(int i, const string& s) {
        if (i < 0 || i > root->weight) {
            return;
        }

        auto insertNode = make_shared<Node>(s);

        auto splitResult = splitHelper(root, i);

        root = concat(concat(splitResult.first, insertNode), splitResult.second);
        root->weight += s.length();
    }

    string subrope(int i, int j) {
        if (i < 1 || j < i || j > root->weight + 1) {
            return "";
        }
        i--;
        string result;
        subropeHelper(root, i, j, result);

        return result;
    }

    void subropeHelper(shared_ptr<Node> node, int i, int j, string &result) {
        if (!node || result.length() >= j) {
            return;
        }

        int leftWeight = node->left ? node->left->weight : 0;

        if (i < leftWeight) {
            subropeHelper(node->left, i, j, result);
        }

        if (i <= leftWeight && leftWeight < j) {
            int startIdx = max(0, i - leftWeight);
            int length = min(static_cast<int>(node->data.length()) - startIdx, j - leftWeight);
            result += node->data.substr(startIdx, length);
        }

        if (leftWeight < j) {
            subropeHelper(node->right, i - leftWeight - 1, j - leftWeight - 1, result);
        }
    }
};
