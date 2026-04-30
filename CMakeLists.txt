cmake_minimum_required (VERSION 4.2)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  

project(Blazar)

file(GLOB SOURCES 
    "src/*.cpp" 
)
 
add_library(Blazar STATIC ${SOURCES}) 

target_include_directories(Blazar PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(Blazar PROPERTIES
    CXX_STANDARD 26
    CXX_STANDARD_REQUIRED ON 
) 

option(BUILD_TESTS "Build tests" ON)
option(BUILD_MAIN "Build main executable" OFF) 

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
 
if(BUILD_MAIN)
    add_executable(main main.cpp)
    target_link_libraries     (main PRIVATE Blazar)
    target_include_directories(main PRIVATE include)

    set_target_properties(main PROPERTIES
        CXX_STANDARD 26
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )
endif()