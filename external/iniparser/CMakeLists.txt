include_directories(
	include/
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -ansi -pedantic")

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(src DIR_SRCS)

# 指定生成动态链接库
#add_library (iniparser SHARED ${DIR_SRCS})
# 指定生成静态态链接库
add_library (iniparser STATIC ${DIR_SRCS})
