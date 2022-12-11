cmake_minimum_required(VERSION 3.14)
project(base-python-data-science LANGUAGES Fortran CXX)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 11) # GoogleTest requires at least C++11
set(CMAKE_CXX_FLAGS="-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS="-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
set(CMAKE_SHARED_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")

#build the test runner
include_directories(external/googletest/googletest/include)
include_directories(external/googletest/googlemock/include)
add_subdirectory(external/googletest)
link_directories(external/googletest/build/lib)

# build a shared library
include_directories(include)
include_directories(src/dspack)
FILE(GLOB dspackSources src/dspack/*.cpp)
add_library(dspack SHARED ${dspackSources})
link_directories(${CMAKE_CURRENT_BINARY_DIR})

# build a test
FILE(GLOB testdspackSources test/test-dspack/*.cpp)
add_executable(test-dspack ${testdspackSources} )
target_link_libraries(test-dspack gtest gtest_main dspack)

enable_testing ()
add_test(run-test-dspack test-dspack)

# build an installer
# include (InstallRequiredSystemLibraries)
# set (CPACK_PACKAGE_NAME "base-python-data-science")
# set (CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
# set (CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
# set (CPACK_SOURCE_GENERATOR "TGZ")
# include (CPack)