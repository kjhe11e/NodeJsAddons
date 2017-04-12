cmake_minimum_required(VERSION 3.5)

# name of project, will be name of plugin
project(Peripherals)

# build shared library named after the project from files in 'src/' dir
file(GLOB SOURCE_FILES "src/*.cpp" "src/*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# needed to resolve nan.h library
include_directories(${CMAKE_JS_INC} ../nan)

# give library file a .node extension without any "lib" prefix
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# essential include files to build a node addon,
# should add this line in every CMake.js based project
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})

# essential library files to link to a node addon
# add this line to every CMake.js based project
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
