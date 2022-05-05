# Ringbuffer

A generic and minimalistic implementation of a fixed size FIFO (first in, first 
out) array.
The buffer has two operating modes: 
- __overriding__: Oldest entries will be overriden when the buffer is full
- __non-overriding__: No entries will be overriden. Instead `ring_buffer_push()` will return a non-zero value.

The mode can be set dynamically using `ring_buffer_enable_override()`.

> :warning: Warning: The implementation is not thread-safe. If you want to use it in a 
> multi-threaded environment make sure to serialize the calls to 
> `ring_buffer_push()` and `ring_buffer_pop()`.

```c
// create a new buffer that can hold up to 10 integers
ring_buffer_t *rb = ring_buffer_new( 10, sizeof( int ) );

// ...or use the convinience macro instead
ring_buffer_t *rb = RING_BUFFER_NEW( int, 10 );
```

Because of the generic implementation items have to be added to the buffer by
passing a pointer to `ring_buffer_push()` instead of the value. The value of
the passed pointer will be copied to the buffer using `memcpy()`.

```c
// ...

int value = 10;
if ( ring_buffer_push( rb, &value ) )
{
    // handle error
}
```

Same applies to `ring_buffer_pop()`. It will return a pointer to the item 
inside of the buffer. 

> Note: susequent calls to `ring_buffer_push()` may change the value
> of the pointer aquired via `ring_buffer_pop()`.

```c
// ...
int *const valueptr = ring_buffer_pop( rb );
if ( NULL == valueptr )
{
    // buffer is empty
}
int value = *valueptr; 

// ...or use the convinience macro
int value = RING_BUFFER_POP( int, rb, -1 );
if ( -1 == value )
{
    // buffer is empty
}
```
