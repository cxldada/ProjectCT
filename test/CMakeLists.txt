file(GLOB_RECURSE SRC_LIST *.cpp *.cc)

set(TARGET "testCT")

add_executable(${TARGET} ${SRC_LIST})
# 连接库
target_link_libraries(${TARGET} ct)