
#ifndef GET_NEXT
#define GET_NEXT
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFF_SIZE 8600

int get_next_line(const int fd,char **line);
 char *buffer;
 int size;

#endif
