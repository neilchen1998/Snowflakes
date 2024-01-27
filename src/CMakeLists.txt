file(GLOB MATH_HEADER_LIST CONFIGURE_DEPENDS "${Snowflake_SOURCE_DIR}/include/math/*.hpp")
file(GLOB GRAPH_HEADER_LIST CONFIGURE_DEPENDS "${Snowflake_SOURCE_DIR}/include/graph/*.hpp" ${OpenCV_INCLUDE_DIRS})
file(GLOB COORDINATE_HEADER_LIST CONFIGURE_DEPENDS "${Snowflake_SOURCE_DIR}/include/coordinate/*.hpp")

add_library(math_library mathlib.cpp ${MATH_HEADER_LIST})
add_library(graph_library graphlib.cpp ${GRAPH_HEADER_LIST})
add_library(coordinate_library coordinatelib.cpp ${COORDINATE_HEADER_LIST})

target_include_directories(math_library PUBLIC ../include)
target_include_directories(graph_library PUBLIC ../include)
target_include_directories(coordinate_library PUBLIC ../include)

target_link_libraries(math_library PRIVATE Boost::boost)
target_link_libraries(graph_library PRIVATE ${OpenCV_LIBS})

target_compile_features(math_library PUBLIC cxx_std_17)
target_compile_features(graph_library PUBLIC cxx_std_17)
target_compile_features(coordinate_library PUBLIC cxx_std_17)