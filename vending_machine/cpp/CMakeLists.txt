cmake_minimum_required(VERSION 3.8)
project(VendingMachine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
include_directories(
    src
)

set(SOURCE_FILES
    src/VendingMachine.h
    src/VendingMachine.cc
    src/Product.h
    src/Product.cc
    src/Transaction.h
    src/Transaction.cc 
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} main.cc)
