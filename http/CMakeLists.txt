aux_source_directory(. LIB_SRCS)

add_compile_options(-std=c++11)

include_directories(../mysql_connpool)  # 添加头文件路径

add_library(http ${LIB_SRCS})

target_link_libraries(http sql) 