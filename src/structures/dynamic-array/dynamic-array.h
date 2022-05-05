#if !defined(__DYNAMIC_ARRAY_H__)
#define __DYNAMIC_ARRAY_H__

#include <stdlib.h>

#define DYNAMIC_ARRAY_GET_CAST( array, index, type ) ( *( (type *)( dynamic_array_get( array, ( index ) ) ) ) )

typedef struct dynamic_array dynamic_array_t;

///
/// @memberof dynamic_array
///
/// @brief Interface called from array_foreach()
///
/// @param[in]  array
/// @param[in]  index        Index of @p element inside @p array
/// @param[in]  element      Pointer to the array element at @p index
/// @param[in]  userdata     user-definable data passed e.g. to store results.
///                         _[nullable]_
///
typedef int ( *dynamic_array_iterator )( const dynamic_array_t *array, const size_t index, void *element, void *userdata );

///
/// @memberof dynamic_array
///
/// @brief Create new Array
///
/// Create a new Array structure where each entry has @p element_size bytes and
/// an @p initial_size reserved allocated elements.
///
/// @param[in]  element_size    Size of the array elements
/// @param[in]  initial_size    Number of elements that shall be allocated
///                             during initialization. If you expect a large
///                             number of elements set this value accordingly to
///                             avoid a lot of reallocations. If 0 is given a
///                             default value of 10 is used
///
/// @retval Array*  On success a pointer to a newly allocated structure.
///                 _[callee allocates]_
/// @retval NULL    When an invalid parameter was given i.e @p element_size == 0
///
dynamic_array_t *dynamic_array_new( const size_t element_size, const size_t initial_size );

///
/// @memberof dynamic_array
///
/// @brief free memory of @p array
///
/// Free all the memory allocated used by Array including data. After calling
/// this the pointer given is invalid and should no longer be used. If @p array
/// equals NULL nothing happens.
///
/// @param[in]  array   Pointer to the array structure that shall be freed.
///                     _[transfer full, nullable]_
///
void dynamic_array_free( dynamic_array_t *array );

///
/// @memberof dynamic_array
///
/// @brief Get element at index
///
/// Returns the element at @p index of @p array
///
/// @param[in]  array   Array of elements
/// @param[in]  index   Index of the wanted element
///
/// @retval void*   Address to the element. This has to be casted to the desired
///                 pointer type. _[transfer none]_
/// @retval NULL    If the given arguments are invalid i.e. @p index equals NULL
///                 or @p index is equal or bigger than Array::len
///
void *dynamic_array_get( const dynamic_array_t *array, const size_t index );

/// 
/// @memberof dynamic_array
/// 
/// @brief Override element at @p index with @p data
/// 
/// @param[in]  array   array you want to set
/// @param[in]  data    pointer to the object you want to set at @p index 
///                     _[transfer: none]_
/// @param[in]  index   index of the element you want to override. If @p index
///                     is larger then dynamic_array::len dynamic_array_append
///                     will be called.
/// 
/// @retval void*   Address to the element. This has to be casted to the desired
///                 pointer type. _[transfer none]_
/// @retval NULL    If the given arguments are invalid i.e. @p array or @p data
///                 are NULL 
void *dynamic_array_set( dynamic_array_t *array, void *data, const size_t index );

///
/// @memberof dynamic_array
///
/// @brief Add element to array
///
/// Append @p data to @p array. This will copy the value of @p data into the
/// array using memcpy.
///
/// @param[in]  array   Array you want to add @p data to
/// @param[in]  data    Data to assign to the new array element.
///                     _[transfer none]_
///
/// @retval void*   Pointer to the array element that now holds the same data as
///                 @p data. _[transfer none]_
/// @retval NULL    on failure i.e. invalid arguments given.
///
void *dynamic_array_append( dynamic_array_t *array, const void *data );

