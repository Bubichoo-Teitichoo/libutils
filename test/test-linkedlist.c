#define __ENABLE_MEMORY_ARGUMENT_CHECKING__
#include "testing.h"

#include "structures/linkedlist/linkedlist.c"

static void test_linked_list_node_new( void **status );
static void test_linked_list_node_new_mem_alloc_fails( void **status );

static void test_linked_list_node_free( void **status );
static void test_linked_list_node_free_node_null( void **status );
static void test_linked_list_node_free_closure( void **status );

static void test_linked_list_new( void **status );
static void test_linked_list_new_mem_alloc_fails( void **status );

static void test_linked_list_free_list( void **status );
static void test_linked_list_free_list_null( void **status );
static void test_linked_list_free_empty_list( void **status );

static void test_linked_list_append( void **status );
static void test_linked_list_append_first_element( void **status );
static void test_linked_list_append_list_null( void **status );
static void test_linked_list_append_data_null( void **status );
static void test_linked_list_append_mem_alloc_fails( void **status );

static void test_linked_list_remove_list_null( void **status );
static void test_linked_list_remove_node_null( void **status );
static void test_linked_list_remove_list_not_node_parent( void **status );
static void test_linked_list_remove_first_element( void **status );
static void test_linked_list_remove_last_element( void **status );
static void test_linked_list_remove_second_element( void **status );

static void test_linked_list_get_first( void **status );
static void test_linked_list_get_first_list_null( void **status );
static void test_linked_list_get_first_list_empty( void **status );

static void test_linked_list_get_last( void **status );
static void test_linked_list_get_last_list_null( void **status );
static void test_linked_list_get_last_list_empty( void **status );

static void test_linked_list_node_next( void **status );
static void test_linked_list_node_next_null( void **status );
static void test_linked_list_node_next_node_null( void **status );

static void test_linked_list_node_prev( void **status );
static void test_linked_list_node_prev_null( void **status );
static void test_linked_list_node_prev_node_null( void **status );

static void test_linked_list_node_set( void **status );
static void test_linked_list_node_set_node_null( void **status );
static void test_linked_list_node_set_data_null( void **status );

static void test_linked_list_node_get( void **status );
static void test_linked_list_node_get_node_null( void **status );

static void test_linked_list_node_get_cpy( void **status );
static void test_linked_list_node_get_cpy_node_null( void **status );
static void test_linked_list_node_get_cpy_data_null( void **status );


int main( void )
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test( test_linked_list_node_new ),
        cmocka_unit_test( test_linked_list_node_new_mem_alloc_fails ),
        cmocka_unit_test( test_linked_list_node_free ),
        cmocka_unit_test( test_linked_list_node_free_node_null ),
        cmocka_unit_test( test_linked_list_node_free_closure ),
        cmocka_unit_test( test_linked_list_new ),
        cmocka_unit_test( test_linked_list_new_mem_alloc_fails ),
        cmocka_unit_test( test_linked_list_free_list ),
        cmocka_unit_test( test_linked_list_free_list_null ),
        cmocka_unit_test( test_linked_list_free_empty_list ),
        cmocka_unit_test( test_linked_list_append ),
        cmocka_unit_test( test_linked_list_append_first_element ),
        cmocka_unit_test( test_linked_list_append_list_null ),
        cmocka_unit_test( test_linked_list_append_data_null ),
        cmocka_unit_test( test_linked_list_append_mem_alloc_fails ),
        cmocka_unit_test( test_linked_list_remove_list_null ),
        cmocka_unit_test( test_linked_list_remove_node_null ),
        cmocka_unit_test( test_linked_list_remove_list_not_node_parent ),
        cmocka_unit_test( test_linked_list_remove_first_element ),
        cmocka_unit_test( test_linked_list_remove_first_element ),
        cmocka_unit_test( test_linked_list_remove_last_element ),
        cmocka_unit_test( test_linked_list_remove_second_element ),
        cmocka_unit_test( test_linked_list_get_first ),
        cmocka_unit_test( test_linked_list_get_first_list_null ),
        cmocka_unit_test( test_linked_list_get_first_list_empty ),
        cmocka_unit_test( test_linked_list_get_last ),
        cmocka_unit_test( test_linked_list_get_last_list_null ),
        cmocka_unit_test( test_linked_list_get_last_list_empty ),
        cmocka_unit_test( test_linked_list_node_next ),
        cmocka_unit_test( test_linked_list_node_next_null ),
        cmocka_unit_test( test_linked_list_node_next_node_null ),
        cmocka_unit_test( test_linked_list_node_prev ),
        cmocka_unit_test( test_linked_list_node_prev_null ),
        cmocka_unit_test( test_linked_list_node_prev_node_null ),
        cmocka_unit_test( test_linked_list_node_set ),
        cmocka_unit_test( test_linked_list_node_set_node_null ),
        cmocka_unit_test( test_linked_list_node_set_data_null ),
        cmocka_unit_test( test_linked_list_node_get ),
        cmocka_unit_test( test_linked_list_node_get_node_null ),
        cmocka_unit_test( test_linked_list_node_get_cpy ),
        cmocka_unit_test( test_linked_list_node_get_cpy_node_null ),
        cmocka_unit_test( test_linked_list_node_get_cpy_data_null ),
    };
    return cmocka_run_group_tests( tests, NULL, NULL );
}

