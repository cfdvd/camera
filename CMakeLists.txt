cmake_minimum_required(VERSION 3.24)
project(test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

aux_source_directory(./source SRC_DIR)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -std=gnu++20 -Werror -W -O2 -ftemplate-depth=4096 -lgomp -lpthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp -Wall -W -O2")

set(CMAKE_PREFIX_PATH "/home/zhb15/newDisk/SoftWare/Cxx_Lib/Qt/5.15.2/gcc_64/lib/cmake/")

set(BOOST_DEBUG ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(OpenMP REQUIRED)
find_package(TBB REQUIRED)
find_package(benchmark REQUIRED)
find_package(OpenCV REQUIRED)
find_package(fmt REQUIRED)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${BOOST_LIBRARY_DIRS})
add_definitions(-DBOOST_ALL_DYN_LINK)

add_executable(test ${SRC_DIR} source/MainWindow.h source/MainWindow.cpp)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(test Qt::Core Qt::Widgets)
target_link_libraries(test ${Boost_LIBRARIES})
target_link_libraries(test TBB::tbb TBB::tbbmalloc)
target_link_libraries(test OpenMP::OpenMP_CXX)
target_link_libraries(test benchmark::benchmark)
target_link_libraries(test fmt)
target_link_libraries(test ${OpenCV_LIBS})