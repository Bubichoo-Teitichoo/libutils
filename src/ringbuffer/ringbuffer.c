#include "ringbuffer.h"

#include <stdlib.h>
#include <string.h>

///
/// @var size_t ring_buffer::capacity
///         @brief Number of elements the buffer can hold
/// @var size_t ring_buffer::size
///         @brief Size of a single element in the buffer
/// @var size_t ring_buffer::head
///         @brief Index where the next element will be stored
/// @var size_t ring_buffer::tail
///         @brief Index of the oldest element in the buffer
/// @var int ring_buffer::override
///         @brief Flag to indicate weather overriding is enabled or not.
///
struct ring_buffer
{
    const size_t capacity;
    const size_t size;
    int override;
    void *head;
    void *tail;
};

static inline void *ring_buffer_idx_to_ptr( const ring_buffer_t *const rb, const size_t idx )
{
    // assuming that char is the smalles possible datatype (1 Byte)
    unsigned char *dataptr = (unsigned char *)( &rb[ 1 ] );
    return (void *)( &dataptr[ rb->size * idx ] );
}

static inline size_t ring_buffer_ptr_to_idx( const ring_buffer_t *const rb, const void *const ptr )
{
    const unsigned char *const beginptr = (unsigned char *)( &rb[ 1 ] );
    const unsigned char *const dataptr  = (unsigned char *)ptr;
    return ( dataptr - beginptr ) / rb->size;
}

/// @memberof ring_buffer
///
/// @brief Get the next item after @p ptr
///
/// The maximum capacity is also factored in so a wrap around might happen
/// when calling this function
///
static inline void *ring_buffer_next_ptr( const ring_buffer_t *const rb, const void *const ptr )
{
    // calculate the next index factoring in the maximum capacity.
    const size_t nextidx = ( ring_buffer_ptr_to_idx( rb, ptr ) + 1U ) % rb->capacity;
    // convert index back to a pointer
    return ring_buffer_idx_to_ptr( rb, nextidx );
}

static inline int ring_buffer_full( const ring_buffer_t *const rb )
{
    return ( ( 0 == rb->override ) && rb->capacity <= ring_buffer_items( rb ) );
}

ring_buffer_t *ring_buffer_new( const size_t capacity, const size_t size )
{
    // single allocation of all memory needed
    const size_t memsize    = sizeof( ring_buffer_t ) + ( capacity * size );
    ring_buffer_t *const rb = calloc( 1, memsize );
    if( NULL != rb )
    {
        const ring_buffer_t tmp = {
            .capacity = capacity,
            .size     = size,
            .override = 1,
            .head     = ring_buffer_idx_to_ptr( rb, 0U ),
            .tail     = NULL,
        };
        memcpy( rb, &tmp, memsize );
    }
    return rb;
}

void ring_buffer_free( ring_buffer_t *const rb )
{
    free( rb );
}

int ring_buffer_enable_override( ring_buffer_t *const rb, const int enable )
{
    const int result = ( rb == NULL );
    if( 0 == result )
    {
        rb->override = enable;
    }
    return result;
}

size_t ring_buffer_items( const ring_buffer_t *const rb )
{
    size_t items = 0U;
    if( NULL != rb && NULL != rb->tail )
    {
        const size_t headidx = ring_buffer_ptr_to_idx( rb, rb->head );
        const size_t tailidx = ring_buffer_ptr_to_idx( rb, rb->tail );
        if( headidx > tailidx )
        {
            items = headidx - tailidx;
        }
        else
        {
            items = headidx + ( rb->capacity - tailidx );
        }
    }
    return items;
}

int ring_buffer_push( ring_buffer_t *const rb, const void *const data )
{
    const int result = ( ( NULL == rb ) || ( NULL == data ) || ( 1 == ring_buffer_full( rb ) ) );
    if( 0 == result )
    {
        void *const nextptr = ring_buffer_next_ptr( rb, rb->head );
        // copy data into buffer
        memcpy( rb->head, data, rb->size );
        if( 1 == rb->override && rb->head == rb->tail )
        {
            rb->tail = nextptr;
        }
        else if( NULL == rb->tail )
        {
            rb->tail = rb->head;
        }
        rb->head = nextptr;
    }
    return result;
}

void *ring_buffer_pop( ring_buffer_t *rb )
{
    void *data = NULL;
    if( NULL != rb && NULL != rb->tail )
    {
        void *const nextptr = ring_buffer_next_ptr( rb, rb->tail );
        data                = rb->tail;
        rb->tail            = ( ( nextptr == rb->head ) ? NULL : nextptr );
    }
    return data;
}
