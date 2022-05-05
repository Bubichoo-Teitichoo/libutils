project("threads" VERSION 1.0.0 LANGUAGES C)

include(CheckIncludeFile)

check_include_file("threads.h" THREADS_H_AVAILABLE)

find_package(Threads REQUIRED)

if ("${THREADS_H_AVAILABLE}" STREQUAL "")
	if (MSVC)
		add_library(${PROJECT_NAME} threads.msvc.c)
	else()
		add_library(${PROJECT_NAME} threads.posix.c)
	endif()
	target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
	target_include_directories(${PROJECT_NAME}
		PUBLIC 
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
			$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
	)

	install(FILES threads.h DESTINATION ${UTILS_HEADER_DEST})
else()
	add_library(${PROJECT_NAME} INTERFACE)
	target_link_libraries(${PROJECT_NAME} INTERFACE Threads::Threads)
endif()
