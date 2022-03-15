project("dynamic-array" VERSION 1.0.0 LANGUAGES C)

add_library(${PROJECT_NAME} dynamic-array.c)
target_include_directories(${PROJECT_NAME}
	PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)