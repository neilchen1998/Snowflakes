add_executable(app app.cpp)
target_compile_features(app PRIVATE cxx_std_17)

# required libraries
target_link_libraries(app PRIVATE math_library graph_library ${OpenCV_LIBS} coordinate_library)