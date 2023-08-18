file(GLOB_RECURSE TEST_SOURCES 
"${CMAKE_CURRENT_SOURCE_DIR}/tests/**.cpp" 
"${CMAKE_CURRENT_SOURCE_DIR}/tests/**.c" 
"${CMAKE_CURRENT_SOURCE_DIR}/tests/**.cc" 
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# Executable
add_executable(mtrp-base64-tests ${TEST_SOURCES})
set_target_properties(mtrp-base64-tests PROPERTIES OUTPUT_NAME "tests")
target_link_libraries(mtrp-base64-tests mtrp-base64 GTest::gtest GTest::gtest_main)
gtest_discover_tests(mtrp-base64-tests)
