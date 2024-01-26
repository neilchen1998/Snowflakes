file(GLOB MATH_HEADER_LIST CONFIGURE_DEPENDS "${Snowflake_SOURCE_DIR}/include/math/*.hpp")

add_library(math_library mathlib.cpp ${MATH_HEADER_LIST})

target_include_directories(math_library PUBLIC ../include)

target_link_libraries(math_library PRIVATE Boost::boost)

target_compile_features(math_library PUBLIC cxx_std_17)