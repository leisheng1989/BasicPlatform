# ./CMakeLists.txt，工程总配置文件

# 最低版本要求，必须
cmake_minimum_required(VERSION 2.8)

# 工程名
project(basic-platform)

message(STATUS "Host system: ${CMAKE_SYSTEM} ${CMAKE_SYSTEM_PROCESSOR}")

#版本信息
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

if (WIN32)
  #do something related to WIN32
elseif (UNIX)
  #do something related to UNIX
elseif(APPLE)
  #do something related to APPLE
endif (WIN32)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
  )

# 添加include目录,本例中文件在./下,所以直接取${PROJECT_SOURCE_DIR}/
include_directories(
	${PROJECT_SOURCE_DIR}/
)

# 添加链接库目录,库查找按照参数顺序从左到右查
link_directories(
	${PROJECT_BINARY_DIR}/libs
	/usr/local/libs
	/usr/lib
)

# 设置生成的库文件目录,这里设置成和库目录相同
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs)

#设置可执行文件目录,同样设成和库目录相同
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# 设置C编译器编译选项
set(CMAKE_C_FLAGS "-Wall -pipe -fmessage-length=0 -ffunction-sections -fdata-sections")
set(CMAKE_C_FLAGS_DEBUG "-g -ggdb -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -static -DNDEBUG")

if (USE_BITS MATCHES "i386")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
elseif (USE_BITS MATCHES "x86_64")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
endif()

#设置C编译器 连接选项
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -Wl,-gc-sections")


# 添加子目录（每个子目录下都必须有自已的CMakeLists.txt文件)
add_subdirectory(external)
add_subdirectory(librarys)
add_subdirectory(app)
if (CMAKE_BUILD_TYPE MATCHES "Release")

else ()
	add_subdirectory(test)
endif()

# 设置安装路径
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/target")

# 构建一个 CPack 安装包
include (InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_BINARY_STGZ "OFF")
set(CPACK_BINARY_TZ "OFF")
set(CPACK_BINARY_TBZ2 "ON")
set(CPACK_GENERATOR "TGZ;TBZ2")
set(CPACK_SOURCE_TZ "OFF")
SET(CPACK_SOURCE_GENERATOR "TGZ;TBZ2")
SET(CPACK_PACKAGE_RELOCATABLE "false")
set(CPACK_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/target")
set(CPACK_PACKAGE_VENDOR "EXCERA")
set(CPACK_PACKAGE_CONTACT "http://www.excera.com.cn")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}-${CMAKE_SYSTEM_NAME}-${USE_BITS}")
include (CPack)
# 生成二进制安装包
#cpack -C CPackConfig.cmake
#生成源码安装包
#cpack -C CPackSourceConfig.cmake
