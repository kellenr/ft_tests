#include <stdlib.h>
#include <check.h>

#include "tests.c"

Suite *c00_test_suite(void)
{
    Suite *s;
    TCase *tc_c00;
    s = suite_create("TestSuite");
    tc_c00 = tcase_create("C00");

    /* Here we add the tests cases */
    tcase_add_test(tc_c00, t_ft_put_string);

    suite_add_tcase(s, tc_c00);
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    setenv("CK_COLOR_ALWAYS", "yes", 1);
    s = c00_test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_SUBUNIT);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