typedef uint8_t mocked_linked_list_node_t[ sizeof( linked_list_node_t ) + sizeof( int ) ];

static linked_list_node_t *mocked_linked_list_node_init( mocked_linked_list_node_t mockednode,
                                                         linked_list_t *parent,
                                                         mocked_linked_list_node_t next,
                                                         mocked_linked_list_node_t prev,
                                                         int data )
{
    linked_list_node_t *const node = (linked_list_node_t *)mockednode;
    int *const dataptr             = (int *)LINKED_LIST_NODE_DATA( node );
    node->parent                   = parent;
    node->next                     = (linked_list_node_t *)next;
    node->prev                     = (linked_list_node_t *)prev;
    *dataptr                       = data;
    return node;
}

static void mocked_linked_list_closure(void *data)
{
    check_expected(data);
}

//==============================================================================
//                         tests for linked_list_node_t
//==============================================================================

void test_linked_list_node_new( void **status )
{
    int input                          = 10;
    linked_list_t list                 = { .size = sizeof( int ) };
    mocked_linked_list_node_t mocknode = { 0 };

    mocked_calloc_p( mocked_linked_list_node_t, mocknode );

    linked_list_node_t *const ptr = linked_list_node_new( &list, &input );
    assert_ptr_equal( ptr, mocknode );
    assert_ptr_equal( ptr->parent, &list );
    assert_ptr_equal( ptr->next, NULL );
    assert_ptr_equal( ptr->prev, NULL );

    assert_memory_equal( &ptr[ 1 ], &input, sizeof( int ) );
}

void test_linked_list_node_new_mem_alloc_fails( void **status )
{
    linked_list_t list = { .size = sizeof( int ) };
    mocked_calloc_n( mocked_linked_list_node_t );

    assert_null( linked_list_node_new( &list, NULL ) );
}

void test_linked_list_node_free( void **status )
{
    linked_list_node_t node = { 0 };

    mocked_free( &node );
    linked_list_node_free( &node, NULL );
}

void test_linked_list_node_free_node_null( void **status )
{
    mocked_free( NULL );
    linked_list_node_free( NULL, NULL);
}

void test_linked_list_node_free_closure( void **status )
{
    linked_list_node_t node = { 0 };

    expect_value(mocked_linked_list_closure, data, LINKED_LIST_NODE_DATA(&node));
    mocked_free( &node );

    linked_list_node_free(&node, mocked_linked_list_closure);
}

//==============================================================================
//                           tests for linked_list_t
//==============================================================================

void test_linked_list_new( void **status )
{
    linked_list_t list = { 0 };

    mocked_calloc_p( linked_list_t, &list );

    linked_list_t *ptr = linked_list_new( sizeof( int ) );
    assert_ptr_equal( ptr, &list );
    assert_int_equal( ptr->size, sizeof( int ) );
    assert_int_equal( ptr->length, 0 );
    assert_null( ptr->first );
    assert_null( ptr->last );
}

