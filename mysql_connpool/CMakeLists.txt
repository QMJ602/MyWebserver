aux_source_directory(. LIB_SRCS)

add_compile_options(-std=c++11)

include_directories(../locker)  # 添加头文件路径

add_library(sql ${LIB_SRCS})

target_link_libraries(sql mysqlclient)