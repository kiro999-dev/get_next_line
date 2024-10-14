#include "get_next_line.h"
list *find_last_node(list *head)
{
    if (head == NULL)
        return NULL;
    while (head->next)
    {
        head = head->next;
    }
    return head;
}

void add_to_list(list **head, char *buf)
{
    list *new_node;
    list *last_node;

    last_node = find_last_node(*head);
    new_node = malloc(sizeof(list));
    if (new_node == NULL)
        return;
      
    if (last_node == NULL)
    {
        *head = new_node;
    }
    else
    {
        last_node->next = new_node;
    }
    new_node->buffer_str = buf; 
    new_node->next = NULL; 
}
