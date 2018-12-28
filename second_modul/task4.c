#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <time.h>
#include <ctime>

class AVLTree {
    struct Node // структура для представления узлов дерева
    {
        int key;
        unsigned char height;
        unsigned int l_nodes;
        unsigned int r_nodes;
        struct Node* left;
        struct Node* right;
        Node(int data) { key = data; left = right = nullptr; r_nodes = 0; l_nodes = 0; height = 1; }
    };
public:
    AVLTree() : head(nullptr) {}
    AVLTree(const AVLTree&) = delete;
    AVLTree(AVLTree&&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&&) = delete;
    ~AVLTree() {
        free_tree(head);
    }

    void InsertAvl(int insert, int& pos) {
        Node* ins = GetNewNode(insert);
        head = this->Insert(head, ins, pos);
    }

    void RemoveAvl(int rem) {
        head = this->Remove(head, rem);
    }


private:
    unsigned char Height(Node* node)
    {
        return node ? node->height : 0;
    }

    int BalanceFactor(Node* node)
    {
        return Height(node->right)-Height(node->left);
    }

    void CountHeight(Node* node)
    {
        unsigned char hl = Height(node->left);
        unsigned char hr = Height(node->right);
        node->height = (hl > hr ? hl : hr) + 1;
    }

    void CountNodes(Node* node)
    {
        node->l_nodes = node->left  ? node->left->l_nodes + node->left->r_nodes  + 1 : 0;
        node->r_nodes = node->right  ? node->right->l_nodes + node->right->r_nodes  + 1: 0;
    }

    Node* Rotateright(Node* node)
    {
        Node* q = node->left;
        node->left = q->right;
        q->right = node;
        CountHeight(node);
        CountHeight(q);

        CountNodes(node);
        CountNodes(q);

        return q;
    }

    Node* Rotateleft(Node* node)
    {
        Node* p = node->right;
        node->right = p->left;
        p->left = node;
        CountHeight(node);
        CountHeight(p);

        CountNodes(node);
        CountNodes(p);

        return p;
    }

    Node* Balance(Node* node)
    {
        CountHeight(node);
        CountNodes(node);
        if( BalanceFactor(node)==2 )
        {
            if( BalanceFactor(node->right) < 0 )
                node->right = Rotateright(node->right);
            return Rotateleft(node);
        }
        if( BalanceFactor(node)==-2 )
        {
            if( BalanceFactor(node->left) > 0  )
                node->left = Rotateleft(node->left);
            return Rotateright(node);
        }
        return node;
    }



    Node* Insert(Node* node, Node* k, int& pos)
    {
        if( !node ) return k;
        if( k->key <= node->key ) {
            pos += node->r_nodes + 1;
            node->left = Insert(node->left, k, pos);
        } else {
            node->right = Insert(node->right, k, pos);
        }
        return Balance(node);
    }


    Node* Findmin(Node* node)
    {
        return node->left ? Findmin(node->left) : node;
    }


    Node* Removemin(Node* node)
    {
        if(node->left == 0) {
            return node->right;
        }
        node->left = Removemin(node->left);
        return Balance(node);
    }

    Node* Remove(Node* node, int k)
    {
        if( !node ) return nullptr;
        if( k > node->r_nodes ) {
            node->left = Remove(node->left, k - node->r_nodes - 1);
        }
        else if( k < node->r_nodes ) {
            node->right = Remove(node->right, k);
        }
        else
        {
            Node* q = node->left;
            Node* r = node->right;

            delete node;
            if( !r ) {
                return q;
            }
            Node* min = Findmin(r);
            min->right = Removemin(r);
            min->left = q;
            return Balance(min);
        }
        return Balance(node);
    }

    Node* GetNewNode(int value) {
        Node* tmp = new Node(value);
        tmp->left = nullptr;
        tmp->right = nullptr;
        return tmp;
    }

    void inOrder(Node* head) {
        if (head == nullptr) return;
        inOrder(head->left);
        std::cout << head->key << " " << head->l_nodes << " " << head->r_nodes << "; ";
        inOrder(head->right);
    }

    void free_tree(Node* head) {
        if (!head) return;
        free_tree(head->left);
        free_tree(head->right);
        free(head);
    }

private:
    Node* head;
};


int main()
{
    int n, x, comand;
    class AVLTree tree;
    int pos = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        pos = 0;
        std::cin >> comand >> x;
        if (comand == 1) {
            tree.InsertAvl(x, pos);
            std::cout << pos;
            std::cout  << "\n";
        } else if (comand == 2) {
            tree.RemoveAvl(x);
        }
    }
}
