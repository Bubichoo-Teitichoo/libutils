#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>
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

static void test_strstripr_single_sep( void **status );
static void test_strstripr_single_sep_retval( void **status );
static void test_strstripr_multi_sep( void **status );
static void test_strstripr_multi_sep_retval( void **status );
static void test_strstripr_all_match( void **status );
static void test_strstripr_all_match_retval( void **status );
static void test_strstripr_no_match( void **status );
static void test_strstripr_no_match_retval( void **status );
static void test_strstripr_empty_string( void **status );
static void test_strstripr_empty_string_retval( void **status );
static void test_strstripr_null_input( void **status );
static void test_strstripr_null_separator( void **status );
static void test_strstripr_null_separator_retval( void **status );

static void test_strstripl_single_sep( void **status );
static void test_strstripl_single_sep_retval( void **status );
static void test_strstripl_multi_sep( void **status );
static void test_strstripl_multi_sep_retval( void **status );
static void test_strstripl_all_match( void **status );
static void test_strstripl_all_match_retval( void **status );
static void test_strstripl_no_match( void **status );
static void test_strstripl_no_match_retval( void **status );
static void test_strstripl_empty_string( void **status );
static void test_strstripl_empty_string_retval( void **status );
static void test_strstripl_null_input( void **status );
static void test_strstripl_null_separator( void **status );
static void test_strstripl_null_separator_retval( void **status );

static void test_strdup_strip_single_sep( void **status );
static void test_strdup_strip_multi_sep( void **status );
static void test_strdup_strip_all_match( void **status );
static void test_strdup_strip_no_match( void **status );
static void test_strdup_strip_empty_string( void **status );
static void test_strdup_strip_null_input( void **status );
static void test_strdup_strip_null_separator( void **status );

static void test_strdup_stripr_single_sep( void **status );
static void test_strdup_stripr_multi_sep( void **status );
static void test_strdup_stripr_all_match( void **status );
static void test_strdup_stripr_no_match( void **status );
static void test_strdup_stripr_empty_string( void **status );
static void test_strdup_stripr_null_input( void **status );
static void test_strdup_stripr_null_separator( void **status );

static void test_strdup_stripl_single_sep( void **status );
static void test_strdup_stripl_multi_sep( void **status );
static void test_strdup_stripl_all_match( void **status );
static void test_strdup_stripl_no_match( void **status );
static void test_strdup_stripl_empty_string( void **status );
static void test_strdup_stripl_null_input( void **status );
static void test_strdup_stripl_null_separator( void **status );

