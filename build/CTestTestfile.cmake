# CMake generated Testfile for 
# Source directory: /home/thom/repos/base-cpp-data-science
# Build directory: /home/thom/repos/base-cpp-data-science/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(run-test-dspack "test-dspack")
set_tests_properties(run-test-dspack PROPERTIES  _BACKTRACE_TRIPLES "/home/thom/repos/base-cpp-data-science/CMakeLists.txt;31;add_test;/home/thom/repos/base-cpp-data-science/CMakeLists.txt;0;")
subdirs("external/googletest")
