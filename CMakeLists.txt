cmake_minimum_required (VERSION 3.28)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(Blazar)

file(GLOB SOURCES 
    "src/*.cpp" 
)
 
add_library(Blazar STATIC ${SOURCES}) 

target_include_directories(Blazar PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(Blazar PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON 
) 

option(BUILD_TESTS ON)
option(BUILD_MAIN OFF) 

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
 
if(BUILD_MAIN)
    add_executable(main main.cpp)
    target_link_libraries     (main PRIVATE Blazar)
    target_include_directories(main PRIVATE include)

    set_target_properties(main PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )
endif()