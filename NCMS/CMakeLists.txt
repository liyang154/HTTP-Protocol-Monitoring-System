cmake_minimum_required(VERSION 3.13)
project(NCMS C)

set(CMAKE_C_STANDARD 99)


# 添加第三方的库
#[[set(INC_DIR /usr/local/include/)
set(LINK_DIR /usr/local/lib)
set(ORACLE /data/oracle/product/11.2.0/db_1)]]

#[[include_directories(${INC_DIR})
include_directories(${ORACLE}/rdbms/public)
link_directories(${LINK_DIR})
link_directories(${ORACLE}/lib)]]

link_libraries(nids)
link_libraries(net)
link_libraries(pcap)
#link_libraries(clntsh)
link_libraries(gthread-2.0)
link_libraries(glib-2.0)
link_libraries(z)
# 查找当前目录下的所有源文件并将名称保存到 DIR_SRCS 变量
#[[aux_source_directory(. DIR_SRCS)]]

#add_executable(NCMS ncms-main.c queue.c hash.c actrie.c change.c aichang_analysis.c am_analysis.c telnet_analysis.c oracle.c mutex.h model.c update_model.c log_queue.c httprequest_analysis.c httpresponse_analysis.c http_hash.c ip.c uncompress.c queue.c ftp_analysis.c file_data.c linklist.c ip.c create_dns.c getdns.h)
#add_executable(NCMS oracle.c)
add_executable(NCMS main.c log_queue.h log_queue.c data_queue.h data_queue.c http_hash.h http_hash.c actrie.h actrie.c change.h change.c)
# 将第三方的库链接到可执行文件

target_link_libraries(NCMS nids net pcap gthread-2.0 glib-2.0 pthread z)