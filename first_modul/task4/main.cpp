#include "stdio.h"
#include "string.h"
#include <iostream>

#define STRING_SIZE 12

typedef struct Node_s
{
    char data[STRING_SIZE];
    struct Node_s *next;
} Node;

void create_node(Node **head, char *data)
{
    *head = (Node *)malloc(sizeof(Node));
    memcpy((*head)->data,data,strlen(data) + 1);
    (*head)->next = NULL;
}

void insert_time(Node **head, char *begin, char *end)
{
    Node *tmp = *head;
    int flag_change = 0;
    while(tmp)
    {
        //printf("%d %d %d\n", strlen(tmp->data), strlen(begin), strcmp(tmp->data, begin));
        if (strlen(tmp->data) < strlen(begin))
        {
            memcpy(tmp->data,end,strlen(end) + 1);
            flag_change = 1;
            break;
        }
        else if (strlen(tmp->data) == strlen(begin))
        {
            if (strcmp(tmp->data, begin) < 0)
            {
                memcpy(tmp->data,end,strlen(end) + 1);
                flag_change = 1;
                break;
            }
        }
        tmp = tmp->next;
    }
    if(!flag_change)
    {
        Node *new_node;
        create_node(&new_node, end);
        new_node->next = *head;
        *head = new_node;

    }
}

int count_list(Node *head)
{
    int k = 0;
    while(head)
    {
        k++;
        //printf("%s -> ",head->data);
        head = head->next;
    }
    return k;
}

int main(void)
{
    Node *head;
    int n;
    char begin[STRING_SIZE], end[STRING_SIZE];
    scanf("%d", &n);
    scanf("%s %s", begin, end);
    create_node(&head, end);
    //printf("%s", head->data);
    for(int i = 0; i < n - 1; i++)
    {
        scanf("%s %s", begin, end);
        insert_time(&head, begin, end);
    }
    printf("%d",count_list(head));

}
