cmake_minimum_required(VERSION 3.8)
project("libutils" VERSION 0.1.0 LANGUAGES C)

include(cmake/base.config.cmake)

option(BUILD_TESTING            "build unit tests"          OFF)
option(BUILD_SHARED_LIBS        "build shared libraries"    OFF)
option(LIBUTILS_BUILD_DOCS      "build documentation"       OFF)

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