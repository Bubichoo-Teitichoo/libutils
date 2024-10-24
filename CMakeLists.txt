cmake_minimum_required(VERSION 3.8)
project("libutils" VERSION 0.1.0 LANGUAGES C)

include(cmake/base.config.cmake)

option(LIBUTILS_BUILD_DOCS      "build documentation"       OFF)
option(CMAKE_EXPORT_COMPILE_COMMANDS "If enabled, CMake will generate a compile_commands.json to use with different tools like clangd. For better integration the file will be linked in the current source directory." ON)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    cmake_language(DEFER CALL
        file
            CREATE_LINK
            ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
            COPY_ON_ERROR SYMBOLIC
)
endif()

add_subdirectory(src)

if (BUILD_TESTING)
    enable_testing()
    add_subdirectory(lib/cmocka cmocka)
    add_subdirectory(test)
endif()

if(LIBUTILS_BUILD_DOCS)
    find_package(Doxygen REQUIRED)

    set(DOXYGEN_GENERATE_HTML YES)

    set(DOXYGEN_PROJECT_BRIEF "A collection of utility functions and structures.")
    set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
    set(DOXYGEN_SORT_MEMBER_DOCS NO)
    set(DOXYGEN_EXTRACT_PACKAGE YES)
    set(DOXYGEN_INLINE_SIMPLE_STRUCTS YES)
    set(DOXYGEN_TYPEDEF_HIDES_STRUCT YES)
    doxygen_add_docs(utils-docs
        ${PROJECT_SOURCE_DIR}/src
        COMMENT "Generate Documentation")
endif()
