# Makefile for UDP Client-Server application

# 编译器
CC = g++
# 编译选项
CFLAGS = -std=c++11 -Wall
# 链接选项
LDFLAGS =

# 目标文件
TARGETS = udpClient udpServer
# 源文件
SRCS = udpClient.cpp udpServer.cpp
# 头文件
HDRS = udpClient.hpp udpServer.hpp

# 默认目标
all: $(TARGETS)

# 生成客户端可执行文件
udpClient: udpClient.cpp $(HDRS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

# 生成服务端可执行文件
udpServer: udpServer.cpp $(HDRS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

# 清除生成的文件
clean:
	rm -f $(TARGETS)
