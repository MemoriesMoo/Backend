#include "udpClient.hpp"
#include <memory>

// 使用说明
static void Usage(std::string proc)
{
    std::cout << "\nUsage:\n\t" << proc << " server_ip server_port\n\n";
}

// ./udpClient server_ip server_port
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(USAGE_ERR);
    }

    // 命令行获取服务器IP和端口号
    std::string server_ip = argv[1];
    uint16_t server_port = atoi(argv[2]);

    // 构建客户端对象
    std::unique_ptr<udpClient> ucli(new udpClient(server_ip, server_port));

    ucli->init();
    ucli->start();
}