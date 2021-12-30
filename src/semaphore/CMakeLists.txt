project("semaphore" VERSION 1.0.0 LANGUAGES C)

include(CheckIncludeFile)

check_include_file("semaphore.h" SEMAPHORE_H_AVAILABLE)

find_package(Threads REQUIRED)

if ("${SEMAPHORE_H_AVAILABLE}" STREQUAL "")
	add_library(${PROJECT_NAME} semaphore.c)
	target_include_directories(${PROJECT_NAME}
		PUBLIC 
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
			$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
	)
else()
	add_library(${PROJECT_NAME} INTERFACE)
	target_link_libraries(${PROJECT_NAME} INTERFACE Threads::Threads)
endif()
