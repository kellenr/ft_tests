#include <unistd.h>
#include <check.h>
#include "utils.h"
#include <strings.h>
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

START_TEST(t_ft_ultimate_ft)
{
    int a = 0;
    int *ptr1 = &a;
    int **ptr2 = &ptr1;
    int ***ptr3 = &ptr2;
    int ****ptr4 = &ptr3;
    int *****ptr5 = &ptr4;
    int ******ptr6 = &ptr5;
    int *******ptr7 = &ptr6;
    int ********ptr8 = &ptr7;
    int *********ptr9 = &ptr8;
    // Call the function we want to test
    ft_ultimate_ft(ptr9);

    // Check that the value was set correctly
    ck_assert_int_eq(a, 42);
}
END_TEST

START_TEST(t_ft_strlen)
{
    char* name;
    name = "walter";

    int got;
    got = ft_strlen(name);
    
    int want = strlen(name);
    ck_assert_int_eq(got, want);
}
END_TEST

START_TEST(t_ft_suma)
{
    int got;
    int want = 4;

    got = ft_suma(2, 2);

    ck_assert_int_eq(want, got);
}
END_TEST

START_TEST(t_ft_strcmp)
{
    int got;
    int want = 0;

    got = ft_strcmp("abc", "abc");
    ck_assert_int_eq(want, got);

    want = 67;
    got = ft_strcmp("ABC", "AB");
    ck_assert_int_eq(want, got);

    want = 7;
    got = ft_strcmp("ABJ", "ABC");
    ck_assert_int_eq(want, got);

    want = -25;
    got = ft_strcmp("ABA", "ABZ");
    ck_assert_int_eq(want, got);
}
END_TEST