static void test_strcpy_stip_single_sep_oversized_input( void **status );
static void test_strcpy_stip_single_sep_undersized_input( void **status );
static void test_strcpy_stip_single_sep_null_input( void **status );
static void test_strcpy_stip_single_sep_null_size( void **status );
static void test_strcpy_stip_multi_sep_oversized_input( void **status );
static void test_strcpy_stip_multi_sep_undersized_input( void **status );
static void test_strcpy_stip_multi_sep_null_input( void **status );
static void test_strcpy_stip_multi_sep_null_size( void **status );
static void test_strcpy_stip_all_match( void **status );
static void test_strcpy_stip_all_match_null_input( void **status );
static void test_strcpy_stip_all_match_null_size( void **status );
static void test_strcpy_stip_no_match_oversized_input( void **status );
static void test_strcpy_stip_no_match_undersize_input( void **status );
static void test_strcpy_stip_no_match_null_input( void **status );
static void test_strcpy_stip_no_match_null_size( void **status );
static void test_strcpy_stip_empty_string( void **status );
static void test_strcpy_stip_empty_string_null_input( void **status );
static void test_strcpy_stip_empty_string_null_size( void **status );
static void test_strcpy_stip_null_separator_oversized_input( void **status );
static void test_strcpy_stip_null_separator_undersized_input( void **status );
static void test_strcpy_stip_null_separator_null_input( void **status );
static void test_strcpy_stip_null_separator_null_size( void **status );

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

        cmocka_unit_test( test_strstripr_single_sep ),
        cmocka_unit_test( test_strstripr_single_sep_retval ),
        cmocka_unit_test( test_strstripr_multi_sep ),
        cmocka_unit_test( test_strstripr_multi_sep_retval ),
        cmocka_unit_test( test_strstripr_all_match ),
        cmocka_unit_test( test_strstripr_all_match_retval ),
        cmocka_unit_test( test_strstripr_no_match ),
        cmocka_unit_test( test_strstripr_no_match_retval ),
        cmocka_unit_test( test_strstripr_empty_string ),
        cmocka_unit_test( test_strstripr_empty_string_retval ),
        cmocka_unit_test( test_strstripr_null_input ),
        cmocka_unit_test( test_strstripr_null_separator ),
        cmocka_unit_test( test_strstripr_null_separator_retval ),

        cmocka_unit_test( test_strstripl_single_sep ),
        cmocka_unit_test( test_strstripl_single_sep_retval ),
        cmocka_unit_test( test_strstripl_multi_sep ),
        cmocka_unit_test( test_strstripl_multi_sep_retval ),
        cmocka_unit_test( test_strstripl_all_match ),
        cmocka_unit_test( test_strstripl_all_match_retval ),
        cmocka_unit_test( test_strstripl_no_match ),
        cmocka_unit_test( test_strstripl_no_match_retval ),
        cmocka_unit_test( test_strstripl_empty_string ),
        cmocka_unit_test( test_strstripl_empty_string_retval ),
        cmocka_unit_test( test_strstripl_null_input ),
        cmocka_unit_test( test_strstripl_null_separator ),
        cmocka_unit_test( test_strstripl_null_separator_retval ),

        cmocka_unit_test( test_strdup_strip_single_sep ),
        cmocka_unit_test( test_strdup_strip_multi_sep ),
        cmocka_unit_test( test_strdup_strip_all_match ),
        cmocka_unit_test( test_strdup_strip_no_match ),
        cmocka_unit_test( test_strdup_strip_empty_string ),
        cmocka_unit_test( test_strdup_strip_null_input ),
        cmocka_unit_test( test_strdup_strip_null_separator ),

        cmocka_unit_test( test_strdup_stripr_single_sep ),
        cmocka_unit_test( test_strdup_stripr_multi_sep ),
        cmocka_unit_test( test_strdup_stripr_all_match ),
        cmocka_unit_test( test_strdup_stripr_no_match ),
        cmocka_unit_test( test_strdup_stripr_empty_string ),
        cmocka_unit_test( test_strdup_stripr_null_input ),
        cmocka_unit_test( test_strdup_stripr_null_separator ),

        cmocka_unit_test( test_strdup_stripl_single_sep ),
        cmocka_unit_test( test_strdup_stripl_multi_sep ),
        cmocka_unit_test( test_strdup_stripl_all_match ),
        cmocka_unit_test( test_strdup_stripl_no_match ),
        cmocka_unit_test( test_strdup_stripl_empty_string ),
        cmocka_unit_test( test_strdup_stripl_null_input ),
        cmocka_unit_test( test_strdup_stripl_null_separator ),

        cmocka_unit_test( test_strcpy_stip_single_sep_oversized_input ),
        cmocka_unit_test( test_strcpy_stip_single_sep_undersized_input ),
        cmocka_unit_test( test_strcpy_stip_single_sep_null_size ),
        cmocka_unit_test( test_strcpy_stip_single_sep_null_input ),
        cmocka_unit_test( test_strcpy_stip_multi_sep_oversized_input ),
        cmocka_unit_test( test_strcpy_stip_multi_sep_undersized_input ),
        cmocka_unit_test( test_strcpy_stip_multi_sep_null_input ),
        cmocka_unit_test( test_strcpy_stip_multi_sep_null_size ),
        cmocka_unit_test( test_strcpy_stip_all_match ),
        cmocka_unit_test( test_strcpy_stip_all_match_null_input ),
        cmocka_unit_test( test_strcpy_stip_all_match_null_size ),
        cmocka_unit_test( test_strcpy_stip_no_match_oversized_input ),
        cmocka_unit_test( test_strcpy_stip_no_match_undersize_input ),
        cmocka_unit_test( test_strcpy_stip_no_match_null_input ),
        cmocka_unit_test( test_strcpy_stip_no_match_null_size ),
        cmocka_unit_test( test_strcpy_stip_empty_string ),
        cmocka_unit_test( test_strcpy_stip_empty_string_null_input ),
        cmocka_unit_test( test_strcpy_stip_empty_string_null_size ),
        cmocka_unit_test( test_strcpy_stip_null_separator_oversized_input ),
        cmocka_unit_test( test_strcpy_stip_null_separator_undersized_input ),
        cmocka_unit_test( test_strcpy_stip_null_separator_null_input ),
        cmocka_unit_test( test_strcpy_stip_null_separator_null_size ),
    };
    return cmocka_run_group_tests( tests, NULL, NULL );
}

