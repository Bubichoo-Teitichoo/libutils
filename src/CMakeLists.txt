set(UTILS_HEADER_DEST include/${CMAKE_PROJECT_NAME})

# basic data types
add_subdirectory(structures)

# extended funtionality and cross platform wrapper
add_subdirectory(async)

# utilities
add_subdirectory(logging)

install(
	TARGETS logging
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
