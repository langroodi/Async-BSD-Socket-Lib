add_test( NetworkSocketTest.TcpClientConstructor /home/runner/work/Async-BSD-Socket-Lib/Async-BSD-Socket-Lib/build/async_bsd_socket_lib_test [==[--gtest_filter=NetworkSocketTest.TcpClientConstructor]==] --gtest_also_run_disabled_tests)
set_tests_properties( NetworkSocketTest.TcpClientConstructor PROPERTIES WORKING_DIRECTORY /home/runner/work/Async-BSD-Socket-Lib/Async-BSD-Socket-Lib/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( NetworkSocketTest.TcpListenerConstructor /home/runner/work/Async-BSD-Socket-Lib/Async-BSD-Socket-Lib/build/async_bsd_socket_lib_test [==[--gtest_filter=NetworkSocketTest.TcpListenerConstructor]==] --gtest_also_run_disabled_tests)
set_tests_properties( NetworkSocketTest.TcpListenerConstructor PROPERTIES WORKING_DIRECTORY /home/runner/work/Async-BSD-Socket-Lib/Async-BSD-Socket-Lib/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( NetworkSocketTest.UdpClientConstructor /home/runner/work/Async-BSD-Socket-Lib/Async-BSD-Socket-Lib/build/async_bsd_socket_lib_test [==[--gtest_filter=NetworkSocketTest.UdpClientConstructor]==] --gtest_also_run_disabled_tests)
set_tests_properties( NetworkSocketTest.UdpClientConstructor PROPERTIES WORKING_DIRECTORY /home/runner/work/Async-BSD-Socket-Lib/Async-BSD-Socket-Lib/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( async_bsd_socket_lib_test_TESTS NetworkSocketTest.TcpClientConstructor NetworkSocketTest.TcpListenerConstructor NetworkSocketTest.UdpClientConstructor)