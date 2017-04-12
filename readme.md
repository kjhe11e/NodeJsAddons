This repo tracks my progress learning how to make NodeJs addons written in C/C++.

=========*Using node-gyp*==========
To run an application:

1) cd to the program's directory (e.g. MathAddon)

2) Run 'node-gyp configure'

3) Run 'node-gyp build'

4) Run 'node {main.js file}' to execute the program (e.g. 'node index.js')


==========*Using Nan and CMake*==========

CMake and Nan is a viable combination for creating NodeJs addons. IntelliJ's CLion IDE supports CMake.

// TODO: currently syntax highlighting is not configured in CLion for Nan.

-- Install cmake-js:

Run 'npm install cmake-js'

-- Basic project structure:

When creating a project in IntelliJ's CLion, a CMakeLists.txt file will be automatically generated.

The CMakeLists.txt file is CMake's version of node-gyp's binding.gyp file.

An example CMakeLists.txt file: 

-------------------------------------------------
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
-------------------------------------------------



