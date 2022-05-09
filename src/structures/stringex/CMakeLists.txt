project("stringex" VERSION 1.0.0 LANGUAGES C)

add_library(${PROJECT_NAME} stringex.c)
target_link_libraries(${PROJECT_NAME} PUBLIC threads)
target_include_directories(${PROJECT_NAME}
	PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

install(FILES stringex.h DESTINATION ${UTILS_HEADER_DEST})
