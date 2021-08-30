add_library(list list.c)
add_library(logic logic.c)
add_library(queue queue.c)
add_library(stack stack.c)
add_library(utils utils.c)

add_executable(ttgen main.c)

target_link_libraries(ttgen list logic queue stack utils)
