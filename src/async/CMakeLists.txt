project("async")

set(UTILS_HEADER_DEST include/${CMAKE_PROJECT_NAME}/${PROJECT_NAME})

add_subdirectory(semaphore)
add_subdirectory(threads)

install(
	TARGETS semaphore threads
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
