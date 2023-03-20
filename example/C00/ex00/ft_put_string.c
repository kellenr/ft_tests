#include <unistd.h>

void ft_put_string(char *s, size_t count) {
    write(1, s, count);
}