void test_linked_list_new_mem_alloc_fails( void **status )
{
    mocked_calloc_n( linked_list_t );
    assert_null( linked_list_new( sizeof( int ) ) );
}

void test_linked_list_free_list( void **status )
{
    mocked_linked_list_node_t nodes[ 10 ] = { 0 };
    linked_list_t list                    = { .size = sizeof( int ), .length = 10U };

    for( size_t i = 0U; i < 10U; i++ )
    {
        if( 0U == i )
        {
            list.first = mocked_linked_list_node_init( nodes[ i ], &list, nodes[ i + 1U ], NULL, 10 );
        }
        else if( 9U == i )
        {
            list.last = mocked_linked_list_node_init( nodes[ i ], &list, NULL, nodes[ i - 1U ], 10 );
        }
        else
        {
            mocked_linked_list_node_init( nodes[ i ], &list, nodes[ i + 1U ], nodes[ i - 1U ], 10 );
        }
        mocked_free( nodes[ i ] );
    }

    mocked_free( &list );

    linked_list_free( &list, NULL );
}

void test_linked_list_free_list_null( void **status )
{
    linked_list_free( NULL, NULL );
}

void test_linked_list_free_empty_list( void **status )
{
    linked_list_t list = { 0 };

    mocked_free( &list );
    linked_list_free( &list, NULL );
}

void test_linked_list_append( void **status )
{
    linked_list_t list                          = { .size = sizeof( int ) };
    mocked_linked_list_node_t mockednodes[ 10 ] = { 0 };

    for( int i = 0; i < 10; i++ )
    {
        void *node = mocked_calloc_p( mocked_linked_list_node_t, mockednodes[ i ] );

        linked_list_node_t *appended = linked_list_append( &list, &i );

        assert_ptr_equal( appended, node );
        assert_memory_equal( LINKED_LIST_NODE_DATA( appended ), &i, sizeof( int ) );

        assert_ptr_equal( list.first, &mockednodes[ 0 ] );
        assert_ptr_equal( list.last, &mockednodes[ i ] );
        assert_int_equal( (size_t)i + 1, list.length );
    }

    // check that all nodes are linked correctly
    linked_list_node_t *first = list.first;
    linked_list_node_t *last  = list.last;
    for( int i = 0; i < 10; i++ )
    {
        assert_non_null( first );
        assert_non_null( last );
        assert_ptr_equal( first, &mockednodes[ i ] );
        assert_ptr_equal( last, &mockednodes[ 9 - i ] );
        first = first->next;
        last  = last->prev;
    }
}

void test_linked_list_append_first_element( void **status )
{
    linked_list_t list             = { .size = sizeof( int ) };
    mocked_linked_list_node_t node = { 0 };

    mocked_calloc_p( mocked_linked_list_node_t, node );

    int input                    = 10;
    linked_list_node_t *appended = linked_list_append( &list, &input );
    assert_ptr_equal( appended, &node );
    assert_memory_equal( LINKED_LIST_NODE_DATA( appended ), &input, sizeof( int ) );

    assert_ptr_equal( list.first, &node );
    assert_ptr_equal( list.last, &node );
    assert_int_equal( 1, list.length );
}

void test_linked_list_append_list_null( void **status )
{
    int data = 10;
    assert_null( linked_list_append( NULL, &data ) );
}

void test_linked_list_append_data_null( void **status )
{
    linked_list_t list = { 0 };
    assert_null( linked_list_append( &list, NULL ) );
}

void test_linked_list_append_mem_alloc_fails( void **status )
{
    const int data     = 10;
    linked_list_t list = { 0 };

    mocked_calloc_n( linked_list_node_t );
    assert_null( linked_list_append( &list, &data ) );
}

void test_linked_list_remove_list_null( void **status )
{
    linked_list_node_t node = { 0 };

    assert_int_equal( 1, linked_list_remove( NULL, &node, NULL ) );
}

void test_linked_list_remove_node_null( void **status )
{
    linked_list_t list = { 0 };

    assert_int_equal( 1, linked_list_remove( &list, NULL, NULL ) );
}

void test_linked_list_remove_list_not_node_parent( void **status )
{
    linked_list_t list      = { 0 };
    linked_list_node_t node = { 0 };

    assert_int_equal( 1, linked_list_remove( &list, &node, NULL ) );
}

