#include "stdio.h"
#include "string.h"
#include <iostream>

#define STRING_SIZE 12

typedef struct Node_s
{
    int left_border;
    int right_border;
    int pen;
    struct Node_s *next;
} Node;

void create_node(Node **head, int left_border, int right_border)
{
    *head = (Node *)malloc(sizeof(Node));
    (*head)->left_border = left_border;
    (*head)->right_border = right_border;
    (*head)->pen = 0;
    (*head)->next = NULL;
}

void insert_borders(Node **head, int left_border, int right_border)
{
    if (left_border == right_border)
        return;
    Node *tmp = *head;
    Node *prev = *head;
    int flag_change = 0;
    int pen = 0;
    while(tmp)
    {
        prev = tmp;
        flag_change = 0;
        //pen = 0;
        if (left_border <= tmp->left_border && right_border >= tmp->right_border) {
            return;
        }
        //printf("%d %d %d\n", strlen(tmp->data), strlen(begin), strcmp(tmp->data, begin));
        if (left_border >= tmp->right_border || right_border <= tmp->left_border) {
            if (left_border == tmp->right_border || right_border == tmp->left_border) {
                pen = 1;
            }

            tmp = tmp->next;
            continue;
        }
        if (left_border > tmp->left_border) {
            tmp->left_border = left_border;
            if (tmp->pen > 0)
                tmp->pen--;
            flag_change = 1;
        }
        if (right_border < tmp->right_border) {
            tmp->right_border = right_border;
            if (tmp->pen > 0)
                tmp->pen--;
            flag_change = 1;
        }

        if (flag_change)
            break;
        tmp = tmp->next;
    }
    if(!flag_change)
    {
        Node *new_node;
        create_node(&new_node, left_border, right_border);
        new_node->pen = pen;
        prev->next = new_node;
    }
}


/*
4
1 5
22 25
5 6
0 25*/
int count_pen(Node *head, int k)
{
    while(head)
    {

        if (k == head->left_border)
            return 1;
        head = head->next;

    }
    return 0;
}
int count_list(Node *head)
{
    int ans = 0;
    Node *tmp = head;
    while(head)
    {

        ans += (2 - count_pen(tmp, head->right_border));
        //printf("%d %d %d -> ", head->left_border, head->right_border, count_pen(tmp, head->right_border));
        head = head->next;

    }
    //printf("\n");
    return ans;
}

void free_list(Node *head)
{
    Node *tmp = NULL;
    while(head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void)
{
    Node *head;
    int n;
    int  left_border, right_border;
    scanf("%d", &n);
    scanf("%d %d", &left_border, &right_border);
    create_node(&head, left_border, right_border);
    //printf("%s", head->data);
    for(int i = 0; i < n - 1; i++)
    {
        scanf("%d %d", &left_border, &right_border);
        insert_borders(&head, left_border, right_border);
    }
    printf("%d",count_list(head));
    free_list(head);

}
