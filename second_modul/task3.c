#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <algorithm>

typedef struct Node {
    int key;
    int priority;
    struct Node* right;
    struct Node* left;
    explicit Node() {
        key = 0;
        priority = 0;
        right = nullptr;
        left = nullptr;
    }
} Node;

Node* GetNewNode(int value, int priority) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->key = value;
    tmp->priority = priority;
    return tmp;
}
void Insert(Node*& head, Node* insert_node) {
    if (head == NULL) {
        head = insert_node;
        return;
    }
    if (head->key < insert_node->key) {
        Insert(head->right, insert_node);
    } else {
        Insert(head->left, insert_node);
    }
}

void free_tree(Node* head) {
    if (!head) return;
    free_tree(head->left);
    free_tree(head->right);
    free(head);
}

class DecardTree {
public:
    DecardTree() : head(nullptr) {}
    DecardTree(const DecardTree&) = delete;
    DecardTree(DecardTree&&) = delete;
    DecardTree& operator=(const DecardTree&) = delete;
    DecardTree& operator=(const DecardTree&&) = delete;
    ~DecardTree() {
        FreeTree();
    };

    void Insert(const int value, const int priority) {
        Node* ins = GetNewNode(value, priority);
        InsertDecard(head, ins);
    }

    void CountVertexes(std::vector<int>& counts, int i) {
        CountVertexesDecard(head, counts, i);
    }

    void FreeTree() {
        FreeTreeDecard(head);
    }

private:
    struct Node {
        int key;
        int priority;
        struct Node* right;
        struct Node* left;
        explicit Node() {
            key = 0;
            priority = 0;
            right = nullptr;
            left = nullptr;
        }
    };

    void FreeTreeDecard(Node* head) {
        if (!head) return;
        FreeTreeDecard(head->left);
        FreeTreeDecard(head->right);
        free(head);
    }

    void CountVertexesDecard(Node* head, std::vector<int>& counts, int i) {
        if (head == NULL) {
            return;
        }
        counts[i]++;
        CountVertexesDecard(head->right, counts, i + 1);
        CountVertexesDecard(head->left, counts, i + 1);
    }

    Node* GetNewNode(int value, int priority) {
        Node* tmp = (Node*)malloc(sizeof(Node));
        tmp->left = tmp->right = NULL;
        tmp->key = value;
        tmp->priority = priority;
        return tmp;
    }

    void InsertDecard(Node*& head, Node*& insert_node) {
        if (!head) {
            head = insert_node;
        } else if (head->priority < insert_node->priority) {
            Split(head, insert_node->key, insert_node->left, insert_node->right);
            head = insert_node;
        } else {
            if (head->key > insert_node->key) {
                InsertDecard(head->left, insert_node);
            } else {
                InsertDecard(head->right, insert_node);
            }
        }
    }

    void Split(Node* currentNode, int key, Node*& left, Node*& right) {
        if (currentNode == 0) {
            left = 0;
            right = 0;
        } else if (currentNode->key <= key) {
            Split(currentNode->right, key, currentNode->right, right);
            left = currentNode;
        } else {
            Split(currentNode->left, key, left, currentNode->left);
            right = currentNode;
        }
    }

    Node* Merge(Node* left, Node* right) {
        if (left == 0 || right == 0) {
            return left == 0 ? right : left;
        }
        if (left->priority > right->priority) {
            left->right = Merge(left->right, right);
            return left;
        } else {
            right->left = Merge(left, right->left);
            return right;
        }
    }

    Node* head;
};

void count_vertexes(Node* head, std::vector<int>& counts, int i) {
    if (head == NULL) {
        return;
    }
    counts[i]++;
    count_vertexes(head->right, counts, i + 1);
    count_vertexes(head->left, counts, i + 1);
}

int main() {
    Node* head = nullptr;
    DecardTree decard_tree;
    srand(time(NULL));

    int n = 0;
    int x = 0, y = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> x >> y;
        decard_tree.Insert(x, y);
        Node* tmp = GetNewNode(x, 0);
        Insert(head, tmp);
    }
    int i = 0;
    std::vector<int> vect(n, 0);
    count_vertexes(head, vect, i);
    i = 0;
    std::vector<int> vect_decard(n, 0);
    decard_tree.CountVertexes(vect_decard, i);

    std::vector<int>::iterator max_nodes, max_nodes_decard;
    max_nodes = std::max_element(vect.begin(), vect.end());
    max_nodes_decard = std::max_element(vect_decard.begin(), vect_decard.end());
    std::cout << *max_nodes_decard - *max_nodes;
    vect.clear();
    vect_decard.clear();
    free_tree(head);
}
