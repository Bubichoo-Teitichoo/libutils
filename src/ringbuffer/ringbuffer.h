///
/// @file ringbuffer.h
/// @brief Implementation of a Ring Buffer
///
#if !defined( __RINGBUFFER_H__ )
#define __RINGBUFFER_H__

#include <stddef.h>

///
/// Convenience Macro for creating a new ringbuffer with given @p TYPE and
/// a @p CAPACITY
///
#define RING_BUFFER_NEW( TYPE, CAPACITY ) ( ring_buffer_new( ( CAPACITY ), sizeof( TYPE ) ) )

///
/// Convenience Macro to pop an element from the ringbuffer and derefernce it
/// automatically. If the buffer is empty @p DEFAULT will be returned.
///
#define RING_BUFFER_POP( TYPE, RB, DEFAULT ) \
    ( 0 != ring_buffer_items( ( RB ) ) ? ( *( (TYPE *)ring_buffer_pop( ( RB ) ) ) ) : ( DEFAULT ) )

typedef struct ring_buffer ring_buffer_t;

/// @memberof ring_buffer
///
/// @brief Create a new ring buffer
///
/// Allocate a new empty ring buffer with a maximum of @p capacity elements
/// where each element uses @p size bytes of storage.
///
/// By default overriding is enabled.
///
/// @see ring_buffer_enable_override()
///
/// @param[in]  capacity            Number of element the buffer shall hold.
/// @param[in]  size                Size of a single elements that in placed
///                                 inside the buffer.
///
/// @retval     ring_buffer_t*  pointer to the newly created ring buffer on
///                             success. __[transfer: full]__
/// @retval     NULL            when memory allocation fails
///
ring_buffer_t *ring_buffer_new( const size_t capacity, const size_t size );

/// @memberof ring_buffer
///
/// @brief Free the allocated memory.
///
/// This will free the array where data is store aswell. Every pointer that
/// was retrieved using ring_buffer_pop() will be invalid after a call to this
/// function and shall not be dereferenced.
///
/// @param[in]  rb      pointer to the buffer that shall be free'd.
///                     __[transfer: full]__
///
void ring_buffer_free( ring_buffer_t *const rb );

/// @memberof ring_buffer
///
/// @brief En-/Disable Overriding
///
/// When enabled new data will override old data.
///
/// @param[in]  rb      The buffer overriding shall be enabled for.
/// @param[in]  enable  If set to 0 override will be disabled for subsequent
///                     ring_buffer_push() calls.
/// 
/// @retval 0   on success
/// @retval 1   if @p rb is NULL
///
int ring_buffer_enable_override( ring_buffer_t *const rb, const int enable );


/// @memberof ring_buffer
///
/// @brief Get the number of items stored in the buffer.
///
/// @param[in]  rb  Buffer
///
/// @returns the current number of items stored in the buffer.
///
size_t ring_buffer_items( const ring_buffer_t *const rb );

/// @memberof ring_buffer
///
/// @brief Push an element into the buffer
///
/// If overriding is enbaled this function will override old data when the
/// buffer is full.
///
/// @see ring_buffer_new()
/// @see ring_buffer_enable_override()
///
/// @param[in]  rb      Buffer the element shall be added to.
/// @param[in]  data    Pointer to the data that shall be put into the buffer.
///                     __[transfer: none]__
///
/// @retval     0   On Success
/// @retval     1   If the buffer is full and overriding is disabled or the one
///                 of the given arguments was NULL.
///
int ring_buffer_push( ring_buffer_t *const rb, const void *const data );

/// @memberof ring_buffer
///
/// @brief Remove the next element from the buffer
///
/// Get the oldest element from the buffer.
///
/// @note   If the pointer to the element is stored be carefull with subsequent
///         calls to ring_buffer_push() because they might override the data
///         stored of that element.
///
/// @param[in]  rb      Buffer to get the element from.
///
/// @retval     void*   Address to the element
/// @retval     NULL    If the buffer was empty or @p rb was NULL.
///
void *ring_buffer_pop( ring_buffer_t *const rb );

#endif   // __RINGBUFFER_H__