void test_linked_list_remove_first_element( void **status )
{
    linked_list_t list                   = { 0 };
    mocked_linked_list_node_t node[ 3U ] = { 0 };

    linked_list_node_t *node0 = mocked_linked_list_node_init( node[ 0U ], &list, node[ 1U ], NULL, 1 );
    linked_list_node_t *node1 = mocked_linked_list_node_init( node[ 1U ], &list, node[ 2U ], node[ 0U ], 2 );
    linked_list_node_t *node2 = mocked_linked_list_node_init( node[ 2U ], &list, NULL, node[ 1U ], 3 );

    list.length = 3U;
    list.first  = node0;
    list.last   = node2;

    mocked_free( node0 );

    assert_int_equal( 0, linked_list_remove( &list, node0, NULL ) );
    assert_int_equal( 2U, list.length );
    assert_ptr_equal( node1, list.first );
    assert_ptr_equal( node2, list.last );

    assert_ptr_equal( node1->next, node2 );
    assert_ptr_equal( node1->prev, NULL );
    assert_ptr_equal( node2->prev, node1 );
    assert_ptr_equal( node2->next, NULL );
}

void test_linked_list_remove_last_element( void **status )
{
    linked_list_t list                   = { 0 };
    mocked_linked_list_node_t node[ 3U ] = { 0 };

    linked_list_node_t *node0 = mocked_linked_list_node_init( node[ 0U ], &list, node[ 1U ], NULL, 1 );
    linked_list_node_t *node1 = mocked_linked_list_node_init( node[ 1U ], &list, node[ 2U ], node[ 0U ], 2 );
    linked_list_node_t *node2 = mocked_linked_list_node_init( node[ 2U ], &list, NULL, node[ 1U ], 3 );

    list.length = 3U;
    list.first  = node0;
    list.last   = node2;

    mocked_free( node2 );

    assert_int_equal( 0, linked_list_remove( &list, node2, NULL ) );
    assert_int_equal( 2U, list.length );
    assert_ptr_equal( node0, list.first );
    assert_ptr_equal( node1, list.last );

    assert_ptr_equal( node0->next, node1 );
    assert_ptr_equal( node0->prev, NULL );
    assert_ptr_equal( node1->prev, node0 );
    assert_ptr_equal( node1->next, NULL );
}

void test_linked_list_remove_second_element( void **status )
{
    linked_list_t list                   = { 0 };
    mocked_linked_list_node_t node[ 3U ] = { 0 };

    linked_list_node_t *node0 = mocked_linked_list_node_init( node[ 0U ], &list, node[ 1U ], NULL, 1 );
    linked_list_node_t *node1 = mocked_linked_list_node_init( node[ 1U ], &list, node[ 2U ], node[ 0U ], 2 );
    linked_list_node_t *node2 = mocked_linked_list_node_init( node[ 2U ], &list, NULL, node[ 1U ], 3 );

    list.length = 3U;
    list.first  = node0;
    list.last   = node2;

    mocked_free( node1 );

    assert_int_equal( 0, linked_list_remove( &list, node1, NULL ) );
    assert_int_equal( 2U, list.length );
    assert_ptr_equal( node0, list.first );
    assert_ptr_equal( node2, list.last );

    assert_ptr_equal( node0->next, node2 );
    assert_ptr_equal( node0->prev, NULL );
    assert_ptr_equal( node2->prev, node0 );
    assert_ptr_equal( node2->next, NULL );
}

void test_linked_list_get_first( void **status )
{
    linked_list_node_t first = { 0 };
    linked_list_t list       = { .first = &first };
    assert_ptr_equal( &first, linked_list_get_first( &list ) );
}

void test_linked_list_get_first_list_null( void **status )
{
    assert_null( linked_list_get_first( NULL ) );
}

void test_linked_list_get_first_list_empty( void **status )
{
    linked_list_t list = { 0 };
    assert_null( linked_list_get_first( &list ) );
}

void test_linked_list_get_last( void **status )
{
    linked_list_node_t last = { 0 };
    linked_list_t list      = { .last = &last };

    assert_ptr_equal( &last, linked_list_get_last( &list ) );
}

