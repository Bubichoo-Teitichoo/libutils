project("structures")

set(UTILS_HEADER_DEST include/${CMAKE_PROJECT_NAME}/${PROJECT_NAME})

add_subdirectory(dynamic-array)
add_subdirectory(linkedlist)
add_subdirectory(ringbuffer)

install(
	TARGETS dynamic-array linkedlist ringbuffer 
	EXPORT ${CMAKE_PROJECT_NAME}-targets
	RUNTIME DESTINATION bin
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	PUBLIC_HEADER DESTINATION ${UTILS_HEADER_DEST}
)

install(
	EXPORT ${CMAKE_PROJECT_NAME}-targets
	DESTINATION lib/cmake
	NAMESPACE ${CMAKE_PROJECT_NAME}::
)
