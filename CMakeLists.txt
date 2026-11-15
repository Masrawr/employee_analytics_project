cmake_minimum_required(VERSION 3.16)
project(EmployeeAnalyticsProject2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(employee_analytics
    src/main.cpp
    src/Employee.cpp
    src/EmployeeIO.cpp
    src/Analytics.cpp
    src/EmployeeContainers.cpp
    src/ContainerAnalytics.cpp
    src/RecursiveAlgorithms.cpp
    src/Benchmark.cpp
)

target_include_directories(employee_analytics PRIVATE include)

if(MSVC)
    target_compile_options(employee_analytics PRIVATE /W4)
else()
    target_compile_options(employee_analytics PRIVATE -Wall -Wextra -Wpedantic)
endif()
