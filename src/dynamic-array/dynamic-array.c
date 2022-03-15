#include "dynamic-array.h"
#include <string.h>

#define ARRAY_PTR_IDX( array, idx ) ( (void *)( ( (char *)array->data ) + ( array->elmnt_size * ( idx ) ) ) )

///
///
///
struct dynamic_array
{
    void *data;          ///< Memory to store array data in
    size_t len;          ///< Number of array elements
    size_t size;         ///< Number of available spots in array
    size_t elmnt_size;   ///< Size of an element in the array
};

static int dynamic_array_init( dynamic_array_t *array, const size_t element_size, const size_t initial_size )
{
    // private method...no need to check arguments
    array->elmnt_size = element_size;
    array->size       = ( 0 != initial_size ) ? initial_size : 10U;
    array->data       = calloc( array->size, element_size );
    return ( NULL == array->data );
}


static int dynamic_array_resize( dynamic_array_t *array, const size_t size )
{
    void *data = realloc( array->data, array->elmnt_size * size );
    if( NULL != data )
    {
        array->data = data;
        array->size = size;
    }
    return ( NULL == data );
}


dynamic_array_t *dynamic_array_new( const size_t element_size, const size_t initial_size )
{
    dynamic_array_t *array = malloc( sizeof( dynamic_array_t ) );
    if( NULL != array && 1 == dynamic_array_init( array, element_size, initial_size ) )
    {
        dynamic_array_free( array );
        array = NULL;
    }
    return array;
}


void dynamic_array_free( dynamic_array_t *array )
{
    if( array )
    {
        free( array->data );
        free( array );
    }
}

void *dynamic_array_get( const dynamic_array_t *array, const size_t index )
{
    void *elmnt = NULL;
    if( NULL != array && index < array->len )
    {
        elmnt = ARRAY_PTR_IDX( array, index );
    }
    return elmnt;
}

void *dynamic_array_set( dynamic_array_t *array, void *data, const size_t index )
{
    void *item = NULL;
    if( NULL != array && NULL != data )
    {
        if( index < array->len )
        {
            item = memcpy( ARRAY_PTR_IDX( array, index ), data, array->elmnt_size );
        }
        else
        {
            item = dynamic_array_append( array, data );
        }
    }
    return item;
}

void *dynamic_array_append( dynamic_array_t *array, const void *data )
{
    void *item = NULL;
    if( NULL != array && NULL != data )
    {
        if( array->size > array->len || ( 0 == dynamic_array_resize( array, array->size * 2 ) ) )
        {
            item = ARRAY_PTR_IDX( array, array->len );
            memcpy( item, data, array->elmnt_size );
            array->len++;
        }
    }
    return item;
}

void *dynamic_array_insert( dynamic_array_t *array, const void *data, const size_t index )
{
    void *item = NULL;

    if( NULL != array && NULL != data )
    {
        if( index < array->len )
        {
            if( array->size > array->len || ( 0 == dynamic_array_resize( array, array->size * 2 ) ) )
            {
                void *from          = ARRAY_PTR_IDX( array, index );
                void *to            = ARRAY_PTR_IDX( array, index + 1 );
                const size_t offset = ( array->len - index ) * array->elmnt_size;
                memmove( to, from, offset );
                item = memcpy( from, data, array->elmnt_size );
                array->len++;
            }
        }
        else
        {
            item = dynamic_array_append( array, data );
        }
    }
    return item;
}

void *dynamic_array_insert_fast( dynamic_array_t *array, const void *data, const size_t index )
{
    void *item = NULL;

    if( NULL != array && NULL != data )
    {
        if( index < array->len )
        {
            if( array->size > array->len || ( 0 == dynamic_array_resize( array, array->size * 2 ) ) )
            {
                // move element at @p index to the back.
                void *from = ARRAY_PTR_IDX( array, index );
                void *to   = ARRAY_PTR_IDX( array, array->len );
                memcpy( to, from, array->elmnt_size );
                // insert new element
                item = memcpy( from, data, array->elmnt_size );
                array->len++;
            }
        }
        else
        {
            // insert item at the back because given index
            // is larger than current item count
            item = dynamic_array_append( array, data );
        }
    }
    return item;
}

int dynamic_array_remove( dynamic_array_t *array, const size_t index )
{
    if( NULL != array && index < array->len )
    {
        if( array->len != index - 1 )
        {
            void *from       = ARRAY_PTR_IDX( array, index + 1 );
            void *to         = ARRAY_PTR_IDX( array, index );
            const size_t len = ( array->len - ( index + 1 ) ) * array->elmnt_size;
            memmove( to, from, len );
        }
        array->len--;
        return 0;
    }
    return 1;
}

int dynamic_array_remove_fast( dynamic_array_t *array, const size_t index )
{
    if( NULL != array && index < array->len )
    {
        // override the item to remove with the last item in array
        if( array->len != index - 1 )
        {
            memcpy( ARRAY_PTR_IDX( array, index ), ARRAY_PTR_IDX( array, array->len - 1 ), array->elmnt_size );
        }
        array->len--;
        return 0;
    }
    return 1;
}

int dynamic_array_clear( dynamic_array_t *array )
{
    array->len = 0;
    memset( array->data, 0, array->elmnt_size * array->size );
    return 0;
}

size_t dynamic_array_len( const dynamic_array_t *array )
{
    return array->len;
}

int dynamic_array_foreach( const dynamic_array_t *array, dynamic_array_iterator it, void *userdata )
{
    int result = 1;

    if( NULL != array && NULL != it )
    {
        size_t i = 0U;
        for( ; i < array->len; i++ )
        {
            // break loop if user function returns non-zero value
            result = it( array, i, ARRAY_PTR_IDX( array, i ), userdata );
            if( 0 != result )
            {
                break;
            }
        }
    }
    return result;
}
