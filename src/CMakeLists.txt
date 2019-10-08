add_executable(${PROJECT_NAME} main.cpp parallel_for.h prefix_sum.h measure_time.h)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
