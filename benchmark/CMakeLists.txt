include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(RANGE_GENERATOR_SOURCES range_generator.cpp)
set(RANGE_GENERATOR_EXECUTABLE rangegen)
add_executable(${RANGE_GENERATOR_EXECUTABLE} ${RANGE_GENERATOR_SOURCES})
target_link_libraries(${RANGE_GENERATOR_EXECUTABLE} ${Boost_LIBRARIES})

add_subdirectory(algorithm)
add_subdirectory(container)
add_subdirectory(iterator)
