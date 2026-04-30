# CMake generated Testfile for 
# Source directory: /home/eric-hermosis/Escritorio/Blazar/tests
# Build directory: /home/eric-hermosis/Escritorio/Blazar/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[test-operations]=] "/home/eric-hermosis/Escritorio/Blazar/build/tests/test-operations")
set_tests_properties([=[test-operations]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/eric-hermosis/Escritorio/Blazar/tests/CMakeLists.txt;31;add_test;/home/eric-hermosis/Escritorio/Blazar/tests/CMakeLists.txt;0;")
add_test([=[test-shape]=] "/home/eric-hermosis/Escritorio/Blazar/build/tests/test-shape")
set_tests_properties([=[test-shape]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/eric-hermosis/Escritorio/Blazar/tests/CMakeLists.txt;31;add_test;/home/eric-hermosis/Escritorio/Blazar/tests/CMakeLists.txt;0;")
add_test([=[test-storage]=] "/home/eric-hermosis/Escritorio/Blazar/build/tests/test-storage")
set_tests_properties([=[test-storage]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/eric-hermosis/Escritorio/Blazar/tests/CMakeLists.txt;31;add_test;/home/eric-hermosis/Escritorio/Blazar/tests/CMakeLists.txt;0;")
add_test([=[test-strides]=] "/home/eric-hermosis/Escritorio/Blazar/build/tests/test-strides")
set_tests_properties([=[test-strides]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/eric-hermosis/Escritorio/Blazar/tests/CMakeLists.txt;31;add_test;/home/eric-hermosis/Escritorio/Blazar/tests/CMakeLists.txt;0;")
add_test([=[test-types]=] "/home/eric-hermosis/Escritorio/Blazar/build/tests/test-types")
set_tests_properties([=[test-types]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/eric-hermosis/Escritorio/Blazar/tests/CMakeLists.txt;31;add_test;/home/eric-hermosis/Escritorio/Blazar/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
