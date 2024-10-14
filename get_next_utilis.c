#include "get_next_line.h"


void finish(list *clean_node, list **head, char *buffer)
{
    list *tmp;

  
    while (*head)
    {
        tmp = (*head)->next;
        free((*head)->buffer_str);
        free(*head);
        *head = tmp;
    }
    *head = NULL;

  
    if (clean_node && clean_node->buffer_str && clean_node->buffer_str[0])
    {
        *head = clean_node;
    }
    else
    {
    free(buffer);
      free(clean_node);
    }

}

void clean_all(list **head)
{
    list *node;
    list *clean_node;
    int i;
    int j;
    char *buffer;

    buffer = malloc(buffsize + 1);
    clean_node = malloc(sizeof(list));
    if (!buffer || !clean_node)
        return;
    node = find_last_node(*head);
    i = 0;
    j = 0;
  
    while (node->buffer_str[i] && node->buffer_str[i] != '\n')
        i++;
    
    while (node->buffer_str[i] != '\0')
	{
            i++;
            buffer[j++] = node->buffer_str[i];  
    }
    buffer[j] = '\0';
    clean_node->buffer_str = buffer;
    clean_node->next = NULL;
    finish(clean_node, head, buffer);
}
