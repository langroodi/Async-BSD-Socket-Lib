if(EXISTS "/home/runner/work/Async-BSD-Socket-Lib/Async-BSD-Socket-Lib/build/async_bsd_socket_lib_test[1]_tests.cmake")
  include("/home/runner/work/Async-BSD-Socket-Lib/Async-BSD-Socket-Lib/build/async_bsd_socket_lib_test[1]_tests.cmake")
else()
  add_test(async_bsd_socket_lib_test_NOT_BUILT async_bsd_socket_lib_test_NOT_BUILT)
endif()
