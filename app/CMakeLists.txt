# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_SRCS)

include_directories(
	../external/iniparser/include/
	../librarys/zlog/include/
	../librarys/osal/include/
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

# 指定生成 执行文件
add_executable(${PROJECT_NAME} ${DIR_SRCS})
# link library
#target_link_libraries(scheduling-server iniparser)
target_link_libraries(${PROJECT_NAME} zlog)
target_link_libraries(${PROJECT_NAME} osal)

# 指定安装路径
# 安装可执行文件，动静态库
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
#　安装普通文件
install (FILES "${PROJECT_SOURCE_DIR}/configs/log.conf" DESTINATION configs)
# 安装脚本文件
install (PROGRAMS "${PROJECT_SOURCE_DIR}/target/install.sh" DESTINATION .)
install (PROGRAMS "${PROJECT_SOURCE_DIR}/target/uninstall.sh" DESTINATION .)
