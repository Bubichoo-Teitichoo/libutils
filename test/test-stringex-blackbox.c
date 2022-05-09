#include "testing.h"

#include "structures/stringex/stringex.c"

static void test_strstrip_single_sep( void **status );
static void test_strstrip_single_sep_retval( void **status );
static void test_strstrip_multi_sep( void **status );
static void test_strstrip_multi_sep_retval( void **status );
static void test_strstrip_all_match( void **status );
static void test_strstrip_all_match_retval( void **status );
static void test_strstrip_no_match( void **status );
static void test_strstrip_no_match_retval( void **status );
static void test_strstrip_empty_string( void **status );
static void test_strstrip_empty_string_retval( void **status );
static void test_strstrip_null_input( void **status );
static void test_strstrip_null_separator( void **status );
static void test_strstrip_null_separator_retval( void **status );

static void test_strrstrip_single_sep( void **status );
static void test_strrstrip_single_sep_retval( void **status );
static void test_strrstrip_multi_sep( void **status );
static void test_strrstrip_multi_sep_retval( void **status );
static void test_strrstrip_all_match( void **status );
static void test_strrstrip_all_match_retval( void **status );
static void test_strrstrip_no_match( void **status );
static void test_strrstrip_no_match_retval( void **status );
static void test_strrstrip_empty_string( void **status );
static void test_strrstrip_empty_string_retval( void **status );
static void test_strrstrip_null_input( void **status );
static void test_strrstrip_null_separator( void **status );
static void test_strrstrip_null_separator_null( void **status );

static void test_strlstrip( void **status );

static void test_strdup_format( void **status );
static void test_strdup_vaformat( void **status );

int main( void )
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test( test_strstrip_single_sep ),
        cmocka_unit_test( test_strstrip_single_sep_retval ),
        cmocka_unit_test( test_strstrip_multi_sep ),
        cmocka_unit_test( test_strstrip_multi_sep_retval ),
        cmocka_unit_test( test_strstrip_all_match ),
        cmocka_unit_test( test_strstrip_all_match_retval ),
        cmocka_unit_test( test_strstrip_no_match ),
        cmocka_unit_test( test_strstrip_no_match_retval ),
        cmocka_unit_test( test_strstrip_empty_string ),
        cmocka_unit_test( test_strstrip_empty_string_retval ),
        cmocka_unit_test( test_strstrip_null_input ),
        cmocka_unit_test( test_strstrip_null_separator ),
        cmocka_unit_test( test_strstrip_null_separator_retval ),
        cmocka_unit_test( test_strrstrip_single_sep ),
        cmocka_unit_test( test_strrstrip_single_sep_retval ),
        cmocka_unit_test( test_strrstrip_multi_sep),
        cmocka_unit_test( test_strrstrip_multi_sep_retval ),
        cmocka_unit_test( test_strrstrip_all_match ),
        cmocka_unit_test( test_strrstrip_all_match_retval),
        cmocka_unit_test( test_strrstrip_no_match ),
        cmocka_unit_test( test_strrstrip_no_match_retval ),
        cmocka_unit_test( test_strrstrip_empty_string),
        cmocka_unit_test( test_strrstrip_empty_string_retval ),
        cmocka_unit_test( test_strrstrip_null),
        cmocka_unit_test( test_strlstrip ),
        cmocka_unit_test( test_strdup_format ),
        cmocka_unit_test( test_strdup_vaformat ),

    };
    return cmocka_run_group_tests( tests, NULL, NULL );
}

void test_strstrip_single_sep( void **status )
{
    char input[]           = "lllLrlrLlll";
    const char output[]    = "LrlrL";
    const char separator[] = "l";
    (void)strstrip( input, separator );
    assert_string_equal( input, output );
}

void test_strstrip_single_sep_retval( void **status )
{
    char input[]           = "lllLrlrLlll";
    const char output[]    = "LrlrL";
    const char separator[] = "l";
    assert_string_equal( strstrip( input, separator ), output );
}

void test_strstrip_multi_sep( void **status )
{
    char input[]           = "qqLLppLpqrLpqrqqLLppLpq";
    const char output[]    = "rLpqr";
    const char separator[] = "Lpq";
    (void)strstrip( input, separator );
    assert_string_equal( input, output );
}

void test_strstrip_multi_sep_retval( void **status )
{
    char input[]           = "qqLLppLpqrLpqrqqLLppLpq";
    const char output[]    = "rLpqr";
    const char separator[] = "Lpq";
    assert_string_equal( strstrip( input, separator ), output );
}

void test_strstrip_all_match( void **status )
{
    char input[]           = "lQpllppQpQl";
    const char output[]    = "";
    const char separator[] = "lpQ";
    (void)strstrip( input, separator );
    assert_string_equal( input, output );
}

void test_strstrip_all_match_retval( void **status )
{
    char input[]           = "lQpllppQpQl";
    const char output[]    = "";
    const char separator[] = "lpQ";
    assert_string_equal( strstrip( input, separator ), output );
}

void test_strstrip_no_match( void **status )
{
    char input[]           = "rstrrssttrs";
    const char output[]    = "rstrrssttrs";
    const char separator[] = "lpQ";
    (void)strstrip( input, separator );
    assert_string_equal( input, output );
}

void test_strstrip_no_match_retval( void **status )
{
    char input[]           = "rstrrssttrs";
    const char output[]    = "rstrrssttrs";
    const char separator[] = "lpQ";
    assert_string_equal( strstrip( input, separator ), output );
}

void test_strstrip_empty_string( void **status )
{
    char input[]           = "";
    const char output[]    = "";
    const char separator[] = "abcdefghijklmnopqrstuvwxyz";
    (void)strstrip( input, separator );
    assert_string_equal( input, output );
}

void test_strstrip_empty_string_retval( void **status )
{
    char input[]           = "";
    const char output[]    = "";
    const char separator[] = "abcdefghijklmnopqrstuvwxyz";
    assert_string_equal( strstrip( input, separator ), output );
}

void test_strstrip_null_input( void **status )
{
    assert_null( strstrip( NULL, "ABC" ) );
}

void test_strstrip_null_separator( void **status )
{
    char input[]           = "ABC";
    const char output[]    = "ABC";
    (void)strstrip( input, NULL );
    assert_string_equal(input , output );
    assert_string_equal( strstrip( input, NULL ), output );
}

void test_strstrip_null_separator_retval( void **status )
{
    char input[]        = "ABC";
    const char output[] = "ABC";
    assert_string_equal( strstrip( input, NULL ), output );
}

// ------------------------------------------------------------------------------------------
// ------------------------------------ TEST strrstrip() ------------------------------------
// ------------------------------------------------------------------------------------------

void test_strrstrip_single_sep( void **status ){}
void test_strrstrip_single_sep_retval( void **status ){}
void test_strrstrip_multi_sep( void **status ){}
void test_strrstrip_multi_sep_retval( void **status ){}
void test_strrstrip_all_match( void **status ){}
void test_strrstrip_all_match_retval( void **status ){}
void test_strrstrip_no_match( void **status ){}
void test_strrstrip_no_match_retval( void **status ){}
void test_strrstrip_empty_string( void **status ){}
void test_strrstrip_empty_string_retval( void **status ){}
void test_strrstrip_null( void **status )
{
}

void test_strlstrip( void **status )
{
}

void test_strdup_format( void **status )
{
}
void test_strdup_vaformat( void **status )
{
}