void test_strstrip_single_sep( void **status )
{
    char input[]           = "lllLrlrLlll";
    const char expected[]  = "LrlrL";
    const char separator[] = "l";
    (void)strstrip( input, separator );
    assert_string_equal( input, expected );
}

void test_strstrip_single_sep_retval( void **status )
{
    char input[]           = "lllLrlrLlll";
    const char expected[]  = "LrlrL";
    const char separator[] = "l";
    assert_string_equal( strstrip( input, separator ), expected );
}

void test_strstrip_multi_sep( void **status )
{
    char input[]           = "qqLLppLpqrLpqrqqLLppLpq";
    const char expected[]  = "rLpqr";
    const char separator[] = "Lpq";
    (void)strstrip( input, separator );
    assert_string_equal( input, expected );
}

void test_strstrip_multi_sep_retval( void **status )
{
    char input[]           = "qqLLppLpqrLpqrqqLLppLpq";
    const char expected[]  = "rLpqr";
    const char separator[] = "Lpq";
    assert_string_equal( strstrip( input, separator ), expected );
}

void test_strstrip_all_match( void **status )
{
    char input[]           = "lQpllppQpQl";
    const char expected[]  = "";
    const char separator[] = "lpQ";
    (void)strstrip( input, separator );
    assert_string_equal( input, expected );
}

void test_strstrip_all_match_retval( void **status )
{
    char input[]           = "lQpllppQpQl";
    const char expected[]  = "";
    const char separator[] = "lpQ";
    assert_string_equal( strstrip( input, separator ), expected );
}

void test_strstrip_no_match( void **status )
{
    char input[]           = "rstrrssttrs";
    const char expected[]  = "rstrrssttrs";
    const char separator[] = "lpQ";
    (void)strstrip( input, separator );
    assert_string_equal( input, expected );
}

void test_strstrip_no_match_retval( void **status )
{
    char input[]           = "rstrrssttrs";
    const char expected[]  = "rstrrssttrs";
    const char separator[] = "lpQ";
    assert_string_equal( strstrip( input, separator ), expected );
}

void test_strstrip_empty_string( void **status )
{
    char input[]           = "";
    const char expected[]  = "";
    const char separator[] = "abcdefghijklmnopqrstuvwxyz";
    (void)strstrip( input, separator );
    assert_string_equal( input, expected );
}

void test_strstrip_empty_string_retval( void **status )
{
    char input[]           = "";
    const char expected[]  = "";
    const char separator[] = "abcdefghijklmnopqrstuvwxyz";
    assert_string_equal( strstrip( input, separator ), expected );
}

void test_strstrip_null_input( void **status )
{
    assert_null( strstrip( NULL, "ABC" ) );
}

void test_strstrip_null_separator( void **status )
{
    char input[]          = "\t\n \rABC \r\n\t";
    const char expected[] = "ABC";
    (void)strstrip( input, NULL );
    assert_string_equal( input, expected );
}

void test_strstrip_null_separator_retval( void **status )
{
    char input[]          = "\t\n \rABC \r\n\t";
    const char expected[] = "ABC";
    assert_string_equal( strstrip( input, NULL ), expected );
}

// ------------------------------------------------------------------------------------------
// ------------------------------------ TEST strstripr() ------------------------------------
// ------------------------------------------------------------------------------------------

void test_strstripr_single_sep( void **status )
{
    char input[]           = "lllLrlrLlll";
    const char expected[]  = "lllLrlrL";
    const char separator[] = "l";
    (void)strstripr( input, separator );
    assert_string_equal( input, expected );
}

void test_strstripr_single_sep_retval( void **status )
{
    char input[]           = "lllLrlrLlll";
    const char expected[]  = "lllLrlrL";
    const char separator[] = "l";
    assert_string_equal( strstripr( input, separator ), expected );
}

