# Executables
add_executable(mtrp-base64-table-generator "${CMAKE_CURRENT_SOURCE_DIR}/tools/table_generator.cpp")
add_executable(mtrp-base64-benchmark "${CMAKE_CURRENT_SOURCE_DIR}/tools/benchmark.cpp")

target_link_libraries(mtrp-base64-benchmark mtrp-base64)

set_target_properties(mtrp-base64-table-generator PROPERTIES OUTPUT_NAME "generator")
set_target_properties(mtrp-base64-benchmark PROPERTIES OUTPUT_NAME "benchmark")
