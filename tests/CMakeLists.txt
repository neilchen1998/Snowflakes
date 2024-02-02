FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.6)
FetchContent_MakeAvailable(catch)

add_executable(testlib testlib.cpp)
add_executable(testCoordinatelib testCoordinatelib.cpp)
add_executable(testHelperlib testHelperlib.cpp)

target_compile_features(testlib PRIVATE cxx_std_17)
target_compile_features(testCoordinatelib PRIVATE cxx_std_17)
target_compile_features(testHelperlib PRIVATE cxx_std_17)

target_link_libraries(testlib PRIVATE math_library Catch2::Catch2)
target_link_libraries(testCoordinatelib PRIVATE coordinate_library Catch2::Catch2)
target_link_libraries(testHelperlib PRIVATE helper_library Catch2::Catch2)

add_test(NAME testlibtest COMMAND testlib)
add_test(NAME testCoordinatelibtest COMMAND testCoordinatelib)
add_test(NAME testHelperlibtest COMMAND testHelperlib)