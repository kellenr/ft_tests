#include <unistd.h>
#include <check.h>
#include "utils.h"
#include "auto_headers.h"

START_TEST(t_ft_put_string)
{
    int pipe;
    pipe = open_pipe_stdout();

    char want[] = "walter";
    size_t gotsize = sizeof(want);

    ft_put_string(want, gotsize);
    
    char got[gotsize];
    read_from_pipe_and_close(pipe, got, gotsize);

    ck_assert_str_eq(want, got);
}
END_TEST
