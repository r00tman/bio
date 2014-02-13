project(containers-test)

add_executable(containers-test main.cpp)
target_link_libraries(containers-test polyml)

enable_testing()
add_subdirectory(tests)
