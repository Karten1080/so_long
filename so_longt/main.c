#include "so_long.h"

int main(int argc, char **argv)
{
    int     fd;
    char    *line;

    argv++;
    argc--;
    fd = open(argv[0], O_RDONLY);
    if (fd == -1)
        return (0);
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    printf("%s", line);
    free(line);
    close(fd);
    return (0);
}