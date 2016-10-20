project(quickfix-test)

cmake_minimum_required( VERSION 3.5)
cmake_policy(SET CMP0012 NEW)
cmake_policy(SET CMP0014 NEW)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# we need C++14 for Poco.
set (CMAKE_CXX_STANDARD 14)

include_directories(
  ${CONAN_INCLUDE_DIRS}
)

add_executable(quickfix-test test.cpp)
target_link_libraries(quickfix-test ${CONAN_LIBS})