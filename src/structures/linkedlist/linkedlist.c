#include "linkedlist.h"

#include <stdlib.h>
#include <string.h>

#define LINKED_LIST_NODE_DATA( NODE ) (void *)( &( (linked_list_node_t *)( NODE ) )[ 1U ] )

struct linked_list_node
{
    const linked_list_t *parent;
    linked_list_node_t *next;
    linked_list_node_t *prev;
};

struct linked_list
{
    linked_list_node_t *first;
    linked_list_node_t *last;
    size_t size;
    size_t length;
};

static linked_list_node_t *linked_list_node_new( const linked_list_t *const list, const void *const data )
{
    // private API no paramter checks required
    linked_list_node_t *const node = calloc( 1, sizeof( linked_list_node_t ) + list->size );
    if( NULL != node )
    {
        node->parent = list;
        if( NULL != data )
        {
            memcpy( LINKED_LIST_NODE_DATA( node ), data, list->size );
        }
    }
    return (linked_list_node_t *)node;
}

static void linked_list_node_free( linked_list_node_t *const node, linked_list_closure closure )
{
    if( closure )
    {
        closure( LINKED_LIST_NODE_DATA( node ) );
    }
    free( node );
}

linked_list_t *linked_list_new( const size_t element_size )
{
    linked_list_t *list = calloc( 1, sizeof( linked_list_t ) );
    if( NULL != list )
    {
        list->size = element_size;
    }
    return list;
}

void linked_list_free( linked_list_t *const list, linked_list_closure closure )
{
    if( NULL != list )
    {
        linked_list_node_t *node = list->first;
        while( NULL != node )
        {
            linked_list_node_t *const next = linked_list_node_next( node );
            linked_list_node_free( node, closure );
            node = next;
        }
        free( list );
    }
}

linked_list_node_t *linked_list_append( linked_list_t *const list, const void *const data )
{
    linked_list_node_t *node = NULL;
    if( NULL != list && NULL != data )
    {
        node = linked_list_node_new( list, data );
        if( NULL != node )
        {
            if( NULL != list->first )
            {
                node->prev       = list->last;
                list->last->next = node;
                list->last       = node;
            }
            else
            {
                list->first = node;
                list->last  = node;
            }
            list->length++;
        }
    }
    return node;
}

int linked_list_remove( linked_list_t *const list, linked_list_node_t *const node, linked_list_closure closure )
{
    const int result = ( ( NULL == list ) || ( NULL == node ) || ( list != node->parent ) );
    if( 0 == result )
    {
        linked_list_node_t *const prev = node->prev;
        linked_list_node_t *const next = node->next;

        // check if node is first in list
        if( NULL != prev )
        {
            prev->next = next;
        }
        else
        {
            list->first = next;
        }

        // check if node is last in list
        if( NULL != next )
        {
            next->prev = prev;
        }
        else
        {
            list->last = prev;
        }
        linked_list_node_free( node, closure );
        list->length--;
    }
    return result;
}

linked_list_node_t *linked_list_get_first( const linked_list_t *const list )
{
    linked_list_node_t *first = NULL;
    if( NULL != list )
    {
        first = list->first;
    }
    return first;
}

linked_list_node_t *linked_list_get_last( const linked_list_t *const list )
{
    linked_list_node_t *last = NULL;
    if( NULL != list )
    {
        last = list->last;
    }
    return last;
}

linked_list_node_t *linked_list_node_next( const linked_list_node_t *const node )
{
    linked_list_node_t *next = NULL;
    if( NULL != node )
    {
        next = node->next;
    }
    return next;
}

linked_list_node_t *linked_list_node_prev( const linked_list_node_t *const node )
{
    linked_list_node_t *prev = NULL;
    if( NULL != node )
    {
        prev = node->prev;
    }
    return prev;
}

int linked_list_node_set( linked_list_node_t *const node, const void *const data )
{
    const int result = ( NULL == node || NULL == data );
    if( 0 == result )
    {
        memcpy( LINKED_LIST_NODE_DATA( node ), data, node->parent->size );
    }
    return result;
}

void *linked_list_node_get( linked_list_node_t *const node )
{
    return ( NULL != node ? LINKED_LIST_NODE_DATA( node ) : NULL );
}

int linked_list_node_get_cpy( const linked_list_node_t *const node, void *const data )
{
    int result = ( NULL == node || NULL == data );
    if( 0 == result )
    {
        memcpy( data, LINKED_LIST_NODE_DATA( node ), node->parent->size );
    }
    return result;
}
