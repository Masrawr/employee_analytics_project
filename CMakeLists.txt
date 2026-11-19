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

include(CTest)
if(BUILD_TESTING)
    add_executable(employee_tests
        tests/employee_tests.cpp
        src/Employee.cpp
        src/EmployeeIO.cpp
        src/Analytics.cpp
        src/EmployeeContainers.cpp
        src/ContainerAnalytics.cpp
    )
    target_include_directories(employee_tests PRIVATE include)
    add_test(NAME employee_model COMMAND employee_tests)
    find_package(Python3 COMPONENTS Interpreter QUIET)
    if(Python3_Interpreter_FOUND)
        add_test(NAME employee_integration
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/verify.py
                    $<TARGET_FILE:employee_analytics>)
    endif()
endif()

# Optional macOS hardware-profiling harness; the main application stays portable.
if(APPLE)
    add_executable(profile_driver EXCLUDE_FROM_ALL
        scripts/profile_driver.cpp
        src/Employee.cpp
        src/EmployeeIO.cpp
        src/EmployeeContainers.cpp
        src/RecursiveAlgorithms.cpp
        src/Benchmark.cpp
    )
    target_include_directories(profile_driver PRIVATE include)
endif()
