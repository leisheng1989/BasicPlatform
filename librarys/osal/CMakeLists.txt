include_directories(
	include/
	src/
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wstrict-prototypes -fwrapv -pthread")

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(src DIR_SRCS)

# 指定生成静态态链接库
add_library (osal STATIC ${DIR_SRCS})