void test_strstripr_multi_sep( void **status )
{
    char input[]           = "qqLLppLpqrLpqrqqLLppLpq";
    const char expected[]  = "qqLLppLpqrLpqr";
    const char separator[] = "Lpq";
    (void)strstripr( input, separator );
    assert_string_equal( input, expected );
}

void test_strstripr_multi_sep_retval( void **status )
{
    char input[]           = "qqLLppLpqrLpqrqqLLppLpq";
    const char expected[]  = "qqLLppLpqrLpqr";
    const char separator[] = "Lpq";
    assert_string_equal( strstripr( input, separator ), expected );
}

void test_strstripr_all_match( void **status )
{
    char input[]           = "lQpllppQpQl";
    const char expected[]  = "";
    const char separator[] = "lpQ";
    (void)strstripr( input, separator );
    assert_string_equal( input, expected );
}

void test_strstripr_all_match_retval( void **status )
{
    char input[]           = "lQpllppQpQl";
    const char expected[]  = "";
    const char separator[] = "lpQ";
    assert_string_equal( strstripr( input, separator ), expected );
}

void test_strstripr_no_match( void **status )
{
    char input[]           = "rstrrssttrs";
    const char expected[]  = "rstrrssttrs";
    const char separator[] = "lpQ";
    (void)strstripr( input, separator );
    assert_string_equal( input, expected );
}

void test_strstripr_no_match_retval( void **status )
{
    char input[]           = "rstrrssttrs";
    const char expected[]  = "rstrrssttrs";
    const char separator[] = "lpQ";
    assert_string_equal( strstripr( input, separator ), expected );
}

void test_strstripr_empty_string( void **status )
{
    char input[]           = "";
    const char expected[]  = "";
    const char separator[] = "abcdefghijklmnopqrstuvwxyz";
    (void)strstripr( input, separator );
    assert_string_equal( input, expected );
}

void test_strstripr_empty_string_retval( void **status )
{
    char input[]           = "";
    const char expected[]  = "";
    const char separator[] = "abcdefghijklmnopqrstuvwxyz";
    assert_string_equal( strstripr( input, separator ), expected );
}

void test_strstripr_null_input( void **status )
{
    assert_null( strstripr( NULL, "ABC" ) );
}

void test_strstripr_null_separator( void **status )
{
    char input[]          = "\t\n \rABC \r\n\t";
    const char expected[] = "\t\n \rABC";
    (void)strstripr( input, NULL );
    assert_string_equal( input, expected );
}

void test_strstripr_null_separator_retval( void **status )
{
    char input[]          = "\t\n \rABC \r\n\t";
    const char expected[] = "\t\n \rABC";
    assert_string_equal( strstripr( input, NULL ), expected );
}


// ------------------------------------------------------------------------------------------
// ------------------------------------ TEST strstripl() ------------------------------------
// ------------------------------------------------------------------------------------------

void test_strstripl_single_sep( void **status )
{
    char input[]           = "lllLrlrLlll";
    const char expected[]  = "LrlrLlll";
    const char separator[] = "l";
    (void)strstripl( input, separator );
    assert_string_equal( input, expected );
}

void test_strstripl_single_sep_retval( void **status )
{
    char input[]           = "lllLrlrLlll";
    const char expected[]  = "LrlrLlll";
    const char separator[] = "l";
    assert_string_equal( strstripl( input, separator ), expected );
}

void test_strstripl_multi_sep( void **status )
{
    char input[]           = "qqLLppLpqrLpqrqqLLppLpq";
    const char expected[]  = "rLpqrqqLLppLpq";
    const char separator[] = "Lpq";
    (void)strstripl( input, separator );
    assert_string_equal( input, expected );
}

void test_strstripl_multi_sep_retval( void **status )
{
    char input[]           = "qqLLppLpqrLpqrqqLLppLpq";
    const char expected[]  = "rLpqrqqLLppLpq";
    const char separator[] = "Lpq";
    assert_string_equal( strstripl( input, separator ), expected );
}

void test_strstripl_all_match( void **status )
{
    char input[]           = "lQpllppQpQl";
    const char expected[]  = "";
    const char separator[] = "lpQ";
    (void)strstripl( input, separator );
    assert_string_equal( input, expected );
}

