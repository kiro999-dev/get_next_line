#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// Function to check if any line in the list contains a newline character
int check_line(list *head)
{
    int i;

    while (head)
    {
        i = 0;
        while (head->buffer_str[i])
        {
            if (head->buffer_str[i] == '\n')
                return 1;
            ++i;
        }
        head = head->next;
    }
    return 0;
}

// Function to create the linked list of buffers from the file descriptor
void create_list(int fd, list **head)
{
    char *buffer;
    int byts;

    while (!check_line(*head))
    {
        buffer = malloc(buffsize + 1);
        if (!buffer)
            return;
        byts = read(fd, buffer, buffsize);
        if (!byts)
        {
            free(buffer);
            return;
        }
        buffer[byts] = '\0';
        add_to_list(head, buffer);
    }
}

// Function to count the length of the line up to the newline character
int count_len(list *head)
{
    int nl = 0;
    int i;

    while (head)
    {
        i = 0;
        while (head->buffer_str[i])
        {
            if (head->buffer_str[i] == '\n')
            {
                ++nl;
                return nl;
            }
            nl++;
            ++i;
        }
        head = head->next;
    }
    return nl;
}

// Function to fill the line buffer with characters up to the newline character
void fill_line(char *line, list *head)
{
    int nl = 0;
    int i;

    while (head)
    {
        i = 0;
        while (head->buffer_str[i])
        {
            if (head->buffer_str[i] == '\n')
            {
                line[nl++] = '\n';
                line[nl] = '\0';
                return;
            }
            line[nl++] = head->buffer_str[i++];
        }
        head = head->next;
    }
    line[nl] = '\0';
}

// Function to get the next line from the list
char *get_line(list *head)
{
    char *line;
    int line_len;

    if (head == NULL)
        return NULL;

    line_len = count_len(head);
    line = malloc(line_len + 1);
    if (!line)
        return NULL;

    fill_line(line, head);
    return line;
}




// Main function to get the next line from the file descriptor
char *get_next_line(int fd)
{
    static list *head = NULL;
    char *line;

    if (fd < 0 || buffsize <= 0 || read(fd, NULL, 0) < 0)
        return NULL;

    create_list(fd, &head);
    if (head == NULL)
        return NULL;

    line = get_line(head);
    clean_all(&head);
    return line;
}

// Main function for testing
int main()
{
    char *res;
    int fd;

    fd = open("a.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("Error opening file\n");
        return 1;
    }

    while ((res = get_next_line(fd)) != NULL)
    {
      
        free(res); // Free the allocated memory for each line
    }

    close(fd);
    return 0;
}
