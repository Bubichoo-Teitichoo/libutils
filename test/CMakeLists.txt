include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

enable_testing()

add_executable(test-linkedlist test-linkedlist.c)
target_link_libraries(test-linkedlist PRIVATE cmocka)
add_test("linkedlist" test-linkedlist)

add_executable(test-ringbuffer-blackbox test-ringbuffer-blackbox.c)
target_link_libraries(test-ringbuffer-blackbox PRIVATE cmocka)
add_test("ringbuffer-blackbox" test-ringbuffer-blackbox)

add_executable(test-stringex-blackbox test-stringex-blackbox.c)
target_link_libraries(test-stringex-blackbox PRIVATE cmocka)
add_test("stringex-blackbox" test-stringex-blackbox)