void test_strstripl_all_match_retval( void **status )
{
    char input[]           = "lQpllppQpQl";
    const char expected[]  = "";
    const char separator[] = "lpQ";
    assert_string_equal( strstripl( input, separator ), expected );
}

void test_strstripl_no_match( void **status )
{
    char input[]           = "rstrrssttrs";
    const char expected[]  = "rstrrssttrs";
    const char separator[] = "lpQ";
    (void)strstripl( input, separator );
    assert_string_equal( input, expected );
}

void test_strstripl_no_match_retval( void **status )
{
    char input[]           = "rstrrssttrs";
    const char expected[]  = "rstrrssttrs";
    const char separator[] = "lpQ";
    assert_string_equal( strstripl( input, separator ), expected );
}

void test_strstripl_empty_string( void **status )
{
    char input[]           = "";
    const char expected[]  = "";
    const char separator[] = "abcdefghijklmnopqrstuvwxyz";
    (void)strstripl( input, separator );
    assert_string_equal( input, expected );
}

void test_strstripl_empty_string_retval( void **status )
{
    char input[]           = "";
    const char expected[]  = "";
    const char separator[] = "abcdefghijklmnopqrstuvwxyz";
    assert_string_equal( strstripl( input, separator ), expected );
}

void test_strstripl_null_input( void **status )
{
    assert_null( strstripl( NULL, "ABC" ) );
}

void test_strstripl_null_separator( void **status )
{
    char input[]          = "\t\n \rABC \r\n\t";
    const char expected[] = "ABC \r\n\t";
    (void)strstripl( input, NULL );
    assert_string_equal( input, expected );
}

void test_strstripl_null_separator_retval( void **status )
{
    char input[]          = "\t\n \rABC \r\n\t";
    const char expected[] = "ABC \r\n\t";
    assert_string_equal( strstripl( input, NULL ), expected );
}

// ------------------------------------------------------------------------------------------
// ----------------------------------- TEST strdup_strip() ----------------------------------
// ------------------------------------------------------------------------------------------

