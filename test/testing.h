#if !defined( __TESTING_H__ )
#define __TESTING_H__

#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdlib.h>

#if defined( __ENABLE_MEMORY_ARGUMENT_CHECKING__ )
// replace memory allocation methods with their argument checking counter parts
// use these function in combination with the mocked_* macros for convinience.
#define malloc( SIZE )         __malloc( ( SIZE ) )
#define calloc( NUM, SIZE )    __calloc( ( NUM ), ( SIZE ) )
#define realloc( BLOCK, SIZE ) __realloc( ( BLOCK ), ( SIZE ) )
#define free( BLOCK )          __free( ( BLOCK ) )
#else
// replace memory allocation methods with profiling counterparts. to find
// potential memory leaks.
#define malloc( SIZE )         test_malloc( SIZE )
#define calloc( LEN, SIZE )    test_calloc( LEN, SIZE )
#define realloc( BLOCK, SIZE ) test_realloc( BLOCK, SIZE )
#define free( BLOCK )          test_free( BLOCK )
#endif

#define mocked_malloc( TYPE )        (TYPE *)__mocked_malloc( test_malloc( sizeof( TYPE ) ), sizeof( TYPE ) )
#define mocked_malloc_n( TYPE )      (TYPE *)__mocked_malloc( NULL, sizeof( TYPE ) )
#define mocked_malloc_p( TYPE, PTR ) (TYPE *)__mocked_malloc( (void *)( PTR ), sizeof( TYPE ) )

#define mocked_calloc( TYPE )        (TYPE *)__mocked_calloc( test_calloc( 1, sizeof( TYPE ) ), 1, sizeof( TYPE ) )
#define mocked_calloc_n( TYPE )      (TYPE *)__mocked_calloc( NULL, 1, sizeof( TYPE ) )
#define mocked_calloc_p( TYPE, PTR ) (TYPE *)__mocked_calloc( (void *)( PTR ), 1, sizeof( TYPE ) )

#define mocked_realloc_n( TYPE, LEN )      (TYPE *)__mocked_realloc( NULL, ( LEN ), sizeof( TYPE ) )
#define mocked_realloc_p( TYPE, PTR, LEN ) (TYPE *)__mocked_realloc( (void *)( PTR ), ( LEN ), sizeof( TYPE ) )

#define mocked_free( BLOCK ) expect_value( __free, block, ( BLOCK ) )

extern void *_test_malloc( const size_t size, const char *file, const int line );
extern void *_test_realloc( void *block, const size_t size, const char *file, const int line );
extern void _test_free( void *const ptr, const char *file, const int line );

static void *__malloc( size_t size )
{
    check_expected( size );
    return mock_type( void * );
}

static void *__calloc( size_t num, size_t size )
{
    check_expected( num );
    check_expected( size );
    return mock_type( void * );
}

static void *__realloc( void *block, const size_t size )
{
    check_expected( block );
    check_expected( size );
    return mock_type( void * );
}

static void __free( void *block )
{
    check_expected( block );
}

static void *__mocked_malloc( void *memory, size_t size )
{
    expect_value( __malloc, size, size );
    will_return( __malloc, memory );
    return memory;
}

static void *__mocked_calloc( void *memory, size_t num, size_t size )
{
    expect_value( __calloc, num, num );
    expect_value( __calloc, size, size );
    will_return( __calloc, memory );
    return memory;
}

static void *__mocked_realloc( void *memory, void *block, const size_t size )
{
    expect_value( __realloc, block, block );
    expect_value( __realloc, size, size );
    will_return( __realloc, memory );
    return memory;
}

#endif   // __TESTING_H__
