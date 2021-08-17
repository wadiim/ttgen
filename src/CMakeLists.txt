add_library(list list.c)
add_library(logic logic.c)

add_executable(ttgen main.c)

target_link_libraries(ttgen list logic)