void test_linked_list_get_last_list_null( void **status )
{
    assert_null( linked_list_get_last( NULL ) );
}

void test_linked_list_get_last_list_empty( void **status )
{
    linked_list_t list = { 0 };
    assert_null( linked_list_get_last( &list ) );
}

void test_linked_list_node_next( void **status )
{
    linked_list_node_t node[ 3U ] = {
        { .next = &node[ 1U ] },
        { .next = &node[ 2U ] },
        { .next = NULL },
    };

    assert_ptr_equal( &node[ 1 ], linked_list_node_next( &node[ 0 ] ) );
    assert_ptr_equal( &node[ 2 ], linked_list_node_next( &node[ 1 ] ) );
    assert_null( linked_list_node_next( &node[ 2 ] ) );
}

void test_linked_list_node_next_null( void **status )
{
    const linked_list_node_t node = { 0 };
    assert_null( linked_list_node_next( &node ) );
}

void test_linked_list_node_next_node_null( void **status )
{
    assert_null( linked_list_node_next( NULL ) );
}

void test_linked_list_node_prev( void **status )
{
    linked_list_node_t node[ 3U ] = {
        { .prev = NULL },
        { .prev = &node[ 0U ] },
        { .prev = &node[ 1U ] },
    };

    assert_null( linked_list_node_prev( &node[ 0 ] ) );
    assert_ptr_equal( &node[ 0 ], linked_list_node_prev( &node[ 1 ] ) );
    assert_ptr_equal( &node[ 1 ], linked_list_node_prev( &node[ 2 ] ) );
}

void test_linked_list_node_prev_null( void **status )
{
    const linked_list_node_t node = { 0 };
    assert_null( linked_list_node_prev( &node ) );
}

void test_linked_list_node_prev_node_null( void **status )
{
    assert_null( linked_list_node_prev( NULL ) );
}

void test_linked_list_node_set( void **status )
{
    linked_list_t list                   = { .size = sizeof( int ) };
    mocked_linked_list_node_t mockednode = { 0 };
    linked_list_node_t *node             = mocked_linked_list_node_init( mockednode, &list, NULL, NULL, 0 );

    const int source = 100;

    assert_int_equal( 0, linked_list_node_set( node, &source ) );
    assert_memory_equal( &source, LINKED_LIST_NODE_DATA( node ), sizeof( int ) );
}

void test_linked_list_node_set_node_null( void **status )
{
    int data = 10;
    assert_int_equal( 1, linked_list_node_set( NULL, &data ) );
}

void test_linked_list_node_set_data_null( void **status )
{
    linked_list_node_t node = { 0 };
    assert_int_equal( 1, linked_list_node_set( &node, NULL ) );
}

void test_linked_list_node_get( void **status )
{
    // prepare variables
    const int data                       = 10;
    mocked_linked_list_node_t mockednode = { 0 };
    linked_list_node_t *node             = mocked_linked_list_node_init( mockednode, NULL, NULL, NULL, data );

    void *dataptr = linked_list_node_get( node );
    assert_ptr_equal( LINKED_LIST_NODE_DATA( node ), dataptr );
    assert_memory_equal( &data, dataptr, sizeof( int ) );
}

void test_linked_list_node_get_node_null( void **status )
{
    assert_null( linked_list_node_get( NULL ) );
}

void test_linked_list_node_get_cpy( void **status )
{
    linked_list_t list                   = { .size = sizeof( int ) };
    mocked_linked_list_node_t mockednode = { 0 };
    linked_list_node_t *const node       = mocked_linked_list_node_init( mockednode, &list, NULL, NULL, 10 );

    int dest = 0;
    assert_int_equal( 0, linked_list_node_get_cpy( node, &dest ) );
    assert_int_equal( 10, dest );
}

void test_linked_list_node_get_cpy_node_null( void **status )
{
    int dest = 0;
    assert_int_equal( 1, linked_list_node_get_cpy( NULL, &dest ) );
}

void test_linked_list_node_get_cpy_data_null( void **status )
{
    linked_list_node_t node = { 0 };
    assert_int_equal( 1, linked_list_node_get_cpy( &node, NULL ) );
}
