add_definitions("-Wall")

set(SLIB "ctf")

aux_source_directory(log SRC_LIST)
aux_source_directory(thread SRC_LIST)

add_library(${SLIB} STATIC ${SRC_LIST})

target_link_libraries(${SLIB} pthread)