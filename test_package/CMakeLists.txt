project(quickfix-test)

cmake_minimum_required( VERSION 3.5)
cmake_policy(SET CMP0012 NEW)
cmake_policy(SET CMP0014 NEW)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)

include_directories(
  ${CONAN_INCLUDE_DIRS}

)

add_executable(quickfix-test test.cpp Application.cpp)
target_link_libraries(quickfix-test Threads::Threads ${CONAN_LIBS})
