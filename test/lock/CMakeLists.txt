set(TEST_TARGET lock-test)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量

aux_source_directory(. DIR_SRCS)

include_directories(
	${PROJECT_SOURCE_DIR}/librarys/zlog/include/
	${PROJECT_SOURCE_DIR}/librarys/osal/include/
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

# 指定生成 执行文件
add_executable(${TEST_TARGET} ${DIR_SRCS})
# link library
#target_link_libraries(scheduling-server iniparser)
target_link_libraries(${TEST_TARGET} zlog)
target_link_libraries(${TEST_TARGET} osal)