///
/// @memberof dynamic_array
///
/// @brief Insert element into Array
///
/// Insert a new element into the array at @p index. This function will keep the
/// order of the array by moving each element by one place beginning at
/// @p index. This will result in a lot of memcpy operations in large arrays.
///
/// If @p index equals dynamic_array_t::len - 1 array_append() will be called
/// internaly.
///
/// @param[in]  array   Array the @p data shall be added to
/// @param[in]  data    Data to assign to the new array element.
///                     _[transfer none]_
/// @param[in]  index   Index @p data shall be inserted at.
///
/// @retval void*   Pointer to the array element that now holds the same data as
///                 @p data. _[transfer none]_
/// @retval NULL    on failure i.e. invalid arguments given.
///
void *dynamic_array_insert( dynamic_array_t *array, const void *data, const size_t index );

///
/// @memberof dynamic_array
///
/// @brief Insert element into Array
///
/// Insert a new element into the array at @p index. This function will destory
/// the order of the array in favor of speed. This method will copy the element
/// at @p index to the end before inserting @p data.
///
/// If @p index equals dynamic_array_t::len - 1 array_append() will be called
/// internaly.
///
/// @param[in]  array   Array the @p data shall be added to
/// @param[in]  data    Data to assign to the new array element.
///                     _[transfer none]_
/// @param[in]  index   Index @p data shall be inserted at.
///
/// @retval void*   Pointer to the array element that now holds the same data as
///                 @p data. _[transfer none]_
/// @retval NULL    on failure i.e. invalid arguments given.
///
void *dynamic_array_insert_fast( dynamic_array_t *array, const void *data, const size_t index );

///
/// @memberof dynamic_array
///
/// @brief Remove element from Array.
///
/// Remove the element at @p index from the array. This function will keep the
/// order of the Array by moving all element following after @p index one to the
/// front.
///
/// @param[in]  array   Array where the element at @p index shall be removed
/// @param[in]  index   Index of the element that shall be removed;
///
/// @retval 0   on sucess
/// @retval 1   if array equals NULL or index is equal to or greater than
///             dynamic_array_t::len
///
int dynamic_array_remove( dynamic_array_t *array, const size_t index );

///
/// @memberof dynamic_array
///
/// @brief Remove element from Array
///
/// Remove the element at @p index from the array. This function will destroy
/// the order of @p array by moving the last element to @p index
///
/// @param[in]  array   Array where the element at @p index shall be removed.
/// @param[in]  index   Index of the element that shall be removed.
///
/// @retval 0   on sucess
/// @retval 1   if array equals NULL or index is equal to or greater than
///             dynamic_array_t::len
///
int dynamic_array_remove_fast( dynamic_array_t *array, const size_t index );

///
/// @memberof dynamic_array
///
/// @brief Clear Array
///
///	This will set dynamic_array_t::len to 0 and fill the allocated memory of
/// dynamic_array_t::data with 0 using memset().
///
/// @param[in] array Array to clear
///
/// @return 0
///
int dynamic_array_clear( dynamic_array_t *array );

///
/// @memberof dynamic_array
///
/// @brief Get length of array
///
/// This returns the current number of elements inside the array. This function
/// does no check wheather a NULL Pointer was given.
///
/// @param[in]  array   Array to get the length from
///
/// @return length of array
///
size_t dynamic_array_len( const dynamic_array_t *array );

///
/// @memberof dynamic_array
///
/// @brief Iterate an Array
///
/// By implementing an ArrayIterator-Function one can skip writing a for loop
/// iterating the Array and simply call this function.
///
/// To stop the iteration @p it simply has to return a non-zero value.
///
/// @param[in]  array       Array to iterate.
/// @param[in]  it          Custom User-Function to call with each element.
/// @param[in]  userdata    Data that is passed into ArrayIterator _[nullable]_
///
/// @retval 1   if invalid arguments were given
/// @retval 0   on success.
///
int dynamic_array_foreach( const dynamic_array_t *array, dynamic_array_iterator it, void *userdata );

#endif // __DYNAMIC_ARRAY_H__