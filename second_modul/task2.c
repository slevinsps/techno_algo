#include <iostream>
#include <stdlib.h>
#include <stack>
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

Node *GetNewNode(int value, Node *parent) {
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}

void insert(Node **head, int value) {
    Node *tmp = NULL;
    if (*head == NULL) {
        *head = GetNewNode(value, NULL);
        return;
    }
    tmp = *head;
    while (tmp) {
        if (value > tmp->data) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            } else {
                tmp->right = GetNewNode(value, tmp);
                return;
            }
        } else if (value < tmp->data) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = GetNewNode(value, tmp);
                return;
            }
        } else {
            break;
        }
    }
}

void inOrderTravers(Node *root) {
    /*if (root) {
        inOrderTravers(root->left);
        printf("%d ", root->data);
        inOrderTravers(root->right);
    }*/
    Node *tmp = root;
    std::stack<Node *> stack;
    stack.push(nullptr);
    do {
        while (tmp) {
            stack.push(tmp);
            tmp = tmp->left;
        }
        tmp = stack.top();
        stack.pop();
        if (tmp) {
            std::cout << tmp->data << " ";
            tmp = tmp->right;
        }

    } while (!stack.empty());
}

void free_tree(Node* head) {
    if (!head) return;
    free_tree(head->left);
    free_tree(head->right);
    free(head);
}

int main() {
    int n = 0;
    int a;
    Node *head = NULL;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a;
        insert(&head, a);
    }
    inOrderTravers(head);
    free_tree(head);
}
