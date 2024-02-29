#pragma once

#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

enum
{
    USAGE_ERR = 1, // usage
    SOCK_ERR = 2,  // socket
    SEND_ERR = 3   // send
};

class udpClient
{
public:
    // 客户端构造函数
    udpClient(const std::string &server_ip, uint16_t server_port)
        : server_ip_(server_ip), server_port_(server_port) {}

    // 初始化
    void init()
    {
        // 创建套接字获取文件描述符
        sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd_ == -1)
        {
            // 创建失败则打印错误信息并退出
            fprintf(stderr, "socket failed: %s\n", strerror(errno));
            exit(SOCK_ERR);
        }

        // 客户端也需要bind，但是不用显示bind绑定端口，由操作系统自动绑定
        // 当客户端发送数据时，操作系统会自动选择一个临时端口，并将其绑定到发送数据的UDP套接字上
    }

    // 启动客户端
    void start()
    {
        // 缓冲区
        char buffer[BUFFER_SIZE];

        // 定义服务器地址结构体
        struct sockaddr_in server_addr;
        socklen_t socklen = sizeof(sockaddr_in);
        // 清空服务器地址结构体
        bzero(&server_addr, sizeof(struct sockaddr_in));

        // 设置服务器地址结构体的属性
        server_addr.sin_family = AF_INET;                            // 地址族为 IPv4
        server_addr.sin_port = htons(server_port_);                  // 设置服务器端口号
        server_addr.sin_addr.s_addr = inet_addr(server_ip_.c_str()); // 设置服务器 IP 地址

        // 循环发送数据
        while (true)
        {
            // 清空缓冲区
            memset(buffer, 0, BUFFER_SIZE);
            // 提示用户输入消息
            std::cout << "Enter# ";
            // 从标准输入读取数据到缓冲区
            std::cin >> buffer;

            // 发送数据
            ssize_t bytes_sent = sendto(sockfd_, buffer, strlen(buffer), 0,
                                        (struct sockaddr *)&server_addr, socklen);

            if (bytes_sent == -1)
            {
                // 发送失败则打印错误信息并退出
                fprintf(stderr, "sendto failed: %s\n", strerror(errno));
                exit(SEND_ERR);
            }
        }
    }

    // 析构函数
    ~udpClient() {}

private:
    int sockfd_;            // 套接字文件描述符
    std::string server_ip_; // 服务器IP
    uint16_t server_port_;  // 服务器端口
};