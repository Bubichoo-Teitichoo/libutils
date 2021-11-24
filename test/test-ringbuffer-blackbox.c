#include "testing.h"
// include uut after testing to override malloc etc...
#include "ringbuffer/ringbuffer.c"

// Black Box Testing of the ring_buffer_* API

static void test_ring_buffer_memory_leak( void **status );
static void test_ring_buffer_fill_buffer( void **status );
static void test_ring_buffer_overfill_buffer_override_enabled( void **status );
static void test_ring_buffer_overfill_buffer_override_disabled( void **status );

int main( void )
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test( test_ring_buffer_memory_leak ),
        cmocka_unit_test( test_ring_buffer_fill_buffer ),
        cmocka_unit_test( test_ring_buffer_overfill_buffer_override_enabled ),
        cmocka_unit_test( test_ring_buffer_overfill_buffer_override_disabled ),

    };
    return cmocka_run_group_tests( tests, NULL, NULL );
}

void test_ring_buffer_memory_leak( void **status )
{
    ring_buffer_t *rb = RING_BUFFER_NEW( int, 20 );
    ring_buffer_free( rb );
}

void test_ring_buffer_fill_buffer( void **status )
{
    ring_buffer_t *rb = RING_BUFFER_NEW( int, 20 );
    for( int i = 0; i < 20; i++ )
    {
        assert_int_equal( 0, ring_buffer_push( rb, &i ) );
        assert_int_equal( (size_t)i + 1, ring_buffer_items( rb ) );
    }
    for( int i = 0; i < 20; i++ )
    {
        const int data = RING_BUFFER_POP( int, rb, -1 );
        assert_int_equal( i, data );
        assert_int_equal( 20 - ( i + 1 ), ring_buffer_items( rb ) );
    }
    assert_null( ring_buffer_pop( rb ) );
    ring_buffer_free( rb );
}

void test_ring_buffer_overfill_buffer_override_enabled( void **status )
{
    ring_buffer_t *rb = RING_BUFFER_NEW( int, 20 );
    assert_int_equal( 0, ring_buffer_enable_override( rb, 1 ) );
    for( int i = 0; i < 35; i++ )
    {
        assert_int_equal( 0, ring_buffer_push( rb, &i ) );
        if( i < 20 )
        {
            assert_int_equal( (size_t)i + 1, ring_buffer_items( rb ) );
        }
        else
        {
            assert_int_equal( (size_t)20, ring_buffer_items( rb ) );
        }
    }
    for( int i = 0; i < 20; i++ )
    {
        const int data = RING_BUFFER_POP( int, rb, -1 );
        assert_int_equal( i + 15, data );
        assert_int_equal( 20 - ( i + 1 ), ring_buffer_items( rb ) );
    }

    ring_buffer_free( rb );
}

void test_ring_buffer_overfill_buffer_override_disabled( void **status )
{
    ring_buffer_t *rb = RING_BUFFER_NEW( int, 20 );
    assert_int_equal( 0, ring_buffer_enable_override( rb, 0 ) );
    for( int i = 0; i < 35; i++ )
    {
        if( i < 20 )
        {
            assert_int_equal( 0, ring_buffer_push( rb, &i ) );
            assert_int_equal( (size_t)i + 1, ring_buffer_items( rb ) );
        }
        else
        {
            assert_int_equal( 1, ring_buffer_push( rb, &i ) );
            assert_int_equal( 20, ring_buffer_items( rb ) );
        }
    }

    for( int i = 0; i < 20; i++ )
    {
        const int data = RING_BUFFER_POP( int, rb, -1 );
        assert_int_equal( i, data );
        assert_int_equal( 20 - ( i + 1 ), ring_buffer_items( rb ) );
    }
    assert_null( ring_buffer_pop( rb ) );
    ring_buffer_free( rb );
}
