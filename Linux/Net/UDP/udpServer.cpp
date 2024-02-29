#include "udpServer.hpp"
#include <memory>

// 使用说明
void Usage(std::string proc)
{
    std::cout << "\nUsage:\n\t" << proc << " server_port\n\n";
}

void handler_message(const std::string &client_ip, uint16_t client_port, const std::string &message)
{
    // 在此处完成对message特定的业务处理，不需要关心消息从何而来 -- 通信与业务解耦
}

// 命令行获取对应信息
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
        exit(USAGE_ERR);
    }

    uint16_t server_port = atoi(argv[1]); // 获取端口号
    // std::string server_ip = argv[2];      // 获取IP

    // 构建服务器对象
    std::unique_ptr<udpServer> usvr(new udpServer(handler_message, server_port));

    // 初始化并运行服务器
    usvr->init();
    usvr->start();
}