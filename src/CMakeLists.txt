file(GLOB_RECURSE SRC_LIST *.cpp *.cc)

set(LIB_CT "ct")

add_library(${LIB_CT} STATIC ${SRC_LIST})

target_link_libraries(${LIB_CT} pthread)