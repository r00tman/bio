project(bio)

add_library(bio STATIC ./basic_logger.cpp)

install (TARGETS bio DESTINATION lib)
install (FILES container.h file_stream.h file.h basic_logger.h byte_stream.h screen_stream.h stream_utils.h stream.h DESTINATION include/bio)

enable_testing()
add_subdirectory(tests)