void test_strdup_strip_single_sep( void **status )
{
    const char input[]     = "lllLrlrLlll";
    const char expected[]  = "LrlrL";
    const char separator[] = "l";

    char *output = strdup_strip( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "lllLrlrLlll" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_strip_multi_sep( void **status )
{
    const char input[]     = "qqLLppLpqrLpqrqqLLppLpq";
    const char expected[]  = "rLpqr";
    const char separator[] = "Lpq";

    char *output = strdup_strip( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "qqLLppLpqrLpqrqqLLppLpq" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_strip_all_match( void **status )
{
    const char input[]     = "lQpllppQpQl";
    const char expected[]  = "";
    const char separator[] = "lpQ";

    char *output = strdup_strip( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "lQpllppQpQl" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_strip_no_match( void **status )
{
    const char input[]     = "rstrrssttrs";
    const char expected[]  = "rstrrssttrs";
    const char separator[] = "lpQ";

    char *output = strdup_strip( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "rstrrssttrs" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_strip_empty_string( void **status )
{
    const char input[]     = "";
    const char expected[]  = "";
    const char separator[] = "abcdefghijklmnopqrstuvwxyz";

    char *output = strdup_strip( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_strip_null_input( void **status )
{
    assert_null( strdup_strip( NULL, "ABC" ) );
}

void test_strdup_strip_null_separator( void **status )
{
    char input[]          = "\t\n \rABC \r\n\t";
    const char expected[] = "ABC";

    char *output = strdup_strip( input, NULL );
    assert_string_equal( output, expected );
    assert_string_equal( input, "\t\n \rABC \r\n\t" );
    assert_ptr_not_equal( output, input );

    free( output );
}


// ------------------------------------------------------------------------------------------
// ----------------------------------- TEST strdup_stripr() ----------------------------------
// ------------------------------------------------------------------------------------------

void test_strdup_stripr_single_sep( void **status )
{
    const char input[]     = "lllLrlrLlll";
    const char expected[]  = "lllLrlrL";
    const char separator[] = "l";

    char *output = strdup_stripr( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "lllLrlrLlll" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_stripr_multi_sep( void **status )
{
    const char input[]     = "qqLLppLpqrLpqrqqLLppLpq";
    const char expected[]  = "qqLLppLpqrLpqr";
    const char separator[] = "Lpq";

    char *output = strdup_stripr( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "qqLLppLpqrLpqrqqLLppLpq" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_stripr_all_match( void **status )
{
    const char input[]     = "lQpllppQpQl";
    const char expected[]  = "";
    const char separator[] = "lpQ";

    char *output = strdup_stripr( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "lQpllppQpQl" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_stripr_no_match( void **status )
{
    const char input[]     = "rstrrssttrs";
    const char expected[]  = "rstrrssttrs";
    const char separator[] = "lpQ";

    char *output = strdup_stripr( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "rstrrssttrs" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_stripr_empty_string( void **status )
{
    const char input[]     = "";
    const char expected[]  = "";
    const char separator[] = "abcdefghijklmnopqrstuvwxyz";

    char *output = strdup_stripr( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_stripr_null_input( void **status )
{
    assert_null( strdup_stripr( NULL, "ABC" ) );
}

void test_strdup_stripr_null_separator( void **status )
{
    const char input[]    = "\t\n \rABC \r\n\t";
    const char expected[] = "\t\n \rABC";

    char *output = strdup_stripr( input, NULL );
    assert_string_equal( output, expected );
    assert_string_equal( input, "\t\n \rABC \r\n\t" );
    assert_ptr_not_equal( output, input );

    free( output );
}

// ------------------------------------------------------------------------------------------
// ----------------------------------- TEST strdup_stripl() ----------------------------------
// ------------------------------------------------------------------------------------------

void test_strdup_stripl_single_sep( void **status )
{
    const char input[]     = "lllLrlrLlll";
    const char expected[]  = "LrlrLlll";
    const char separator[] = "l";

    char *output = strdup_stripl( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "lllLrlrLlll" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_stripl_multi_sep( void **status )
{
    const char input[]     = "qqLLppLpqrLpqrqqLLppLpq";
    const char expected[]  = "rLpqrqqLLppLpq";
    const char separator[] = "Lpq";

    char *output = strdup_stripl( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "qqLLppLpqrLpqrqqLLppLpq" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_stripl_all_match( void **status )
{
    const char input[]     = "lQpllppQpQl";
    const char expected[]  = "";
    const char separator[] = "lpQ";

    char *output = strdup_stripl( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "lQpllppQpQl" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_stripl_no_match( void **status )
{
    const char input[]     = "rstrrssttrs";
    const char expected[]  = "rstrrssttrs";
    const char separator[] = "lpQ";

    char *output = strdup_stripl( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "rstrrssttrs" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_stripl_empty_string( void **status )
{
    const char input[]     = "";
    const char expected[]  = "";
    const char separator[] = "abcdefghijklmnopqrstuvwxyz";

    char *output = strdup_stripl( input, separator );
    assert_string_equal( output, expected );
    assert_string_equal( input, "" );
    assert_ptr_not_equal( output, input );

    free( output );
}

void test_strdup_stripl_null_input( void **status )
{
    assert_null( strdup_stripl( NULL, "ABC" ) );
}

void test_strdup_stripl_null_separator( void **status )
{
    const char input[]    = "\t\n \rABC \r\n\t";
    const char expected[] = "ABC \r\n\t";

    char *output = strdup_stripl( input, NULL );
    assert_string_equal( output, expected );
    assert_string_equal( input, "\t\n \rABC \r\n\t" );
    assert_ptr_not_equal( output, input );

    free( output );
}


void test_strcpy_stip_single_sep_oversized_input( void **status )
{
    char output[ 32 ]      = { 0 };
    const char input[]     = "lllLrlrLlll";
    const char expected[]  = "LrlrL";
    const char separator[] = "l";

    const size_t len = strcpy_strip( output, sizeof( output ), input, separator );
    assert_string_equal( output, expected );
    assert_int_equal( len, 6 );
}

void test_strcpy_stip_single_sep_undersized_input( void **status )
{
    char output[ 4 ]       = { 0 };
    const char input[]     = "lllLrlrLlll";
    const char expected[]  = "Lrl";
    const char separator[] = "l";

    const size_t len = strcpy_strip( output, sizeof( output ), input, separator );
    assert_string_equal( output, expected );
    assert_int_equal( len, 4 );
}

void test_strcpy_stip_single_sep_null_input( void **status )
{
    const char input[]     = "lllLrlrLlll";
    const char expected[]  = "LrlrL";
    const char separator[] = "l";

    const size_t len = strcpy_strip( NULL, 32, input, separator );
    assert_int_equal( len, 6 );
}

void test_strcpy_stip_single_sep_null_size( void **status )
{
    char output[ 32 ]      = { 0 };
    const char input[]     = "lllLrlrLlll";
    const char expected[]  = "LrlrL";
    const char separator[] = "l";

    const size_t len = strcpy_strip( output, 0, input, separator );
    assert_int_equal( len, 6 );
}

void test_strcpy_stip_multi_sep_oversized_input( void **status )
{
    char output[ 32 ]      = { 0 };
    const char input[]     = "qqLLppLpqrLpqrqqLLppLpq";
    const char expected[]  = "rLpqr";
    const char separator[] = "Lpq";

    const size_t len = strcpy_strip( output, sizeof( output ), input, separator );
    assert_string_equal( output, expected );
    assert_int_equal( len, 6 );
}

void test_strcpy_stip_multi_sep_undersized_input( void **status )
{
    char output[ 4 ]       = { 0 };
    const char input[]     = "qqLLppLpqrLpqrqqLLppLpq";
    const char expected[]  = "rLp";
    const char separator[] = "Lpq";

    const size_t len = strcpy_strip( output, sizeof( output ), input, separator );
    assert_string_equal( output, expected );
    assert_int_equal( len, 4 );
}

void test_strcpy_stip_multi_sep_null_input( void **status )
{
    const char input[]     = "qqLLppLpqrLpqrqqLLppLpq";
    const char expected[]  = "rLpqr";
    const char separator[] = "Lpq";

    const size_t len = strcpy_strip( NULL, 32, input, separator );
    assert_int_equal( len, 6 );
}

void test_strcpy_stip_multi_sep_null_size( void **status )
{
    char output[ 32 ]      = { 0 };
    const char input[]     = "qqLLppLpqrLpqrqqLLppLpq";
    const char expected[]  = "rLpqr";
    const char separator[] = "Lpq";

    const size_t len = strcpy_strip( output, 0, input, separator );
    assert_string_equal( output, "" );
    assert_int_equal( len, 6 );
}

void test_strcpy_stip_all_match( void **status )
{
    char output[ 32 ]      = "13141451";
    const char input[]     = "lQpllppQpQl";
    const char expected[]  = "";
    const char separator[] = "lpQ";

    const size_t len = strcpy_strip( output, sizeof( output ), input, separator );
    assert_string_equal( output, expected );
    assert_int_equal( len, 1 );
}

void test_strcpy_stip_all_match_null_input( void **status )
{
    const char input[]     = "lQpllppQpQl";
    const char expected[]  = "";
    const char separator[] = "lpQ";

    const size_t len = strcpy_strip( NULL, 32, input, separator );
    assert_int_equal( len, 1 );
}

void test_strcpy_stip_all_match_null_size( void **status )
{
    char output[ 32 ]      = { 0 };
    const char input[]     = "lQpllppQpQl";
    const char expected[]  = "";
    const char separator[] = "lpQ";

    const size_t len = strcpy_strip( NULL, 0, input, separator );
    assert_int_equal( len, 1 );
}

void test_strcpy_stip_no_match_oversized_input( void **status )
{
}

void test_strcpy_stip_no_match_undersize_input( void **status )
{
}

void test_strcpy_stip_no_match_null_input( void **status )
{
}

void test_strcpy_stip_no_match_null_size( void **status )
{
}

void test_strcpy_stip_empty_string( void **status )
{
}

void test_strcpy_stip_empty_string_null_input( void **status )
{
}

void test_strcpy_stip_empty_string_null_size( void **status )
{
}

void test_strcpy_stip_null_separator_oversized_input( void **status )
{
}

void test_strcpy_stip_null_separator_undersized_input( void **status )
{
}

void test_strcpy_stip_null_separator_null_input( void **status )
{
}

void test_strcpy_stip_null_separator_null_size( void **status )
{
}
