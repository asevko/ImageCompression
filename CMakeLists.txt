cmake_minimum_required(VERSION 3.8)
project(ImageCompression)

set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )

find_package(ARMADILLO REQUIRED)

set(SOURCE_FILES main.cpp rectangleModel.h ractangleModel.cpp imageModel.cpp imageModel.h)
add_executable(ImageCompression ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( ImageCompression ${OpenCV_LIBS} )

include_directories(${ARMADILLO_INCLUDE_DIRS})
target_link_libraries( ImageCompression ${ARMADILLO_LIBRARIES} )

