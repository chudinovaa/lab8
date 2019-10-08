add_executable(prefix_sum_test prefix_sum_test.cpp)
target_link_libraries(prefix_sum_test OpenMP::OpenMP_CXX gtest gtest_main)
add_test(NAME prefix_sum_test COMMAND prefix_sum_test)

add_executable(parallel_for_test parallel_for_test.cpp)
target_link_libraries(parallel_for_test gtest gtest_main)
add_test(NAME parallel_for_test COMMAND parallel_for_test)
