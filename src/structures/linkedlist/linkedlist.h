#if !defined( __LINKED_LIST_H__ )
#define __LINKED_LIST_H__

#include <stddef.h>

typedef struct linked_list linked_list_t;
typedef struct linked_list_node linked_list_node_t;

typedef void ( *linked_list_closure )( void *data );

///
#define LINKED_LIST_NEW( TYPE ) linked_list_new( sizeof( TYPE ) )

/// @memberof linked_list
///
/// @brief
/// @param element_size
/// @return
linked_list_t *linked_list_new( const size_t element_size );

/// @memberof linked_list
///
/// @brief
/// @param list
void linked_list_free( linked_list_t *const list, linked_list_closure closure );

/// @memberof linked_list
///
/// @brief
/// @param list
/// @param data
/// @return
linked_list_node_t *linked_list_append( linked_list_t *const list, const void *const data );

/// @memberof linked_list
///
/// @brief
/// @param list
/// @param node
/// @return
int linked_list_remove( linked_list_t *const list, linked_list_node_t *const node, linked_list_closure closure );

/// @memberof linked_list
///
/// @brief
/// @param list
/// @return
linked_list_node_t *linked_list_get_first( const linked_list_t *const list );

/// @memberof linked_list
///
///
/// @brief
/// @param list
/// @return
linked_list_node_t *linked_list_get_last( const linked_list_t *const list );

/// @memberof linked_list_node
///
/// @brief
/// @param node
/// @return
linked_list_node_t *linked_list_node_next( const linked_list_node_t *const node );

/// @memberof linked_list_node
///
/// @brief
/// @param node
/// @return
linked_list_node_t *linked_list_node_prev( const linked_list_node_t *const node );

/// @memberof linked_list_node
///
/// @brief
/// @param node
/// @param data
/// @return
int linked_list_node_set( linked_list_node_t *const node, const void *const data );

/// @memberof linked_list_node
///
/// @brief
/// @param node
/// @return
void *linked_list_node_get( linked_list_node_t *const node );

/// @memberof linked_list_node
///
/// @brief
/// @param node
/// @param data
/// @return
int linked_list_node_get_cpy( const linked_list_node_t *const node, void *const data );


#endif   // __LINKED_LIST_H__