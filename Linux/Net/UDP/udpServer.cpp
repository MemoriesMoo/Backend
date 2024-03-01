#include "udpServer.hpp"
#include <memory>
#include <fstream>
#include <unordered_map>

std::unordered_map<std::string, std::string> dict; // 字典
const std::string dict_txt = "./dict.txt";         // 字典路径

// 使用说明
static void Usage(std::string proc)
{
    std::cout << "\nUsage:\n\t" << proc << " server_port\n\n";
}

// 切割字符串
static bool cut_string(const std::string &target, std::string &key, std::string &value, const std::string sep)
{
    auto pos = target.find(sep);
    if (pos == std::string::npos)
        return false;

    key = target.substr(0, pos); // [)
    value = target.substr(pos + 1, target.size());
    return true;
}

// 加载字典
static void init_dict()
{
    std::ifstream in(dict_txt, std::ios::binary);
    if (!in.is_open())
    {
        std::cerr << "open " << dict_txt << "failed" << std::endl;
        exit(OPEN_ERR);
    }

    std::string line;
    std::string key, value;
    while (getline(in, line))
    {
        // std::cout << line << std::endl;
        if (cut_string(line, key, value, ":"))
            dict.insert(std::make_pair(key, value));
    }
}

static void debug_print()
{
    for(const auto& dt : dict)
    {
        std::cout << dt.first << ":" << dt.second << std::endl; 
    }
}

void handler_message(const std::string &client_ip, uint16_t client_port, const std::string &message)
{
    // 在此处完成对message特定的业务处理，不需要关心消息从何而来 -- 通信与业务解耦
}

// 命令行获取对应信息
int main(int argc, char *argv[])
{
    // if (argc != 2)
    // {
    //     Usage(argv[0]);
    //     exit(USAGE_ERR);
    // }

//     uint16_t server_port = atoi(argv[1]); // 获取端口号
//     // std::string server_ip = argv[2];      // 获取IP

//     // 构建服务器对象
//     std::unique_ptr<udpServer> usvr(new udpServer(handler_message, server_port));

//     // 初始化并运行服务器
//     usvr->init();
//     usvr->start();
        init_dict();
        debug_print();
}