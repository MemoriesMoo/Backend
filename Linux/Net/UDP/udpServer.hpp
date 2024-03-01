#pragma once

#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <strings.h>
#include <functional>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static const std::string defaultIp = "0.0.0.0";
#define BUFFER_SIZE 1024

typedef std::function<void(std::string, uint16_t, std::string)> func_t;

enum
{
    USAGE_ERR = 1, // usage
    SOCK_ERR = 2,  // socket
    BIND_ERR = 3,  // bind
    RECV_ERR = 4,  // recvfrom
    OPEN_ERR = 5   // open
};

// udp服务端
class udpServer
{
public:
    // 构造函数
    udpServer(const func_t &call_back, const uint16_t &port, const std::string &ip = defaultIp)
        : call_back_(call_back), port_(port), ip_(ip) {}

    // 初始化
    void init()
    {
        // 1.创建套接字获取文件描述符
        sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd_ == -1)
        {
            // 创建失败则打印错误信息并退出
            fprintf(stderr, "socket failed: %s\n", strerror(errno));
            exit(SOCK_ERR);
        }

        // 2.绑定端口及IP地址
        // 服务器端口要不能随意改变，需要明确绑定
        struct sockaddr_in server_addr;           // IPv4地址结构体变量
        bzero(&server_addr, sizeof(server_addr)); // 将server_addr变量清零
        // memset(&server_addr, 0, sizeof(server_addr));

        // 设置服务器信息
        server_addr.sin_family = AF_INET;                            // 指定地址族为IPv4
        server_addr.sin_port = htons(port_);                         // 指定端口号
        server_addr.sin_addr.s_addr = htonl(inet_addr(ip_.c_str())); // 指定IPv4地址
        // server_addr.sin_addr.s_addr = INADDR_ANY;               // 使用任意可用的IP地址

        // 将套接字绑定到服务器地址
        int ret = bind(sockfd_, (const sockaddr *)&server_addr, sizeof(sockaddr_in));
        if (ret == -1)
        {
            // 创建失败则打印错误信息并退出
            fprintf(stderr, "bind failed: %s\n", strerror(errno));
            exit(BIND_ERR);
        }

        // 至此udp服务器预备工作完毕
    }

    void start()
    {
        // 服务器本质
        // 循环中持续监听来自客户端的连接请求或者数据传输，并根据请求的类型采取相应的行动

        // 创建用于接收数据的缓冲区
        char buffer[BUFFER_SIZE];
        // 循环接收数据
        while (true)
        {
            // 清空缓冲区
            memset(buffer, 0, sizeof(buffer));
            // 定义客户端地址结构体
            struct sockaddr_in client_addr;
            socklen_t socklen = sizeof(struct sockaddr_in);

            // 接收数据
            ssize_t bytes_received = recvfrom(sockfd_, buffer, BUFFER_SIZE - 1, 0,
                                              (struct sockaddr *)&client_addr, &socklen);

            if (bytes_received == -1)
            {
                // 接收失败则打印错误信息并退出
                fprintf(stderr, "recvfrom failed: %s\n", strerror(errno));
                exit(RECV_ERR);
            }

            // 在UDP套接字中，recvfrom函数不会返回0表示连接关闭，因为UDP是无连接的
            if (bytes_received > 0)
            {
                // 将接收到的数据转换为字符串
                buffer[bytes_received] = '\0';

                // printf("Received message: %s\n", buffer);
                // 将网络字节序的IP地址转换为点分十进制字符串并打印
                // printf("From: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

                uint16_t client_port = ntohs(client_addr.sin_port);      // 转换获取client端口号
                const char *client_ip = inet_ntoa(client_addr.sin_addr); // 转换获取clientIP地址

                // 打印获取的信息
                printf("Received message: %s | From: %s:%d\n", buffer, client_ip, client_port);

                call_back_(client_ip, client_port, buffer);
            }
        }
    }

    ~udpServer() {}

private:
    int sockfd_;       // 套接字文件描述符
    uint16_t port_;    // 端口号
    std::string ip_;   // IPv4地址
    func_t call_back_; // 回调函数
};