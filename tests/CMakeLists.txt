enable_testing()

include_directories(. ../)

add_executable(basic_io_test basic_io_test.cpp)
target_link_libraries(basic_io_test bio)

add_executable(container_basic_test container_basic_test.cpp)
target_link_libraries(container_basic_test bio polyml)

add_test(basic_io_test ${CMAKE_CURRENT_BINARY_DIR}/basic_io_test)
add_test(container_basic_test ${CMAKE_CURRENT_BINARY_DIR}/container_basic_test)
