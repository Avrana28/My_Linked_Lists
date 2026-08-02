cmake_minimum_required(VERSION 3.15)
project(MyLinkedList C)

set(CMAKE_C_STANDARD 17)

add_library(my_linked_list libs/linked_list.c)

add_executable(Test src/main.c)

target_include_directories(Test PUBLIC
  libs
  src
)

target_link_libraries(Test PRIVATE my_linked_list)
