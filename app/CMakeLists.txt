# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_SRCS)

include_directories(
	../external/iniparser/include/
	../librarys/zlog/include/
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pthread")

# 指定生成 执行文件
add_executable(basic-platform ${DIR_SRCS})
# link library
#target_link_libraries(scheduling-server iniparser)
target_link_libraries(basic-platform zlog)

# 指定安装路径
install(TARGETS basic-platform DESTINATION bin)
