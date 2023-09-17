cmake_minimum_required(VERSION 2.8.12)
project (ParallelImageProcessing)

find_package(OpenCV REQUIRED)

set (CMAKE_SHARED_LINKER_FLAGS "-pthread")

add_executable(app ${CMAKE_SOURCE_DIR}/src/main.cpp)

target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(app PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(app PUBLIC ${OpenCV_LIBS})