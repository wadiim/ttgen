add_library(list list.c)
add_library(queue queue.c)
add_library(stack stack.c)
add_library(utils utils.c)

add_library(logic logic.c)
target_link_libraries(logic list queue stack utils)

add_executable(ttgen main.c)
target_link_libraries(ttgen logic)
