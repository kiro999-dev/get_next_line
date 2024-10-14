#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define buffsize 10

typedef struct list
{
    char *buffer_str;
    struct list *next;
}list;
list *find_last_node(list *head);
void    add_to_list(list **head,char *buffer);
void    clean_all(list **head);
