#include "get_next_line.h"

int count_line(char *buffer, int n) {
    int count = 0;
    while (buffer[n] == '\n' && buffer[n])
        n++;
    while (buffer[n] != '\n' && buffer[n]) {
        count++;
        n++;
    }
    return count;
}

int get_next_line(const int fd, char **line) {
    static int i = 0;
    static int cheak_fd = 0;
    int line_len = 0, j = 0;

    if (cheak_fd != fd) {
        if (cheak_fd != 0) {
            free(buffer);
            free(*line);
            buffer = NULL;
            *line = NULL;
        }
        buffer = (char *)malloc(sizeof(char) * BUFF_SIZE + 1);
        if (!buffer)
            return 0;
        size = read(fd, buffer, BUFF_SIZE);
        if (size <= 0) {
            return size;
        }
        cheak_fd = fd;
        i = 0;
    }

    if (i > 0) {
        free(*line);
        *line = NULL;
    }
    line_len = count_line(buffer, i);
    *line = (char *)malloc(line_len + 1 * sizeof(char));
    if (!line)
        return 0;

    while (buffer[i] == '\n' && buffer[i])
        i++;

    while (buffer[i] && buffer[i] != '\n') {
        (*line)[j] = buffer[i];
        i++;
        j++;
    }
    (*line)[j] = '\0';

    while (buffer[i] == '\n' && buffer[i])
        i++;

    return size;
}

